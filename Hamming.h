#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "HammingPacket.h"

class Hamming
{
public:
	Hamming(std::string txt);

	std::string get_packet(int index);
	std::string get_clear_text();
	void write_detail_information();

private:
	std::vector <HammingPacket> text;
	std::string clearText;
};