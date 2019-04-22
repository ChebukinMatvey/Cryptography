#include "header.h"
extern int ROUNDS_COUNT;

void decrypt() {

    ifstream input(ENCRYPTED_FILE, ios_base::binary);
    ofstream output(DECRYPTED_FILE, ios_base::binary);

    cout<<"Count of rounds [1:32] = ";
    cin>>ROUNDS_COUNT;

    int*  keys   = read_keys(&input);
    int** matrix = read_matrix(&input);

    vector<int>* keysequence = get_keysecuence(keys,ROUNDS_COUNT);
    reverse(keysequence->begin(),keysequence->end());

    for (int i = 0; i < 8; ++i)
        keysequence->push_back(keys[i]);
    for (int i = 0; i < 3; ++i)
        for (int j = 7; j > -1; --j)
            keysequence->push_back(keys[j]);

    int file_size;
    input.read(reinterpret_cast<char *>(&file_size), 4);

    block *b;
    for (int i = 0; i < file_size / 8; ++i) {
        b = read_block(&input);
        process_block(b, matrix, keysequence);
        output.write(reinterpret_cast<const char *>( &b->re), 4);
        output.write(reinterpret_cast<const char *>( &b->le), 4);
    }
    int tail = (file_size+ 8)%8;
    if(tail != 0){
        b = read_block(&input);
        process_block(b,matrix,keysequence);
        uint temp = b->le;
        b->le = b->re;
        b->re = temp;
        ulong pi= ((long)b->re << 32 ) + b->le;
        for(int i =0;i<tail;++i){
            char c =  (pi >> i*8 ) & 0b011111111;
            output.write(&c,1);
        }
    }

    output.close();
    input.close();

    delete []keys;
    for(int i=0; i<16;++i)
        delete [] matrix[i];
    delete [] matrix;
}