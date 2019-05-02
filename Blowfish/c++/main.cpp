#include"functions.h"

void encrypt();
void decrypt();

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	generate_info();
    encrypt();
    decrypt();
    return 0;
}

