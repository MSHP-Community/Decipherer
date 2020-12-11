#pragma once

#include <vector>
#include <string>

std::vector <int> fromVStrToVInt(std::vector <std::string> txt, int f);

std::vector <std::string> fromStrToIntHexVStr(std::string txt);

std::vector <std::string> fromStrToVStr(std::string txt);

bool pred(char x);

int check_ASCII_input(std::string& text);