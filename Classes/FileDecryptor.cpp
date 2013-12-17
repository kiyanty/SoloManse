#include "FileDecryptor.h"

FileDecryptor::FileDecryptor(const unsigned char key1, const unsigned char key2)
	:key1(key1), key2(key2)
{

}

void FileDecryptor::Decrypt(char* arr, const int size)
{
	for (int i=0; i<size; i++)
	{
		DecryptFunc(key1, &arr[i]);
		DecryptFunc(key1, &arr[i]);
		DecryptFunc(key2, &arr[i]);
	}
}


void FileDecryptor::DecryptFunc(const unsigned char key, char* byte)
{
	char temp_char = *byte;

	// reverse
	*byte = 0;
	for (int i=0; i<8; i++)
	{
		*byte <<= 1;
		*byte |= temp_char & 0x01;
		temp_char >>= 1;
	}

	// xor
	*byte ^= key;
}