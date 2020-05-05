#include "Elias.h"

Elias::Elias()
{
    text = "";
}

Elias::Elias(std::string txt)
{
	this->text = txt;
	firstBit = txt[0];
	clean();
}

void Elias::read()
{
    std::string s;
    std::cin >> s;
    auto n = s.find_first_of(' ');
    do {
        s.erase(n, 1);
        auto n = s.find_first_of(' ');
    } while (n != std::string::npos);
    Elias t(s);
    *(this) = t;
}

std::string Elias::get_final_text()
{
    return finalText;
}

std::vector<std::string> Elias::get_format_str_text()
{
    return formatStrText;
}

std::vector<int> Elias::get_format_int_text()
{
    return formatIntText;
}

Elias& Elias::operator=(Elias& tmp)
{
    this->text = tmp.text;
    this->finalText = tmp.finalText;
    this->formatStrText = tmp.formatStrText;
    this->formatIntText = tmp.formatIntText;
    this->firstBit = tmp.firstBit;
    this->intermediateStrValue = tmp.intermediateStrValue;
    this->intermediateIntValue = tmp.intermediateIntValue;
    return *(this);
}

void Elias::out()
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "text: " << text << std::endl;
    std::cout << "firstBit: " << firstBit << std::endl;
    std::cout << "intermediateStrValue: ";
    for (auto it = intermediateStrValue.begin(); it < intermediateStrValue.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "intermediateIntValue: ";
    for (auto it = intermediateIntValue.begin(); it < intermediateIntValue.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "formatStrText: ";
    for (auto it = formatStrText.begin(); it < formatStrText.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "formatIntText: ";
    for (auto it = formatIntText.begin(); it < formatIntText.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl << std::endl;
}

void Elias::clean()
{
    separation();
    createIntValue();
    createFinal();
    finalSeparation();
}

void Elias::createFinal()
{
    std::string txt;
    bool num = (firstBit == '1' ? true : false);
    for (auto it = intermediateIntValue.begin(); it < intermediateIntValue.end(); ++it)
    {
        for (int j = 0; j < *it; ++j)
        {
            txt += (num ? '1' : '0');
        }
        num = (num ? false : true);
    }
    finalText = txt;
}

void Elias::separation()
{
	std::string txt = text;
	txt.erase(0, 1);
	int count = 0;

    while (txt.size())
    {
        if (txt[0] == '1')
        {
            std::string t = "1";
            intermediateStrValue.push_back(t);
            txt.erase(0, 1);
        }
        else
        {
            int j = 0, count = 1;
            while (txt[j + 1] == '0' && j < (int)txt.size())
            {
                ++count;
                ++j;
            }
            std::string t(txt, 0, count * 2 + 1);
            intermediateStrValue.push_back(t);
            txt.erase(0, count * 2 + 1);
        }
    }
    
    for (auto it = intermediateStrValue.begin(); it < intermediateStrValue.end(); ++it)
    {
        std::string txt = *it;
        txt.erase(0, (txt.size() - 1) / 2);
        *it = txt;
    }
}

void Elias::finalSeparation()
{
    int n = finalText.size() / 8;
    std::string s(finalText);
    while (s.size() % 8 != 0)
    {
        s.insert(s.size() - 1, "0");
    }
    for (int i = 0; i < n; ++i)
    {
        std::string str(s, 0, 8);
        int t = to_int(str);
        s.erase(0, 8);
        formatStrText.push_back(str);
        formatIntText.push_back(t);
    }
}

void Elias::createIntValue()
{
    intermediateIntValue.resize(intermediateStrValue.size());
    int i = 0;
    for (auto it = intermediateStrValue.begin(); it < intermediateStrValue.end(); ++it, ++i)
    {
        std::string txt = *it;
        intermediateIntValue[i] = to_int(txt);
    }
}

int Elias::to_int(std::string txt) // convert from Base-2 to Base-10 for char with 4 symbols (use for recovery of losses)
{
    int count = 0, n = 1;

    for (int i = txt.size() - 1; i >= 0; --i)
    {
        if (txt[i] == '1')
            count += n;
        n *= 2;
    }

    return count;
}