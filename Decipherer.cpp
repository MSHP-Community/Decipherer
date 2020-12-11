#include <Windows.h>
#undef max
#include <iostream>
#include <clocale>
#include <algorithm>
#include <limits>
#include <string>

#include "Hamming.h"
#include "Elias.h"
#include "Siberia.h"
#include "AES.h"
#include "ASCII.h"

using namespace std;

// For debug:
//
// Hamming test input : 111111011100111 001010111000000
// correct result :     1110110011111011000000
//
// Elias test input : 10100010011011010110010100100011101010010010111
// correct result : 0011110101011110010111110101111000111101
//
// ASCII test input : 1100001011100101111100001110110111101110
// correct result : Верно

// AES test input : :иуеьлнт куви ,п  С нгюшииьеболте х.еаетоеир рры д рв тт ллс а 
// correct result : Секрет: буратиновые угли тлеют дольше, если при них врать.

// Siberia test input : Кау кр К Ур Куа.а8Клл лур7 аы кл2Ррэн  Фканл.раиршу
// correct result : Карл у Клары украл экранку. Карл нарушил 278 УК РФ.

void unencrypt_ascii_text(vector <int> txt)
{
	cout << "Answer: \n";
	for (auto it = txt.begin(); it < txt.end(); ++it)
		cout << (char)((*it + 256) % 256);
	cout << endl;
}

void work_with_hamming(string text)
{
	Hamming code(text);
	string anws = code.get_clear_text();
	cout << "Answer: \n";
	cout << anws << endl;
}

void work_with_elias(string text)
{
	Elias code(text);
	string anws = code.get_final_text();
	cout << "Answer: \n";
	cout << anws << endl;
}

void work_with_siberia(wstring text)
{
	Siberia code(text);
	wstring anws = code.get_decrypted_text();
	cout << "Answer: \n";
	wcout << anws << endl;
}

void work_with_AES(wstring text, wstring key)
{
	Aes code(text, key);
	wstring anws = code.get_decrypted_text();
	cout << "Answer: \n";
	wcout << anws << endl;
}

bool work_with_ASCII(string text)
{
	int f = check_ASCII_input(text);
	if (!f)
		return false;
	if (f == 1)
		unencrypt_ascii_text(fromVStrToVInt(fromStrToVStr(text), 1));
	else
		unencrypt_ascii_text(fromVStrToVInt(fromStrToIntHexVStr(text), f));
	return true;
}



bool check_user_input(string& str) {
	str.erase(remove_if(str.begin(), str.end(), pred), str.end());

	for (auto& c : str)
		if (c != '0' && c != '1')
			return false;

	return true;
}

string user_text_input()
{
	string text;
	do {
		cout << "Write the encrypted text (format: \"01010100 0110100 001100101\"):\n";
		getline(cin, text);
		if (!check_user_input(text))
			cout << "Incorrect input text! Try again!\n";

	} while (!check_user_input(text));
	return text;
}

void user_input()
{
	string uin;
	cout << "Write the encoding type (Example: \"Hamming\"; \"all\" for output of all commands):\n";
	getline(cin, uin);
	for (int i = 0; i < uin.size(); ++i)
		uin[i] = toupper(uin[i]);

	if (uin == "ALL")
	{
		cout << "All Types:\n";
		cout << "\"Hamming\" - The received text is packaged in separate packets of 15 characters. Each packet is checked for losses and if they are present, the losses are eliminated. Then all the defender bits are deleted. You can get separate clear packet.\n\n";
		cout << "\"Elias\" - The received text is separated by the gamma code rule and joins into a single line. Two vectors are created at runtime: (not connected text after separated by the gamma code rule) and (text with values from vector in Base-10).\n\n";
		cout << "\"ASCII\" - Translates text from an ASCII table. The text can be in binary, decimal, or hexadecimal format.\n\n";
		cout << "\"Siberia\" - The received text is transferring to the format table. Then the text is read from the resulting table starting from the upper-left edge and filling in by diagonally.\n\n";
		cout << "\"AES\" - Entered text and key. The text is written to a table with a width equal to the length of the key and a height equal to the ratio of the length of the text to the length of the key. Then the columns are shuffled by key and the text from this table is returned.\n\n";
		cout << "\"cls\" - clear console\n\n";
		cout << "Write the encoding type or command:\n";
		getline(cin, uin);
	}
	if (uin == "HAMMING")
	{
		string text = user_text_input();
		work_with_hamming(text);
	}
	else if (uin == "ELIAS")
	{
		string text = user_text_input();
		work_with_elias(text);
	}
	else if (uin == "ASCII")
	{
		string text;
		cout << "Write the encrypted text (format: \"1100101 10101 101101\" or \"78 101 120 116\" or \"4C 75 63 6B\"):\n";
		bool success = true;
		do {
			if (!success)
				cout << "Incorrect input text! Try again!\n";

			getline(cin, text);
			success = work_with_ASCII(text);
		} while (!success);

	}
	else if (uin == "SIBERIA")
	{
		cout << "Write the encrypted text (format: \"very G00D\"):\n";
		wstring text;
		getline(wcin, text);
		work_with_siberia(text);
	}
	else if (uin == "AES")
	{
		cout << "Write the encrypted text (format: \"very G00D\"):\n";
		wstring text;
		getline(wcin, text);
		cout << "Write key (format: \"NICE\"):\n";
		wstring key;
		getline(wcin, key);
		for (int i = 0; i < (int)key.length(); ++i)
			key[i] = towupper(key[i]);
		work_with_AES(text, key);
	}
	else if (uin == "CLS")
		system("cls");
	else
	{
		cout << "Incorrect input! Try again!\n";
		user_input();
	}
}

bool check_continue(char s)
{
	s = toupper(s);
	if (s == 'Y' || s == 'N')
		return true;
	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool cont;
	do {
		user_input();
		char c;
		do {
			cout << "Do you want continue working? (Y / N)\n";
			cin.get(c);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (!check_continue(c));
		cont = (c == 'y' ? true : false);
	} while (cont);
}