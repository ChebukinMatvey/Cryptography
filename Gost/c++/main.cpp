#include "header.h"

using namespace std;

void encrypt(); // main for encryption file
void generate(); // main for generator file
void decrypt();  // main for decryption file

// Global main function
int main(int argc, char **argv) {
    srand(time(nullptr));
    generate();
    encrypt();
    decrypt();
    return 0;
}
