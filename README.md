# Decipherer
Program that decrypts any length of Hamming code and Elias code. Translates text from an ASCII table.

## Hamming
The received text is packaged in separate packets of 15 characters. Each packet is checked for losses and if they are present, the losses are eliminated. Then all the defender bits are deleted. You can get separate clear packet.

### Hamming methods
string Hamming::get_packet(int index) - returns separate clear packet.
string Hamming::get_clear_text() - returns whole clear text.
void Hamming::write_detail_information() - displays detailed information about each package.

## Elias
The received text is separated by the gamma code rule and joins into a single line. 
Two vectors are created at runtime: <string> (not connected text after separated by the gamma code rule) and <int> (text with values from vector <string> in Base-10).
  
### Elias methods
void Elias::read() - reading a value.
string Elias::get_final_text() - returns decrypted text.
vector <string> Elias::get_format_str_text() - returns decrypted separeted text as string.
vector <int> Elias::get_format_int_text() - returns decrypted separeted text as int.

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
