#include "Siberia.h"

Siberia::Siberia(std::wstring str)
{
    clearText = str;
    rows = find_size(str.length());

    encryptedTable.resize(rows);
    encrypt();
    encrypt_text();
    encrypt_int_text();

    decryptedTable.resize(rows);
    decrypt();
}

std::wstring Siberia::get_encrypted_text()
{
    return encryptedText;
}

std::vector<int> Siberia::get_encrypted_int_text()
{
    return encryrtedIntText;
}

std::wstring Siberia::get_decrypted_text()
{
    return decryptedText;
}

std::vector<int> Siberia::get_decrypted_int_text()
{
    return decryptedIntText;
}

int Siberia::find_size(int n)
{
    int count = 0;
    int tn = 1, tmp = 0;
    while (n > tmp)
    {
        count = tn;
        if (tn % 2 == 0)
            tmp = tn * (tn + 1) / 2;
        else
            tmp = (tn - 1) * tn / 2 + 1;
        tn++;
    }
    return count;
}

void Siberia::encrypt()
{
    int n = clearText.size();
    int i = 0;
    int j = 1;
    int count = 1;
    bool flag = true, first = true, rl = false;
    encryptedTable[0].push_back((int)clearText[0]);
    while (flag)
    {
        if (first)
        {
            encryptedTable[i].push_back((int)clearText[count++]);
            ++i;
            --j;
            if (n == count)
                flag = false;
            else
                encryptedTable[i].push_back((int)clearText[count++]);
            first = false;
        }
        else if (!i && rl)
        {
            ++j;
            encryptedTable[i].push_back((int)clearText[count++]);
            rl = false;
            if (n == count)
                flag = false;
        }
        else if (!j && !rl)
        {
            ++i;
            encryptedTable[i].push_back((int)clearText[count++]);
            rl = true;
            if (n == count)
                flag = false;
        }
        else if (!j)
        {
            do {
                --i;
                ++j;
                encryptedTable[i].push_back((int)clearText[count++]);
                if (n == count)
                    flag = false;
            } while (i && flag);
        }
        else if (!i)
        {
            do {
                --j;
                ++i;
                encryptedTable[i].push_back((int)clearText[count++]);
                if (n == count)
                    flag = false;
            } while (j && flag);
        }
    }
}

void Siberia::encrypt_text()
{
    std::wstring str = {};
    for (int i = 0; i < (int)encryptedTable.size(); ++i)
        for (int j = 0; j < (int)encryptedTable[i].size(); ++j)
            str += (wchar_t)encryptedTable[i][j];

    encryptedText = str;
}

void Siberia::encrypt_int_text()
{
    for (int i = 0; i < (int)encryptedTable.size(); ++i)
        for (int j = 0; j < (int)encryptedTable[i].size(); ++j)
            encryrtedIntText.push_back(encryptedTable[i][j]);
}

void Siberia::decrypt()
{
    int n = 0;
    for (int i = 0; i < encryptedTable.size(); ++i)
        for (int j = 0; j < encryptedTable[i].size(); ++j)
            decryptedTable[i].push_back(clearText[n++]);

    n = clearText.size();
    std::wstring str = {};
    int i = 0;
    int j = 1;
    int count = 2;
    bool flag = true, first = true, rl = false;
    str += decryptedTable[0][0];
    while (flag)
    {
        if (first)
        {
            str += decryptedTable[i][j];
            count++;
            ++i;
            --j;
            if (n == count)
                flag = false;
            else
                str += decryptedTable[i][j];
            first = false;
        }
        else if (!i && rl)
        {
            ++j;
            count++;
            rl = false;
            if (n == count)
                flag = false;
            str += decryptedTable[i][j];
        }
        else if (!j && !rl)
        {
            ++i;
            count++;
            rl = true;
            if (n == count)
                flag = false;
            str += decryptedTable[i][j];
        }
        else if (!j)
        {
            do {
                --i;
                ++j;
                count++;
                if (n == count)
                    flag = false;
                str += decryptedTable[i][j];
            } while (i && flag);
        }
        else if (!i)
        {
            do {
                --j;
                ++i;
                count++;
                if (n == count)
                    flag = false;
                str += decryptedTable[i][j];
            } while (j && flag);
        }
    }

    decryptedText = str;
}

void Siberia::decrypt_int_text()
{
    for (int i = 0; i < decryptedText.length(); ++i)
        decryptedIntText[i] = (int)decryptedText[i];
}