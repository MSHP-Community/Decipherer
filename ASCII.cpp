#include "ASCII.h"

std::vector <int> fromVStrToVInt(std::vector <std::string> txt, int f)
{
	std::vector <int> v;
	v.resize(txt.size());
	auto iti = v.begin();
	for (auto its = txt.begin(); its < txt.end(); ++its, ++iti)
		*iti = stoi(*its, nullptr, (f == 1 ? 2 : (f == 2 ? 10 : 16)));
	return v;
}

std::vector <std::string> fromStrToIntHexVStr(std::string txt)
{
	std::vector <std::string> v;
	int n = 0;
	std::string s = {};
	do {
		while (txt[n] != ' ' && n + 1 <= txt.length())
			s += txt[n++];

		v.push_back(s);
		s = {};
		n++;
	} while (n + 1 <= txt.length());
	return v;
}

std::vector <std::string> fromStrToVStr(std::string txt)
{
	txt.erase(remove_if(txt.begin(), txt.end(), pred), txt.end());
	std::vector <std::string> v;
	int n = txt.size() / 8;
	std::string s(txt);
	while (s.size() % 8 != 0)
		s.insert(s.size() - 1, "0");

	for (int i = 0; i < n; ++i)
	{
		std::string str(s, 0, 8);
		int t = stoi(str);
		s.erase(0, 8);
		v.push_back(str);
	}
	return v;
}

bool pred(char x)
{
	return (x == ' ' ? true : false);
}

int check_ASCII_input(std::string& text)
{
	for (auto& i : text)
		if (!isdigit(i) && toupper(i) != 'A' && toupper(i) != 'B' && toupper(i) != 'C' && toupper(i) != 'D' && toupper(i) != 'E' && toupper(i) != 'F' && i != ' ')
			return 0;

	bool flag = true;
	for (auto& i : text)
		if (i != '0' && i != '1' && i != ' ')
			flag = false;

	if (flag)
	{
		text.erase(remove_if(text.begin(), text.end(), pred), text.end());
		return 1;
	}
	else
	{
		for (auto& i : text)
			if (toupper(i) == 'A' || toupper(i) == 'B' || toupper(i) == 'C' || toupper(i) == 'D' || toupper(i) == 'E' || toupper(i) == 'F')
				return 3;
	}
	return 2;
}
