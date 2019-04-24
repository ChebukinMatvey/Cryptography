# Cryptography 



## Content 
- Gost 
- Blowfish
- Des


## Usage 
```c++
// main.cpp
int main(int argc, char **argv) {
    generate(); // if you do not have 'info file '
    encrypt(); // encrypt 'text' file 
    decrypt(); // decrypt 'encrypted' file 
    return 0;
}    

// header.h
// global constants
const string THE_GOAL_FILE="../text";         // File to be encrypted   
const string MAIN_INFORMATION_FILE="../info"; // Main information file   
const string ENCRYPTED_FILE="../encrypted";   // Encrypted file 
const string DECRYPTED_FILE="../decrypted";   // Decrypted file 


// encrypt & decrypt 
cout<<"Count of rounds [1:32] = ";
cin >> ROUNDS_COUNT;   // parameter for encryption/decryption
```


## Done 

### Gost 
- [x] Java
- [x] C++
- [x] C#
- [x] Python

### Blowfish
- [x] Java
- [x] C++
- [X] C#
- [ ] Python