#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

class Elias
{
public:
	Elias();
	Elias(std::string txt);

	void read();

	std::string get_final_text();
	std::vector <std::string> get_format_str_text();
	std::vector <int> get_format_int_text();

	Elias& operator=(Elias& tmp);

private:
	std::string text;
	std::string finalText;
	std::vector <std::string> formatStrText;
	std::vector <int> formatIntText;
	char firstBit;
	std::vector <std::string> intermediateStrValue;
	std::vector <int> intermediateIntValue;

	int to_int(std::string txt);

	void clean();
	void separation();
	void createFinal();
	void finalSeparation();
	void createIntValue();

	void out();
};

