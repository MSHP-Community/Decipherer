#pragma once

#include <string>

class Hamming // class
{
public:
    Hamming(); // create object with value = 0
    Hamming(char* s); // create object from value = char[16] and cleaars it

    int clean_in_int(); // return clean recovery packet in int
    std::string clean_in_string(); // return clean recovery packet in string

    friend std::istream& operator >>(std::istream& in, Hamming& tmp); // enters value
    friend std::ostream& operator <<(std::ostream& out, Hamming& tmp); // outputs a primordial package

private:

    class Binary // nested class that stored packets
    {
    public:
        Binary(); // create object with value = 0
        Binary(int value); // create object from value = int
        Binary(char* s); // create object from value = char[16]

        bool& at(int index); // provide access
        void read(); // enters value
        void write() const; // outputs value

        Binary& operator +(Binary& tmp); // the addition of two of the packages as mathematical objects (not used)
        Binary& operator -(Binary& tmp); // subtraction of two of the packages as mathematical objects (not used)
        Binary& operator *(Binary& tmp); // multiplication of two of the packages as mathematical objects (not used)
        Binary& operator /(Binary& tmp); // division of two of the packages as mathematical objects (not used)
        Binary& operator =(Binary& tmp); // assignment overload

    private:
        bool data[15] = {}; // the package is stored

        int to_bin(int value) const; // convert from Base-10 to Base-2
        int to_int() const; // convert from Base-2 to Base-10
    };

    Binary fullSection; // the original packet is stored here
    Binary firstClean; // the original pocket after recovery
    int finalCleanInt; // a clean restored packet with no security bits in int
    std::string finalCleanString; // a clean restored packet with no security bits in string

    template <typename T>
    int to_int(T* s) const; // convert from Base-2 to Base-10 (used for recovery of losses and translating a clean recovery package)
    long long to_bin(long long value) const; // convert from Base-10 to Base-2 (not used)

    int first_check(); // checking for the first defender bit, return 1 or 0
    int second_check(); // checking for the second defender bit, return 1 or 0
    int third_check(); // checking for the third defender bit, return 1 or 0
    int fourth_check(); // checking for the fourth defender bit, return 1 or 0

    void clean(); // the main method that calculates the error using the check() method is fixed and defines the package without protection
    int check(); // the method that find error using first_check(), second_check(), third_check(), fourth_check(), return error number in Base-2
    void delete_excess(Binary section); // the method that delete protecting bits
};

