#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>

#include "Hamming.h"

using namespace std;

istream& operator>>(istream& in, vector<Hamming>& tmp) // inputs text with the Hamming encoding
{
	string str;
	getline(in, str);

	str.erase(remove_if(str.begin(), str.end(), not1(ptr_fun(isdigit))), str.end()); // deletes all non-digit symbols

	int n;
	n = str.size() / 15;

	vector <Hamming> t(str.size() % 15 == 0 ? (n) : (n + 1));
	vector <Hamming>::iterator it = t.begin();

	int i = 0;
	for (; it < (str.size() % 15 == 0 ? (t.end()) : (t.end() - 1)); ++it)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			s[j] = str[i];
		}
		Hamming a(s);
		*it = a;
	}
	if (t.size() - n != 0)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			if (i < (int)str.size())
			{
				s[j] = str[n * 15 + j];
			}
			else
			{
				s[j] = '0';
			}
		}
		Hamming a(s);
		t[n] = a;
	}

	tmp = t;

	return in;
}

ostream& operator<<(ostream& out, vector<Hamming>& tmp) // formatted text output in Hamming encoding
{
	cout << "Total of " << tmp.size() << " elements:" << endl;
	vector <Hamming>::iterator it;
	int i = 0;
	for (it = tmp.begin(); it < tmp.end(); ++it, ++i)
	{
		cout << i + 1 << " - " << *it << endl;
	}
	return out;
}

string get_Elias_text(vector <Hamming> text) // this function translates text from the Hamming encoding
{
	vector <Hamming>::iterator it;
	string str;
	for (it = text.begin(); it < text.end(); ++it)
	{
		str += (*it).clean_in_string();
	}
	return str;
}

int main()
{
	vector <Hamming> textWithHamming;
	cin >> textWithHamming;
	cout << textWithHamming;
	string text;
	text = get_Elias_text(textWithHamming);
	cout << text;
}