#pragma once

class FileEncryptor
{
private:
	unsigned char key1, key2;

public:
	FileEncryptor();
	void Encrypt(char* arr, const int size);

	void GetKey(char* out);

private:
	void EncryptFunc(const unsigned char key, char* byte);
};
