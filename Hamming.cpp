#pragma once
#include <iostream>
#include <cstring>

#include "Hamming.h"
#include "HammingPacket.h"

Hamming::Hamming(std::string txt)
{
	int n;
	n = txt.size() / 15;

	std::vector <HammingPacket> t(txt.size() % 15 == 0 ? (n) : (n + 1));
	std::vector <HammingPacket>::iterator it = t.begin();

	int i = 0;
	for (; it < (txt.size() % 15 == 0 ? (t.end()) : (t.end() - 1)); ++it)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			s[j] = txt[i];
		}
		HammingPacket a(s);
		*it = a;
	}
	if (t.size() - n != 0)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			if (i < (int)txt.size())
			{
				s[j] = txt[n * 15 + j];
			}
			else
			{
				s[j] = '0';
			}
		}
		HammingPacket a(s);
		t[n] = a;
	}

	this->text = t;
}

std::string Hamming::get_packet(int index) // Âîçâðàùàåò êîïèþ HammingPacket èç âåêòîðà ïî èíäåêñó
{
	HammingPacket h = text.at(index);
	std::string str = h.clean_in_string();
	return str; // òîæå ñàìîå ÷òî return HammingPacket(text.at(index))
}

std::string Hamming::get_clear_text()
{
	std::string str;
	for (auto& h : text) {
		str += h.clean_in_string();
	}
	return str;
}

void Hamming::write_detail_information() // äîáàâèòü ðàçøèâðîâêó
{
	std::cout << "Total of " << this->text.size() << " elements:" << std::endl;
	int i = 1;
	for (int i = 0; i < (int)this->text.size(); ++i) {
		std::cout << i + 1 << " - " << this->text.at(i) << " : " << this->get_packet(i) << std::endl;
	}
	std::cout << std::endl;
}
