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


bool seal( const char * inFile, const char * outFile, const char * publicKeyFile, const char * symmetricCipher) {
    //Read the public key
    FILE* publicKey = fopen(publicKeyFile, "r");
    if (!publicKey) {
        cout << "Unable to open public key file." << endl;
        return false;
    }
    EVP_PKEY* pkey = PEM_read_PUBKEY(publicKey, NULL, NULL, NULL);
    if (!pkey) {
        cout << "Unable to read public key." << endl;
        fclose(publicKey);
        return false;
    }
    fclose(publicKey);

    //Generate a symmetric key
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (RAND_bytes(key, EVP_CIPHER_key_length(EVP_get_cipherbyname(symmetricCipher))) != 1 ||
        RAND_bytes(iv, EVP_CIPHER_iv_length(EVP_get_cipherbyname(symmetricCipher))) != 1) {
        cout << "Failed to generate random data." << endl;
        EVP_PKEY_free(pkey);
        return false;
    }

    //Encrypt the input file with the symmetric key
    FILE* inputFile = fopen(inFile, "rb");
    if (!inputFile) {
        cout << "Unable to open input file." << endl;
        EVP_PKEY_free(pkey);
        return false;
    }
    FILE* outputFile = fopen(outFile, "wb");
    if (!outputFile) {
        cout << "Unable to open output file." << endl;
        fclose(inputFile);
        EVP_PKEY_free(pkey);
        return false;
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx || EVP_EncryptInit_ex(ctx, EVP_get_cipherbyname(symmetricCipher), NULL, key, iv) != 1) {
        cout << "Unable to initialize encryption context." << endl;
        fclose(inputFile);
        fclose(outputFile);
        EVP_PKEY_free(pkey);
        return false;
    }
    unsigned char inbuf[BUFSIZ], outbuf[BUFSIZ + EVP_MAX_BLOCK_LENGTH];
    int outlen, tmplen;
    
    //Perform encryption
    while (!feof(inputFile)) {
        int len = fread(inbuf, 1, BUFSIZ, inputFile);
        if (len <= 0) {
            break;
        }
        if (EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, len) != 1) {
            cout << "Failed to encrypt data." << endl;
            fclose(inputFile);
            fclose(outputFile);
            EVP_PKEY_free(pkey);
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
        fwrite(outbuf, 1, outlen, outputFile);
    }

    if (EVP_EncryptFinal(ctx, outbuf, &outlen) != 1) {
        cout << "Failed to finalize encryption." << endl;
        fclose(inputFile);
        fclose(outputFile);
        EVP_PKEY_free(pkey);
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    fwrite(outbuf, 1, outlen, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    EVP_PKEY_free(pkey);
    EVP_CIPHER_CTX_free(ctx);
        
    return true;
}


bool open( const char * inFile, const char * outFile, const char * privateKeyFile)
{
    cout << "Control! open" << endl;
    
    return true;
}



#ifndef __PROGTEST__

int main ( void )
{
    assert( seal("fileToEncrypt", "sealed.bin", "tests/PublicKey.pem", "aes-128-cbc") );
    assert( open("sealed.bin", "openedFileToEncrypt", "tests/PrivateKey.pem") );

    assert( open("tests/sealed_sample.bin", "opened_sample.txt", "tests/PrivateKey.pem") );

    return 0;
}

#endif /* __PROGTEST__ */

