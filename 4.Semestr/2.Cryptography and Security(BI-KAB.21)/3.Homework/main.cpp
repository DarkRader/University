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

void cleanUp(const char * inFile, const char * outFile, ifstream & in, ofstream & out,
             EVP_CIPHER_CTX * ctx, EVP_PKEY * someKey, bool end) {
    if(in.is_open()) {
        in.close();
    }
    if(out.is_open()) {
        out.close();
        if(!end) {
            remove(outFile);
        }
    }
    if(someKey) {
        EVP_PKEY_free(someKey);
    }
    if(ctx) {
        EVP_CIPHER_CTX_free(ctx);
    }
}

bool updateFinal(const char * inFile, const char * outFile, ifstream & in, ofstream & out,
                 EVP_CIPHER_CTX * ctx, const char & type) {
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

bool openReadHeader(const char * inFile, const char * outFile, ifstream & in, ofstream & out, int & nid, unsigned char * my_ek,
                   int & encKeyLen, EVP_PKEY * someKey, std::unique_ptr<uint8_t[]> & iv) {
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
//    if(ivLen > 0) {
        iv = make_unique<uint8_t[]>(ivLen);
        in.read(reinterpret_cast<char *>(iv.get()), ivLen);
        if (!in.good()) {
            cout << "Failed to read IV from input file" << endl;
            return false;
        }
//    }

    return true;
}

bool sealWriteHeader(const char * inFile, const char * outFile, ifstream & in, ofstream & out, int & nid, unsigned char * my_ek,
                   int & encKeyLen, EVP_CIPHER_CTX * ctx, EVP_PKEY * publicKey, std::unique_ptr<uint8_t[]> & iv) {

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

    int ivLen = EVP_CIPHER_iv_length(EVP_get_cipherbynid(nid));
    if (ivLen > 0) {
        iv = make_unique<uint8_t[]>(ivLen);
        if(!RAND_bytes(iv.get(), ivLen)) {
            cout << "Failed to generate random IV" << endl;
            return false;
        }
        out.write(reinterpret_cast<char *>(iv.get()), ivLen);
        if (!out.good()) {
            cout << "Failed write IV to output file" << endl;
            return false;
        }
    }

    return true;
}

bool initData(const char * inFile, const char * outFile, ifstream & in, ofstream & out, const char * someKeyFile, EVP_PKEY * someKey) {

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

bool seal(const char * inFile, const char * outFile, const char * publicKeyFile, const char * symmetricCipher) {
    if(!inFile || !outFile || !publicKeyFile || !symmetricCipher) {
        if(outFile) {
            remove(outFile);
        }
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

    if(!initData(inFile, outFile, in, out, publicKeyFile, publicKey)) {
        cleanUp(inFile, outFile, in, out, nullptr, publicKey, false);
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        cout << "Failed to create OpenSSL cipher context" << std::endl;
        cleanUp(inFile, outFile, in, out, ctx, publicKey, false);
        return false;
    }

    int encKeyLen = EVP_PKEY_size(publicKey);
    auto * my_ek = new unsigned char[encKeyLen];
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(symmetricCipher);
    if (!cipher) {
        cout << "Invalid cipher name" << endl;
        cleanUp(inFile, outFile, in, out, ctx, publicKey, false);
        delete [] my_ek;
        return false;
    }

    //Generate the symetric key and IV
    int nid = EVP_CIPHER_nid(cipher);
    std::unique_ptr<uint8_t[]> iv;
    if(!sealWriteHeader(inFile, outFile, in, out, nid, my_ek, encKeyLen, ctx, publicKey, iv)) {
        cleanUp(inFile, outFile, in, out, ctx, publicKey, false);
        delete [] my_ek;
        return false;
    }

    //Initialize the encryption context
    if(EVP_SealInit(ctx, cipher, &my_ek, &encKeyLen, iv.get(), &publicKey, 1) != 1) {
        cout << "Failed to initialize OpenSSL cipher context" << endl;
        cleanUp(inFile, outFile, in, out, ctx, publicKey, false);
        delete [] my_ek;
        return false;
    }

    if(!updateFinal(inFile, outFile, in, out, ctx, 's')) {
        cleanUp(inFile, outFile, in, out, ctx, publicKey, false);
        delete [] my_ek;
        return false;
    }

    cleanUp(inFile, outFile, in, out, ctx, publicKey, true);
    delete [] my_ek;
    return true;
}

bool open(const char *inFile, const char *outFile, const char *privateKeyFile) {
    if(!inFile || !outFile || !privateKeyFile) {
        if(outFile) {
            remove(outFile);
        }
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

    if(!initData(inFile, outFile, in, out, privateKeyFile, privateKey)) {
        cleanUp(inFile, outFile, in, out, nullptr, privateKey, false);
        return false;
    }

    int nid = 0;
    int encKeyLen = EVP_PKEY_size(privateKey);
    auto * my_ek = new unsigned char[encKeyLen];
    std::unique_ptr<uint8_t[]> iv;
    if(!openReadHeader(inFile, outFile, in, out, nid, my_ek, encKeyLen, privateKey, iv)) {
        cleanUp(inFile, outFile, in, out, nullptr, privateKey, false);
        delete [] my_ek;
        return false;
    }

    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cout << "Could not create cipher context" << endl;
        cleanUp(inFile, outFile, in, out, ctx, privateKey, false);
        delete [] my_ek;
        return false;
    }

    const EVP_CIPHER *cipher = EVP_get_cipherbynid(nid);
    if(!cipher) {
        cout << "Invalid cipher" << endl;
        cleanUp(inFile, outFile, in, out, ctx, privateKey, false);
        delete [] my_ek;
        return false;
    }

    //Initialize the decryption context
    if (EVP_OpenInit(ctx, cipher, my_ek, encKeyLen, iv.get(), privateKey) != 1) {
        cout << "Could not initialize decryption operation" << endl;
        cleanUp(inFile, outFile, in, out, ctx, privateKey, false);
        delete [] my_ek;
        return false;
    }

    if(!updateFinal(inFile, outFile, in, out, ctx, 'o')) {
        cleanUp(inFile, outFile, in, out, ctx, privateKey, false);
        delete [] my_ek;
        return false;
    }

    cleanUp(inFile, outFile, in, out, ctx, privateKey, true);
    delete [] my_ek;
    return true;
}


#ifndef __PROGTEST__

int main(void) {
    assert( seal("tests/fileToEncrypt.txt", "sealed.bin", "tests/PublicKey.pem", "aes-128-cbc") );
    assert( open("sealed.bin", "openedFileToEncrypt.txt", "tests/PrivateKey.pem") );

//    assert(open("tests/sealed_sample.bin", "opened_sample.txt", "tests/PrivateKey.pem"));

    return 0;
}

#endif /* __PROGTEST__ */

