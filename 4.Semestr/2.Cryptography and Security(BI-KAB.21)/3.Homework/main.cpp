#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/pem.h>

using namespace std;

#endif /* __PROGTEST__ */

#define K_BUFFER_SIZE 4096

bool seal(const char * inFile, const char * outFile, const char * publicKeyFile, const char * symmetricCipher) {
    //Read the public key from file
    FILE* fp = fopen(publicKeyFile, "rb");
    if(!fp) {
        cout << "Failed to open key file " << publicKeyFile << endl;
        return false;
    }

    EVP_PKEY* publicKey = PEM_read_PUBKEY(fp, NULL, NULL, NULL);
    fclose(fp);

    if(!publicKey) {
        cout << "Failde to read public key from file " << publicKeyFile << endl;
    }

    //Generate the symetric key and IV
    unsigned char iv[EVP_MAX_IV_LENGTH];
    int encKeyLen;


    //Open the input and output files
    ifstream in(inFile, ios::binary);
    if (!in.is_open()) {
        cout << "Filed to open input file " << inFile << endl;
        EVP_PKEY_free(publicKey);
        return false;
    }

    ofstream out(outFile, ios::binary | ios::trunc);
    if(!out.is_open()) {
        cout << "Failed to open output file " << outFile << endl;
        EVP_PKEY_free(publicKey);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        cout << "Failed to create OpenSSL cipher context" << std::endl;
        EVP_PKEY_free(publicKey);
        return false;
    }

    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(publicKey));
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(symmetricCipher);

    //Initialize the encryption context
    if(EVP_SealInit(ctx, cipher, &my_ek, &encKeyLen, iv, &publicKey, 1) != 1) {
        cout << "Failed to initialize OpenSSL cipher context" << endl;
        EVP_CIPHER_CTX_free(ctx);
        EVP_PKEY_free(publicKey);
        return false;
    }

    //Write the IV to the output file
    out.write(reinterpret_cast<const char*>(iv), EVP_MAX_IV_LENGTH);
    if(!out.good()) {
        cout << "Failed to write IV to output file" << endl;
        EVP_CIPHER_CTX_free(ctx);
        EVP_PKEY_free(publicKey);
        return false;
    }

    //Prepare buffer for input data and encryption output data
    unsigned char inBuffer[K_BUFFER_SIZE];
    unsigned char outBuffer[K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outLength = 0;

    //Read data from the input file, encryption it's using the EVP_DecryptUpdate function, and write it to the output file
    while (in.good()) {
        in.read(reinterpret_cast<char*>(inBuffer), K_BUFFER_SIZE);
        int inLength = (int)(in.gcount());
        if (EVP_SealUpdate(ctx, outBuffer, &outLength, inBuffer, inLength) != 1) {
            cout << "Failed to encrypt data" << endl;
            EVP_CIPHER_CTX_free(ctx);
            EVP_PKEY_free(publicKey);
            return false;
        }

        out.write(reinterpret_cast<char*>(outBuffer), outLength);
        if(!out.good()) {
            cout << "Can't writting data to file " << outFile << endl;
            out.close();
            EVP_CIPHER_CTX_free(ctx);
            EVP_PKEY_free(publicKey);
            return false;
        }
    }

    //Finalize the encryption context using the EVP_DecryptFinal_ex function
    if (EVP_SealFinal(ctx, outBuffer, &outLength) != 1) {
        cout << "Failed to finalize OpenSSL cipher context" << endl;
        EVP_CIPHER_CTX_free(ctx);
        EVP_PKEY_free(publicKey);
        return false;
    }

    //Write the final block of encryption data to the output file
    out.write(reinterpret_cast<char*>(outBuffer), outLength);
    if(!out.good()) {
        cout << "Can't writting data to file " << outFile << endl;
        out.close();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    EVP_PKEY_free(publicKey);
    return true;
}

bool open(const char *inFile, const char *outFile, const char *privateKeyFile) {
    // Load the private key from file
    FILE *fp = fopen(privateKeyFile, "r");
    if (!fp) {
        cerr << "Error: could not open private key file: " << privateKeyFile << endl;
        return false;
    }

    EVP_PKEY *privateKey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);
    if (!privateKey) {
        cerr << "Error: could not load private key from file: " << privateKeyFile << endl;
        return false;
    }

    // Open the input and output files
    ifstream in(inFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Error: could not open input file: " << inFile << endl;
        EVP_PKEY_free(privateKey);
        return false;
    }

    ofstream out(outFile, ios::binary);
    if (!out.is_open()) {
        cerr << "Error: could not open output file: " << outFile << endl;
        EVP_PKEY_free(privateKey);
        return false;
    }

    //Read the IV from the input file
    unsigned  char iv[EVP_MAX_IV_LENGTH];
    in.read(reinterpret_cast<char*>(iv), EVP_MAX_IV_LENGTH);
    if(!in.good()) {
        cout << "Failed to read IV from input file" << endl;
        EVP_PKEY_free(privateKey);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Error: could not create cipher context" << endl;
        EVP_PKEY_free(privateKey);
        return false;
    }

    const char* K_SYMMETRIC_CIPHER = "AES-256-CBC";
    const EVP_CIPHER  *cipher = EVP_get_cipherbyname(K_SYMMETRIC_CIPHER);

    //Initialize the decryption context
    if (!EVP_OpenInit(ctx, cipher, NULL, 0, NULL, privateKey)) {
        cerr << "Error: could not initialize decryption operation" << endl;
        EVP_CIPHER_CTX_free(ctx);
        EVP_PKEY_free(privateKey);
        return false;
    }

    //Prepare buffer for input data and decryption output data
    unsigned char inBuffer[K_BUFFER_SIZE];
    unsigned char outBuffer[K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outLenght = 0;

    //Read data from the input file, decrypt it using the EVP_OpenUpdate function, and write it to the output file
    while (in.good()) {
        in.read(reinterpret_cast<char*>(inBuffer), K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH);
        int inLenght = (int)in.gcount();

        if (EVP_OpenUpdate(ctx, outBuffer, &outLenght, inBuffer, inLenght) != 1) {
            cout << "Failed to decrypt data" << endl;
            EVP_CIPHER_CTX_free(ctx);
            EVP_PKEY_free(privateKey);
            return false;
        }

        out.write(reinterpret_cast<char*>(outBuffer), outLenght);
        if(!out.good()) {
            cout << "Failed to write decrypted data to output file" << endl;
            out.close();
            EVP_CIPHER_CTX_free(ctx);
            EVP_PKEY_free(privateKey);
            remove(outFile);
            return false;
        }
    }

    // Finalize the decryption operation
    if (EVP_OpenFinal(ctx, outBuffer, &outLenght) != 1) {
        cerr << "Error: decryption error" << endl;
        EVP_CIPHER_CTX_free(ctx);
        EVP_PKEY_free(privateKey);
        return false;
    }

    //Write the final block of encryption data to the output file
    out.write(reinterpret_cast<char*>(outBuffer), outLenght);
    if(!out.good()) {
        cout << "Failed to write decrypted data to output file" << endl;
        out.close();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    EVP_PKEY_free(privateKey);
    return true;
}


#ifndef __PROGTEST__

int main(void) {
    assert( seal("test/fileToEncrypt", "sealed.bin", "tests/PublicKey.pem", "aes-128-cbc") );
    assert( open("sealed.bin", "openedFileToEncrypt", "tests/PrivateKey.pem") );

    assert(open("tests/sealed_sample.bin", "opened_sample.txt", "tests/PrivateKey.pem"));

    return 0;
}

#endif /* __PROGTEST__ */

