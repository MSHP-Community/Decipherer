# Decipherer
Program that decrypts any length of Hamming code into Elias code. The received value is packaged in separate packets of 15 characters. Each packet is checked for losses and if they are present, the losses are eliminated. Then all the defender bits are deleted.

# Download
```bash
git clone https://github.com/MSHP-Community/Decipherer
git clona https://github.com/NikKrasavchik/Decipherer
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
