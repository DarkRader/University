#ifndef __PROGTEST__
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

#endif /* __PROGTEST__ */

using namespace std;

#define MESSANGE_SIZE 64 // SHA-512 outputs 64 bytes (512 bits)

bool calculateHash(const unsigned char *messageData, unsigned char *hashData) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        return false;
    }

    if (!EVP_DigestInit_ex(ctx, EVP_sha512(), NULL)) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (!EVP_DigestUpdate(ctx, messageData, MESSANGE_SIZE)) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (!EVP_DigestFinal_ex(ctx, hashData, NULL)) {
        EVP_MD_CTX_free(ctx);
        return false;
    }

    EVP_MD_CTX_free(ctx);
    return true;
}

int findHash (int bits, char ** message, char ** hash) {
    //Check input parameters
    if(bits < 0 || bits > 512) {
        return 0;
    }

    unsigned char * messageData = (unsigned char*) malloc(64 * sizeof(unsigned char));

    // check if message is provided
    if(!messageData) {
        free(messageData);
        return 0;
    }

    // prepare a random message
    if (RAND_bytes(messageData, MESSANGE_SIZE) != 1) {
        free(messageData);
        return 0;
    }

    // hash the message until the required number of bits is achieved
    while (true) {
        //Init data
        unsigned char hashData[MESSANGE_SIZE];
        if(calculateHash(messageData, hashData) == false) {
            free(messageData);
            return 0;
        }

        //The variable bytesToCheck is calculated as the number of bytes to check for a given number of bits
        const int bytesToCheck = (bits + 7) / 8;
        bool found = true;
        for (int i = 0; i < bytesToCheck; ++i) {
            if (hashData[i] != 0) {
                found = false;
                break;
            }
        }

        //Converts a byte array to a hexadecimal string.
        if (found) {
            char * hashStr = (char *) malloc(129);
            for (int i = 0; i < MESSANGE_SIZE; ++i) {
                snprintf(hashStr + 2 * i, 3, "%02x", hashData[i]);
            }
            hashStr[128] = '\0';
            *hash = hashStr;

            char * messageStr = (char *) malloc(129);
            for (int i = 0; i < MESSANGE_SIZE; ++i) {
                snprintf(messageStr + 2 * i, 3, "%02x", messageData[i]);
            }
            messageStr[128] = '\0';
            *message = messageStr;

            free(messageData);
            return 1;
        }

        for (int i = 0; i < MESSANGE_SIZE; ++i) {
            messageData[i] = hashData[i % 64];
        }
    }
}

int findHashEx (int bits, char ** message, char ** hash, const char * hashFunction) {
    /* TODO or use dummy implementation */
    return 1;
}

#ifndef __PROGTEST__

int checkHash(int bits, char * hexString) {
    int bytes;
    if (bits % 8 == 0) {
        bytes = bits / 8;
    } else {
        bytes = bits / 8 + 1;
    }

    char *hash = new char[bytes];
    for (int i = 0; i < bytes; i++) {
        hash[i] = 0;
    }

    for (int i = 0; i < bytes * 2; i += 2) {
        char c1 = hexString[i];
        char c2 = hexString[i + 1];
        uint8_t byte = 0;
        if (isdigit(c1)) {
            byte = c1 - '0';
        } else {
            byte = 10 + (tolower(c1) - 'a');
        }

        byte = byte * 16;
        if (isdigit(c2)) {
            byte = c2 - '0';
        } else {
            byte = 10 + (tolower(c2) - 'a');
        }
        hash[i / 2] = byte;
    }
    int result = 1;

    for (int i = 0; i < bits; i++) {
        if (hash[i / 8] & (1 << (7 - i % 8))) {
            result = 0;
            break;
        }
    }

    delete[] hash;
    return result;
}

int main (void) {
    char * message, * hash;
    assert(findHash(0, &message, &hash) == 1);
    assert(message && hash && checkHash(0, hash));
    free(message);
    free(hash);
    assert(findHash(1, &message, &hash) == 1);
    assert(message && hash && checkHash(1, hash));
    free(message);
    free(hash);
    assert(findHash(2, &message, &hash) == 1);
    assert(message && hash && checkHash(2, hash));
    free(message);
    free(hash);
    assert(findHash(3, &message, &hash) == 1);
    assert(message && hash && checkHash(3, hash));
    free(message);
    free(hash);
    assert(findHash(-1, &message, &hash) == 0);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

