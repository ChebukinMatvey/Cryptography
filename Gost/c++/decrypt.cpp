#include "header.h"
//extern int ROUNDS_COUNT;

void decrypt() {

    ifstream input(ENCRYPTED_FILE, ios_base::binary);
    ofstream output(DECRYPTED_FILE, ios_base::binary);

    int*  keys   = read_keys(&input);
    int** matrix = read_matrix(&input);

	int rounds;
    cout<<"Count of rounds [1:32] = ";
    cin>>rounds;
 
	vector<int>* keysequence = get_keysecuence(keys,rounds);
    reverse(keysequence->begin(),keysequence->end());
 
	int file_size;
    input.read(reinterpret_cast<char *>(&file_size), 4);

    block *b;
    for (int i = 0; i < ceil(file_size / 8.0); ++i) {
        b = read_block(&input);
        process_block(b, matrix, keysequence);
		output.write(reinterpret_cast<char*>(b), i*8 <= (file_size-8) ? 8: (file_size+8)%8);
    }

    output.close();
    input.close();

    delete []keys;
    for(int i=0; i<16;++i)
        delete [] matrix[i];
    delete [] matrix;
}