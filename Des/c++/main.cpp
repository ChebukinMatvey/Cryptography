#include "header.h"

string THE_GOAL_FILE = "./text";
string MAIN_INFORMATION_FILE="./info";
string ENCRYPTED_FILE="./encrypted";
string DECRYPTED_FILE="./decrypted";

int main() {
    generate(&MAIN_INFORMATION_FILE);
    encrypt(&THE_GOAL_FILE,&MAIN_INFORMATION_FILE,&ENCRYPTED_FILE);
    decrypt(&ENCRYPTED_FILE,&DECRYPTED_FILE);
    return 0;
}
