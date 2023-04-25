#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

struct crypto_config
{
	const char * m_crypto_function;
	std::unique_ptr<uint8_t[]> m_key;
	std::unique_ptr<uint8_t[]> m_IV;
	size_t m_key_len;
	size_t m_IV_len;
};

#endif /* _PROGTEST_ */

#define K_BUFFER_SIZE 4096

bool controlTgaFile(const std::string & filename) {

    ifstream inFile(filename, ios::binary);
    if(!inFile.is_open()) {
        cout << "Can't open file " << filename << endl;
        return false;
    }

    // Check file size
    inFile.seekg(0, ios::end);
    int fileSize = inFile.tellg();
    if(fileSize < 18) {
        cout << "File " << filename << " is too small to be a TGA file" << endl;
        inFile.close();
        return false;
    }
    inFile.seekg(0, ios::beg);

    //Check TGA header
    char headerFile[18];
    inFile.read(headerFile, sizeof(headerFile));
    if(!inFile.good()) {
        cout << "Can't reading TGA header from file " << filename << endl;
        inFile.close();
        return false;
    }

    inFile.close();
    return true;
}

bool controlIvCipher(crypto_config & config, const char & type) {
    if(config.m_crypto_function == nullptr) {
        cout << "Invalid crypto_config parameter" << endl;
        return false;
    }

    const EVP_CIPHER *cipher = EVP_get_cipherbyname(config.m_crypto_function);
    if(cipher == nullptr) {
        cout << "Unknown cipher name" << endl;
        return false;
    }

    size_t key_len = EVP_CIPHER_key_length(cipher);
    size_t IV_len = EVP_CIPHER_iv_length(cipher);

    //Check if key is provided
    if(config.m_key == nullptr || config.m_key_len < key_len) {
        if(type == 'e') {
            //Generate a new key and store it in config
            config.m_key = make_unique<uint8_t[]>(key_len);
            if (!RAND_bytes(config.m_key.get(), key_len)) {
                cout << "Failed to generate random key" << endl;
                return false;
            }
        } else {
            return false;
        }
        config.m_key_len = key_len;
    }

    //Check if IV is provided
    if(IV_len > 0 && (config.m_IV == nullptr || config.m_IV_len < IV_len)) {
        if(type == 'e') {
            config.m_IV = make_unique<uint8_t[]>(IV_len);
            if(!RAND_bytes(config.m_IV.get(), IV_len)) {
                cout << "Failed to generate random IV" << endl;
                return false;
            }
        } else {
            return false;
        }
        config.m_IV_len = IV_len;
    }
    return true;
}

bool dataInitialization(const string & in_filename, const string & out_filename, crypto_config & config, ifstream & inFile, ofstream & outFile, const char & type) {
    //Control TGA header and format of file
    if(!controlTgaFile(in_filename)) {
        cout << "Bad TGA file" << endl;
        return false;
    }

    if (!inFile.is_open()) {
        cout << "Filed to open input file " << in_filename << endl;
        return false;
    }

    if(!outFile.is_open()) {
        cout << "Failed to open output file " << out_filename << endl;
        return false;
    }

    //Read TGA header from input file and write it to output file
    char header[18];
    inFile.read(header, 18);
    outFile.write(header, 18);
    if(!outFile.good()) {
        cout << "Can't writting TGA header to file " << out_filename << endl;
        outFile.close();
        return false;
    }

    //If block cipher requires an IV
    if(!controlIvCipher(config, type)) {
        return false;
    }
    return true;
}

bool dataEncryptOrDecrypt(const string & in_filename, const string & out_filename, crypto_config & config, ifstream & inFile, ofstream & outFile, const char & type) {
    //Prepare the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx) {
        cout << "Failed to create OpenSSL cipher context" << std::endl;
        return false;
    }

    if(type == 'e') {
        if(EVP_EncryptInit_ex(ctx, EVP_get_cipherbyname(config.m_crypto_function), nullptr, config.m_key.get(), config.m_IV.get()) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
    } else {
        if (EVP_DecryptInit_ex(ctx, EVP_get_cipherbyname(config.m_crypto_function), nullptr, config.m_key.get(),
                               config.m_IV.get()) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
    }

    //Prepare buffer for input data and decrypted output data
    unsigned char in_buffer[K_BUFFER_SIZE];
    unsigned char out_buffer[K_BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int out_length = 0;

    //Read data from the input file, decrypt it using the EVP_DecryptUpdate function, and write it to the output file
    while (inFile.good()) {
        inFile.read(reinterpret_cast<char*>(in_buffer), K_BUFFER_SIZE);
        int in_length = (int)(inFile.gcount());
        if(type == 'e') {
            if (EVP_EncryptUpdate(ctx, out_buffer, &out_length, in_buffer, in_length) != 1) {
                cout << "Failed to encrypt data" << endl;
                EVP_CIPHER_CTX_free(ctx);
                return false;
            }
        } else {
            if (EVP_DecryptUpdate(ctx, out_buffer, &out_length, in_buffer, in_length) != 1) {
                cout << "Failed to decrypt data" << endl;
                EVP_CIPHER_CTX_free(ctx);
                return false;
            }
        }

        outFile.write(reinterpret_cast<char*>(out_buffer), out_length);
        if(!outFile.good()) {
            cout << "Can't writting TGA header to file " << out_filename << endl;
            outFile.close();
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
    }

    //Finalize the decryption context using the EVP_DecryptFinal_ex function
    if(type == 'e') {
        if (EVP_EncryptFinal_ex(ctx, out_buffer, &out_length) != 1) {
            cout << "Failed to finalize OpenSSL cipher context" << endl;
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
    } else {
        if (EVP_DecryptFinal_ex(ctx, out_buffer, &out_length) != 1) {
            cout << "Failed to finalize OpenSSL cipher context" << endl;
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
    }

    //Write the final block of decrypted data to the output file
    outFile.write(reinterpret_cast<char*>(out_buffer), out_length);
    if(!outFile.good()) {
        cout << "Can't writting TGA header to file " << out_filename << endl;
        outFile.close();
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool encrypt_data (const string & in_filename, const string & out_filename, crypto_config & config) {

    ifstream inFile(in_filename, ios::binary);
    ofstream outFile(out_filename, ios::binary | ios::trunc);

    //Prepairing data for working and passage through the first checks
    if(!dataInitialization(in_filename, out_filename, config, inFile, outFile, 'e')) {
        return false;
    }

    //Encrypt picture
    if(!dataEncryptOrDecrypt(in_filename, out_filename, config, inFile, outFile, 'e')) {
        return false;
    }

    return true;
}

bool decrypt_data  (const string & in_filename, const string & out_filename, crypto_config & config) {

    ifstream inFile(in_filename, ios::binary);
    ofstream outFile(out_filename, ios::binary | ios::trunc);

    //Prepairing data for working and passage through the first checks
    if(!dataInitialization(in_filename, out_filename, config, inFile, outFile, 'd')) {
        return false;
    }

    //Decrypt picture
    if(!dataEncryptOrDecrypt(in_filename, out_filename, config, inFile, outFile, 'd')) {
        return false;
    }

    return true;
}

#ifndef __PROGTEST__

bool compare_files ( const char * name1, const char * name2 ) {

    ifstream  inFile1(name1, ios::binary | ios::ate);
    ifstream  inFile2(name2, ios::binary | ios::ate);

    if(!inFile1 || !inFile2) {
        cout << "Failed to open file in compare file!" << endl;
        return false;
    }

    //Check equals size
    if(inFile1.tellg() != inFile2.tellg()) {
        cout << "Files have different size" << endl;
        return false;
    }

    inFile1.seekg(0, ios::beg);
    inFile2.seekg(0, ios::beg);

    if(!equal(istreambuf_iterator<char>(inFile1.rdbuf()),
              istreambuf_iterator<char>(),
              istreambuf_iterator<char>(inFile2.rdbuf()))) {
        cout << "Files are not equal!" << endl;
        return false;
    }

    return true;
}

int main ( void )
{
	crypto_config config {nullptr, nullptr, nullptr, 0, 0};

	// ECB mode
	config.m_crypto_function = "AES-128-ECB";
	config.m_key = std::make_unique<uint8_t[]>(16);
 	memset(config.m_key.get(), 0, 16);
	config.m_key_len = 16;

	assert( encrypt_data  ("tests/homer-simpson.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/homer-simpson_enc_ecb.TGA") );

	assert( decrypt_data  ("tests/homer-simpson_enc_ecb.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/homer-simpson.TGA") );

	assert( encrypt_data  ("tests/UCM8.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/UCM8_enc_ecb.TGA") );

	assert( decrypt_data  ("tests/UCM8_enc_ecb.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/UCM8.TGA") );

	assert( encrypt_data  ("tests/image_1.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/ref_1_enc_ecb.TGA") );

	assert( encrypt_data  ("tests/image_2.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/ref_2_enc_ecb.TGA") );

	assert( decrypt_data ("tests/image_3_enc_ecb.TGA", "tests/out_file.TGA", config)  &&
		    compare_files("tests/out_file.TGA", "tests/ref_3_dec_ecb.TGA") );

	assert( decrypt_data ("tests/image_4_enc_ecb.TGA", "tests/out_file.TGA", config)  &&
		    compare_files("tests/out_file.TGA", "tests/ref_4_dec_ecb.TGA") );

	// CBC mode
	config.m_crypto_function = "AES-128-CBC";
	config.m_IV = std::make_unique<uint8_t[]>(16);
	config.m_IV_len = 16;
	memset(config.m_IV.get(), 0, 16);

	assert( encrypt_data  ("tests/UCM8.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/UCM8_enc_cbc.TGA") );

	assert( decrypt_data  ("tests/UCM8_enc_cbc.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/UCM8.TGA") );

	assert( encrypt_data  ("tests/homer-simpson.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/homer-simpson_enc_cbc.TGA") );

	assert( decrypt_data  ("tests/homer-simpson_enc_cbc.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/homer-simpson.TGA") );

	assert( encrypt_data  ("tests/image_1.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/ref_5_enc_cbc.TGA") );

	assert( encrypt_data  ("tests/image_2.TGA", "tests/out_file.TGA", config) &&
			compare_files ("tests/out_file.TGA", "tests/ref_6_enc_cbc.TGA") );

	assert( decrypt_data ("tests/image_7_enc_cbc.TGA", "tests/out_file.TGA", config)  &&
		    compare_files("tests/out_file.TGA", "tests/ref_7_dec_cbc.TGA") );

	assert( decrypt_data ("tests/image_8_enc_cbc.TGA", "tests/out_file.TGA", config)  &&
		    compare_files("tests/out_file.TGA", "tests/ref_8_dec_cbc.TGA") );
	return 0;
}

#endif /* _PROGTEST_ */
