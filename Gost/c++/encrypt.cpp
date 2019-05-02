#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"



void  encrypt(){
    ifstream info(MAIN_INFORMATION_FILE, ios_base::binary);
    ifstream input(THE_GOAL_FILE, ios_base::ate | ios_base::binary);
    ofstream output(ENCRYPTED_FILE, ios_base::binary);

    int* keys = read_keys(&info);
    int** matrix = read_matrix(&info);

    output.write(reinterpret_cast<char*>(keys), sizeof(int)*8);

    for(int j = 0;j<8;j++) // for column
        for(int i=0;i<16;i++) // for row
            output.write(reinterpret_cast<char*>(&(matrix[i][j])),4);

    uint file_size = static_cast<uint>(input.tellg());
    input.seekg(0);
    output.write(reinterpret_cast<const char *>(&file_size), 4);

	int ROUNDS_COUNT;
    cout<<"Count of rounds [1:32] = ";
    cin >> ROUNDS_COUNT;
    vector<int> *keysequence = get_keysecuence(keys,ROUNDS_COUNT);

    block *b;
    for (int i = 0; i < ceil(file_size /8.0); ++i) {
        b = read_block(&input);
        process_block(b, matrix, keysequence);
		output.write(reinterpret_cast<char*>(b), 8);
    }
    input.close();
    output.close();


    delete [] keys;
    for(int i =0 ; i<16;i++)
        delete [] matrix[i];
    delete [] matrix;
}