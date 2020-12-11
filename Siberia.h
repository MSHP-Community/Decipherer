#pragma once

#include <vector>
#include <string>

class Siberia
{
public:
	Siberia(std::wstring str);

	std::wstring get_encrypted_text();
	std::vector <int> get_encrypted_int_text();

	std::wstring get_decrypted_text();
	std::vector <int> get_decrypted_int_text();

private:
	std::wstring clearText;
	int rows;

	std::vector <std::vector <int>> encryptedTable;
	std::vector <int> encryrtedIntText;
	std::wstring encryptedText;

	std::vector <std::vector <int>> decryptedTable;
	std::vector <int> decryptedIntText;
	std::wstring decryptedText;

	int find_size(int n);

	void encrypt();
	void encrypt_text();
	void encrypt_int_text();

	void decrypt();
	void decrypt_int_text();
};