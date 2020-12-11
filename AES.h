#pragma once

#include <vector>
#include <string>

class Aes
{
public:
	Aes(std::wstring text, std::wstring key);

	std::wstring get_decrypted_text();

private:
	std::wstring text;
	std::wstring key;
	std::vector <int> ordKey;
	std::vector <std::vector <wchar_t>> textTable;
	std::vector <std::vector <wchar_t>> sortTextTable;
	std::wstring decryptedText;

	void determineOrder();
	void decrypt();
};
