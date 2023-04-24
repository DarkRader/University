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

void cleanUp(const char * outFile, FILE * fp, ifstream & in, ofstream & out,
             EVP_CIPHER_CTX * ctx, EVP_PKEY * someKey) {
    in.close();
    out.close();
    EVP_PKEY_free(someKey);
    EVP_CIPHER_CTX_free(ctx);
    fclose(fp);
    remove(outFile);
}

bool UpdateFinal() {

    return true;
}

bool seal(const char * inFile, const char * outFile, const char * publicKeyFile, const char * symmetricCipher) {
    //Read the public key from file
    FILE* fp = fopen(publicKeyFile, "rb");
    if(!fp) {
        cout << "Failed to open key file " << publicKeyFile << endl;
        fclose(fp);
        return false;
    }

    EVP_PKEY* publicKey = PEM_read_PUBKEY(fp, NULL, NULL, NULL);
    fclose(fp);

    if(!publicKey) {
        cout << "Failde to read public key from file " << publicKeyFile << endl;
        EVP_PKEY_free(publicKey);
        fclose(fp);
        return false;
    }

    //Generate the symetric key and IV
    unsigned char iv[EVP_MAX_IV_LENGTH];
    int encKeyLen = 0;

    //Open the input and output files
    ifstream in(inFile, ios::binary);
    if (!in.is_open()) {
        cout << "Filed to open input file " << inFile << endl;
        in.close();
        EVP_PKEY_free(publicKey);
        fclose(fp);
        return false;
    }

    ofstream out(outFile, ios::binary | ios::trunc);
    if(!out.is_open()) {
        cout << "Failed to open output file " << outFile << endl;
        in.close();
        out.close();
        EVP_PKEY_free(publicKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        cout << "Failed to create OpenSSL cipher context" << std::endl;
        in.close();
        out.close();
        EVP_PKEY_free(publicKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(publicKey));
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(symmetricCipher);
    if (!cipher) {
        cout << "Invalid cipher name" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    //Initialize the encryption context
    if(EVP_SealInit(ctx, cipher, &my_ek, &encKeyLen, iv, &publicKey, 1) != 1) {
        cout << "Failed to initialize OpenSSL cipher context" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    int nid = EVP_CIPHER_nid(cipher);
    out.write(reinterpret_cast<char*>(&nid), sizeof(nid));
    if(!out.good()) {
        cout << "Can't writting nid header to file " << outFile << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    out.write(reinterpret_cast<char*>(&encKeyLen), sizeof(encKeyLen));
    if(!out.good()) {
        cout << "Failed to write encrypted key length to output file" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    out.write(reinterpret_cast<char*>(&my_ek), sizeof(encKeyLen));
    if(!out.good()) {
        cout << "Failed to write encrypted key to output file" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    int ivLen = EVP_CIPHER_iv_length(EVP_get_cipherbynid(nid));
    out.write(reinterpret_cast<char*>(iv), ivLen);
    if(!out.good()) {
        cout << "Failed write IV to output file" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
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
            cleanUp(outFile, fp, in, out, ctx, publicKey);
            return false;
        }

        out.write(reinterpret_cast<char*>(outBuffer), outLength);
        if(!out.good()) {
            cout << "Can't writting data to file " << outFile << endl;
            cleanUp(outFile, fp, in, out, ctx, publicKey);
            return false;
        }
    }

    //Finalize the encryption context using the EVP_DecryptFinal_ex function
    if (EVP_SealFinal(ctx, outBuffer, &outLength) != 1) {
        cout << "Failed to finalize OpenSSL cipher context" << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    //Write the final block of encryption data to the output file
    out.write(reinterpret_cast<char*>(outBuffer), outLength);
    if(!out.good()) {
        cout << "Can't writting data to file " << outFile << endl;
        cleanUp(outFile, fp, in, out, ctx, publicKey);
        return false;
    }

    //Clean up
    cleanUp(outFile, fp, in, out, ctx, publicKey);
    return true;
}

bool open(const char *inFile, const char *outFile, const char *privateKeyFile) {
    // Load the private key from file
    FILE *fp = fopen(privateKeyFile, "rb");
    if (!fp) {
        cout << "Could not open private key file: " << privateKeyFile << endl;
        fclose(fp);
        return false;
    }

    EVP_PKEY *privateKey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);
    if (!privateKey) {
        cout << "Could not load private key from file: " << privateKeyFile << endl;
        EVP_PKEY_free(privateKey);
        fclose(fp);
        return false;
    }

    // Open the input and output files
    ifstream in(inFile, ios::binary);
    if (!in.is_open()) {
        cout << "Could not open input file: " << inFile << endl;
        in.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        return false;
    }

    ofstream out(outFile, ios::binary);
    if (!out.is_open()) {
        cout << "Could not open output file: " << outFile << endl;
        in.close();
        out.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    int nid = 0;
    in.read(reinterpret_cast<char *>(&nid), sizeof(nid));
    if(!in.good()) {
        cout << "Failed to read nid from input file" << endl;
        in.close();
        out.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    //Read the IV from the input file
    int encKeyLen = 0;
    in.read(reinterpret_cast<char*>(&encKeyLen), sizeof(encKeyLen));
    if(!in.good()) {
        cout << "Failed to read encrypted key length from input file" << endl;
        in.close();
        out.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    //Read the encrypted key from the input file
    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(privateKey));
    in.read(reinterpret_cast<char*>(my_ek), encKeyLen);
    if(!in.good()) {
        cout << "Failed to read encrypted key from input file" << endl;
        in.close();
        out.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    //Read the IV from the input file
    unsigned char iv[EVP_MAX_IV_LENGTH];
    int ivLen = EVP_CIPHER_iv_length(EVP_get_cipherbynid(nid));
    in.read(reinterpret_cast<char*>(iv), ivLen);
    if(!in.good()) {
        cout << "Failed to read IV from input file" << endl;
        in.close();
        out.close();
        EVP_PKEY_free(privateKey);
        fclose(fp);
        remove(outFile);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cout << "Could not create cipher context" << endl;
        cleanUp(outFile, fp, in, out, ctx, privateKey);
        return false;
    }

    const EVP_CIPHER *cipher = EVP_get_cipherbynid(nid);
    if(!cipher) {
        cout << "Invalid cipher" << endl;
        cleanUp(outFile, fp, in, out, ctx, privateKey);
        return false;
    }

    //Initialize the decryption context
    if (EVP_OpenInit(ctx, cipher, my_ek, encKeyLen, iv, privateKey) != 1) {
        cout << "Could not initialize decryption operation" << endl;
        cleanUp(outFile, fp, in, out, ctx, privateKey);
        return false;
    }

    //Prepare buffer for input data and decryption output data
    unsigned char inBuffer[K_BUFFER_SIZE];
    unsigned char outBuffer[K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outLenght = 0;

    //Read data from the input file, decrypt it using the EVP_OpenUpdate function, and write it to the output file
    while (in.good()) {
        in.read(reinterpret_cast<char*>(inBuffer), K_BUFFER_SIZE);
        int inLenght = (int)in.gcount();

        if (EVP_OpenUpdate(ctx, outBuffer, &outLenght, inBuffer, inLenght) != 1) {
            cout << "Failed to decrypt data" << endl;
            cleanUp(outFile, fp, in, out, ctx, privateKey);
            return false;
        }

        out.write(reinterpret_cast<char*>(outBuffer), outLenght);
        if(!out.good()) {
            cout << "Failed to write decrypted data to output file" << endl;
            cleanUp(outFile, fp, in, out, ctx, privateKey);
            return false;
        }
    }

    // Finalize the decryption operation
    if (EVP_OpenFinal(ctx, outBuffer, &outLenght) != 1) {
        cout << "Decryption error" << endl;
        cleanUp(outFile, fp, in, out, ctx, privateKey);
        return false;
    }

    //Write the final block of encryption data to the output file
    out.write(reinterpret_cast<char*>(outBuffer), outLenght);
    if(!out.good()) {
        cout << "Failed to write decrypted data to output file" << endl;
        cleanUp(outFile, fp, in, out, ctx, privateKey);
        return false;
    }

    // Clean up
    cleanUp(outFile, fp, in, out, ctx, privateKey);
    return true;
}


#ifndef __PROGTEST__

int main(void) {
//    assert( seal("test/fileToEncrypt", "sealed.bin", "tests/PublicKey.pem", "aes-128-cbc") );
//    assert( open("sealed.bin", "openedFileToEncrypt", "tests/PrivateKey.pem") );

    assert(open("tests/sealed_sample.bin", "opened_sample.txt", "tests/PrivateKey.pem"));

    return 0;
}

#endif /* __PROGTEST__ */

