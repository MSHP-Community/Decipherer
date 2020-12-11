#include "Aes.h"

Aes::Aes(std::wstring text, std::wstring key)
{
    this->text = text;
    this->key = key;
    textTable.resize(text.length() / key.length());
    decrypt();
}

std::wstring Aes::get_decrypted_text()
{
    return decryptedText;
}

void Aes::determineOrder()
{
    struct t
    {
        int num;
        wchar_t letter;
    };
    std::vector <t> v(key.length());
    for (int i = 0; i < (int)key.length(); ++i)
    {
        v[i].num = i;
        v[i].letter = key[i];
    }

    for (int i = 0; i < (int)key.length(); ++i)
        for (int j = 0; j < (int)key.length() - 1; ++j)
            if ((int)v[j].letter > (int)v[j + 1].letter)
                std::swap(v[j], v[j + 1]);

    for (auto& i : v)
        ordKey.push_back(i.num);
}

void Aes::decrypt()
{
    int n = 0;
    for (int i = 0; i < (int)key.length(); ++i)
        for (int j = 0; j < (int)text.length() / (int)key.length(); ++j)
            textTable[j].push_back(text[n++]);

    determineOrder();

    struct tmp
    {
        std::vector <wchar_t> row;
        int num = 0;
    };

    std::vector <tmp> t(key.length());
    for (int i = 0; i < (int)key.length(); ++i)
    {
        t[i].num = ordKey[i];
        std::vector <wchar_t> g;
        for (int j = 0; j < (int)text.length() / (int)key.length(); ++j)
            g.push_back(textTable[j][i]);
        t[i].row = g;
    }

    for (int i = 0; i < (int)key.length(); ++i)
        for (int j = 0; j < (int)key.length() - 1; ++j)
            if (t[j].num > t[j + 1].num)
                std::swap(t[j], t[j + 1]);

    sortTextTable = textTable;
    for (int i = 0; i < (int)key.length(); ++i)
        for (int j = 0; j < (int)text.length() / (int)key.length(); ++j)
            sortTextTable[j][i] = t[i].row[j];

    for (auto& i : sortTextTable)
        for (auto& j : i)
            decryptedText += j;
}
