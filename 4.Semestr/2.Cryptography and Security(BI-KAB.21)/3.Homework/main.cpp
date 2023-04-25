#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <fstream>
#include <cassert>

#include <openssl/evp.h>
#include <openssl/pem.h>

using namespace std;

#endif /* __PROGTEST__ */

#define K_BUFFER_SIZE 4096

bool controlFiles(const char * inFile, const char * outFile, ifstream & in, ofstream & out, const char * someKeyFile, EVP_PKEY * someKey) {
    if(!someKey) {
        cout << "Failde to read key from file " << someKeyFile << endl;
        return false;
    }

    //Open the input and output files
    if (!in.is_open()) {
        cout << "Filed to open input file " << inFile << endl;
        return false;
    }

    if(!out.is_open()) {
        cout << "Failed to open output file " << outFile << endl;
        return false;
    }
    return true;
}

void cleanUp(const char * outFile, ifstream & in, ofstream & out, EVP_CIPHER_CTX * ctx, EVP_PKEY * someKey, bool end) {
    if(in.is_open()) {
        in.close();
    }
    if(out.is_open()) {
        out.close();
    }
    if(!end) {
        remove(outFile);
    }
    if(someKey) {
        EVP_PKEY_free(someKey);
    }
    if(ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
}

bool openReadHeader(ifstream & in, int & nid, unsigned char * my_ek, int & encKeyLen, std::unique_ptr<uint8_t[]> & iv) {
    in.read(reinterpret_cast<char *>(&nid), sizeof(nid));
    if(!in.good()) {
        cout << "Failed to read nid from input file" << endl;
        return false;
    }

    //Read the IV from the input file
    in.read(reinterpret_cast<char*>(&encKeyLen), sizeof(encKeyLen));
    if(!in.good()) {
        cout << "Failed to read encrypted key length from input file" << endl;
        return false;
    }

    //Read the encrypted key from the input file
    in.read(reinterpret_cast<char*>(my_ek), encKeyLen);
    if(!in.good()) {
        cout << "Failed to read encrypted key from input file" << endl;
        return false;
    }

    //Read the IV from the input file
    int ivLen = EVP_CIPHER_iv_length(EVP_get_cipherbynid(nid));
    iv = make_unique<uint8_t[]>(ivLen);
    in.read(reinterpret_cast<char *>(iv.get()), ivLen);
    if (!in.good()) {
        cout << "Failed to read IV from input file" << endl;
        return false;
    }

    return true;
}

bool sealWriteHeader(const char * outFile, ofstream & out, int & nid, unsigned char * my_ek, int & encKeyLen, std::unique_ptr<uint8_t[]> & iv, int & ivLen) {

    out.write(reinterpret_cast<char*>(&nid), sizeof(nid));
    if(!out.good()) {
        cout << "Can't writting nid header to file " << outFile << endl;
        return false;
    }

    out.write(reinterpret_cast<char*>(&encKeyLen), sizeof(encKeyLen));
    if(!out.good()) {
        cout << "Failed to write encrypted key length to output file" << endl;
        return false;
    }

    out.write(reinterpret_cast<char*>(my_ek), encKeyLen);
    if(!out.good()) {
        cout << "Failed to write encrypted key to output file" << endl;
        return false;
    }

    out.write(reinterpret_cast<char *>(iv.get()), ivLen);
    if (!out.good()) {
        cout << "Failed write IV to output file" << endl;
        return false;
    }

    return true;
}

bool updateFinal(const char * outFile, ifstream & in, ofstream & out, EVP_CIPHER_CTX * ctx, const char & type) {
    //Prepare buffer for input data and encryption or decrypt output data
    unsigned char inBuffer[K_BUFFER_SIZE];
    unsigned char outBuffer[K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outLength = 0;

    //Read data from the input file, it's using the EVP_SealUpdate function, and write it to the output file
    while (in.good()) {
        in.read(reinterpret_cast<char*>(inBuffer), K_BUFFER_SIZE);
        int inLength = (int)(in.gcount());
        if(type == 's') {
            if (EVP_SealUpdate(ctx, outBuffer, &outLength, inBuffer, inLength) != 1) {
                cout << "Failed to encrypt data" << endl;
                return false;
            }
        } else {
            if (EVP_OpenUpdate(ctx, outBuffer, &outLength, inBuffer, inLength) != 1) {
                cout << "Failed to encrypt data" << endl;
                return false;
            }
        }

        out.write(reinterpret_cast<char*>(outBuffer), outLength);
        if(!out.good()) {
            cout << "Can't writting data to file " << outFile << endl;
            return false;
        }
    }

    //Finalize the context using the EVP_SealFinal function
    if(type == 's') {
        if (EVP_SealFinal(ctx, outBuffer, &outLength) != 1) {
            cout << "Failed to finalize OpenSSL cipher context" << endl;
            return false;
        }
    } else {
        if (EVP_OpenFinal(ctx, outBuffer, &outLength) != 1) {
            cout << "Failed to finalize OpenSSL cipher context" << endl;
            return false;
        }
    }

    //Write the final block of data to the output file
    out.write(reinterpret_cast<char*>(outBuffer), outLength);
    if(!out.good()) {
        cout << "Can't writting data to file " << outFile << endl;
        return false;
    }
    return true;
}

bool seal(const char * inFile, const char * outFile, const char * publicKeyFile, const char * symmetricCipher) {
    if(!inFile || !outFile || !publicKeyFile || !symmetricCipher) {
        if(outFile) {
            remove(outFile);
        }
        return false;
    }

    //Init public key, in and out files
    FILE* fp = fopen(publicKeyFile, "r");
    if(!fp) {
        cout << "Failed to open key file " << publicKeyFile << endl;
        if(outFile) {
            remove(outFile);
        }
        return false;
    }
    EVP_PKEY* publicKey = PEM_read_PUBKEY(fp, nullptr, nullptr, nullptr);
    fclose(fp);
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary | ios::trunc);

    if(!controlFiles(inFile, outFile, in, out, publicKeyFile, publicKey)) {
        cleanUp(outFile, in, out, nullptr, publicKey, false);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        cout << "Failed to create OpenSSL cipher context" << std::endl;
        cleanUp(outFile, in, out, ctx, publicKey, false);
        return false;
    }

    int encKeyLen = EVP_PKEY_size(publicKey);
    auto * my_ek = (unsigned char *) malloc(encKeyLen);
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(symmetricCipher);
    if (!cipher) {
        cout << "Invalid cipher name" << endl;
        cleanUp(outFile, in, out, ctx, publicKey, false);
        free(my_ek);
        return false;
    }

    //Generate the symetric key and IV
    int nid = EVP_CIPHER_nid(cipher);
    int ivLen = EVP_CIPHER_iv_length(EVP_get_cipherbynid(nid));
    std::unique_ptr<uint8_t[]> iv = make_unique<uint8_t[]>(ivLen);

    //Initialize the encryption context
    if(EVP_SealInit(ctx, cipher, &my_ek, &encKeyLen, iv.get(), &publicKey, 1) != 1) {
        cout << "Failed to initialize OpenSSL cipher context" << endl;
        cleanUp(outFile, in, out, ctx, publicKey, false);
        free(my_ek);
        return false;
    }

    if(!sealWriteHeader(outFile, out, nid, my_ek, encKeyLen, iv, ivLen)) {
        cleanUp(outFile, in, out, ctx, publicKey, false);
        free(my_ek);
        return false;
    }

    if(!updateFinal(outFile, in, out, ctx, 's')) {
        cleanUp(outFile, in, out, ctx, publicKey, false);
        free(my_ek);
        return false;
    }

    cleanUp(outFile, in, out, ctx, publicKey, true);
    free(my_ek);
    return true;
}

bool open(const char *inFile, const char *outFile, const char *privateKeyFile) {
    if(!inFile || !outFile || !privateKeyFile) {
        if(outFile) {
            remove(outFile);
        }
        return false;
    }

    //Init public key, in and out files
    FILE* fp = fopen(privateKeyFile, "r");
    if(!fp) {
        cout << "Failed to open key file " << privateKeyFile << endl;
        if(outFile) {
            remove(outFile);
        }
        return false;
    }
    EVP_PKEY* privateKey = PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr);
    fclose(fp);
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary | ios::trunc);

    if(!controlFiles(inFile, outFile, in, out, privateKeyFile, privateKey)) {
        cleanUp(outFile, in, out, nullptr, privateKey, false);
        return false;
    }

    int nid = 0;
    int encKeyLen = EVP_PKEY_size(privateKey);
    auto * my_ek = (unsigned char *) malloc(encKeyLen);
    std::unique_ptr<uint8_t[]> iv;
    if(!openReadHeader(in, nid, my_ek, encKeyLen, iv)) {
        cleanUp(outFile, in, out, nullptr, privateKey, false);
        free(my_ek);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cout << "Could not create cipher context" << endl;
        cleanUp(outFile, in, out, ctx, privateKey, false);
        free(my_ek);
        return false;
    }

    const EVP_CIPHER *cipher = EVP_get_cipherbynid(nid);
    if(!cipher) {
        cout << "Invalid cipher" << endl;
        cleanUp(outFile, in, out, ctx, privateKey, false);
        free(my_ek);
        return false;
    }

    //Initialize the decryption context
    if (EVP_OpenInit(ctx, cipher, my_ek, encKeyLen, iv.get(), privateKey) != 1) {
        cout << "Could not initialize decryption operation" << endl;
        cleanUp(outFile, in, out, ctx, privateKey, false);
        free(my_ek);
        return false;
    }

    if(!updateFinal(outFile, in, out, ctx, 'o')) {
        cleanUp(outFile, in, out, ctx, privateKey, false);
        free(my_ek);
        return false;
    }

    cleanUp(outFile, in, out, ctx, privateKey, true);
    free(my_ek);
    return true;
}


#ifndef __PROGTEST__

int main(void) {
    assert( seal("tests/fileToEncrypt.txt", "tests/sealed.bin", "tests/PublicKey.pem", "aes-128-cbc") );
    assert( open("tests/sealed.bin", "tests/openedFileToEncrypt.txt", "tests/PrivateKey.pem") );

    assert(open("tests/sealed_sample.bin", "tests/opened_sample.txt", "tests/PrivateKey.pem"));

    return 0;
}

#endif /* __PROGTEST__ */

