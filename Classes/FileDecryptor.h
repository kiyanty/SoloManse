#pragma once

// ������ ��ȣȭ
class FileDecryptor
{
private:
	unsigned char key1, key2;

public:
	FileDecryptor(const unsigned char key1, const unsigned char key2);
	void Decrypt(char* arr, const int size);

private:
	void DecryptFunc(const unsigned char key, char* byte);
};