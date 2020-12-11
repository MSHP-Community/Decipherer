# Decipherer
Program that decrypts any length of Hamming code and Elias code. Translates text from an ASCII table.

## Hamming
The received text is packaged in separate packets of 15 characters. Each packet is checked for losses and if they are present, the losses are eliminated. Then all the defender bits are deleted. You can get separate clear packet.

### Hamming methods
```c++
string Hamming::get_packet(int index); // returns separate clear packet.
string Hamming::get_clear_text(); // returns whole clear text.
void Hamming::write_detail_information(); // displays detailed information about each package.
```

## Elias
The received text is separated by the gamma code rule and joins into a single line. 
Two vectors are created at runtime: <string> (not connected text after separated by the gamma code rule) and <int> (text with values from vector <string> in Base-10).
  
### Elias methods
```c++
void Elias::read(); // reading a value.
string Elias::get_final_text(); // returns decrypted text.
vector <string> Elias::get_format_str_text(); // returns decrypted separeted text as string.
vector <int> Elias::get_format_int_text(); // returns decrypted separeted text as int.
```
## ASCII
Translates text from an ASCII table. Enter a binary, decimal, or hexadecimal number.

## Siberia
The received text is transferring to the format table. Then the text is read from the resulting table starting from the upper-left edge and filling in by diagonally. 

### Siberia methods
```c++
std::wstring get_decrypted_text(); // returns decrypted text.
	std::vector <int> get_decrypted_int_text(); // returns decrypted text character by character.
```

## AES
Entered text and key. The text is written to a table with a width equal to the length of the key and a height equal to the ratio of the length of the text to the length of the key. Then the columns are shuffled by key and the text from this table is returned.

### AES methods
```c++
std::wstring get_decrypted_text(); // returns decrypted text.
```

# Download
```bash
git clone https://github.com/NikKrasavchik/Decipherer
```

# Build
```bash
cd Decipherer
cmake .
make
```

# Permission
```bash
chmod +x ./run
```

# Usage
```bash
./run
```