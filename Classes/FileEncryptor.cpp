#include "FileEncryptor.h"

// #define _CRT_RAND_S

#include <stdlib.h>
#include <time.h>

FileEncryptor::FileEncryptor()
{
//	unsigned int randnum;
    srand(unsigned(time(NULL)));
    key1 = rand() % 256;
    key2 = rand() % 256;
//	rand_r(&randnum); key1 = randnum & 0xff;
//	rand_r(&randnum); key2 = randnum & 0xff;
}

void FileEncryptor::Encrypt(char* arr, const int size)
{
	for (int i=0; i<size; i++)
	{
		EncryptFunc(key2, &arr[i]);
		EncryptFunc(key1, &arr[i]);
		EncryptFunc(key1, &arr[i]);
	}
}


void FileEncryptor::GetKey(char* out)
{
	out[0] = key1;
	out[1] = key2;
}


void FileEncryptor::EncryptFunc(const unsigned char key, char* byte)
{
	char temp_char = *byte;

	// xor
	temp_char ^= key;

	// reverse
	*byte = 0;
	for (int i=0; i<8; i++)
	{
		*byte <<= 1;
		*byte |= temp_char & 0x01;
		temp_char >>= 1;
	}
}