#include"functions.h"

// Thinking - not typing 

// extern for functions 
const char* KEYS_FILE = "keys";
const char* MATRIX_FILE = "matrix";


void encrypt();
void decrypt();

int main(int argc, char const *argv[])
{

    srand(time(NULL));
//     generate_info();
     encrypt();
     decrypt();
    return 0;
}

