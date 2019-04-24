#include "functions.h"

void decrypt()
{
    ifstream file(ENCRYPTED_FILE,ios_base::binary);
    ofstream out(DECRYPTED_FILE,ios_base::binary);

    int* keys = read_keys(&file);
    int** matrix = read_matrix(&file);

    int file_len;
    file.read(reinterpret_cast<char*>(&file_len),4);


    int rounds_count;
    cout<<"Count of rounds = ";
    cin>>rounds_count;
    reverse(keys,rounds_count);

    _tuple* block;
    for(int i = 0; i < file_len/8; ++i)
    {
        block = read_block(&file);
        process_block(block,keys,matrix,rounds_count);
        out.write(reinterpret_cast<char*>(block),8);
    }

    int tail = (file_len + 8)%8;
    if(tail != 0){
        block = read_block(&file);
        process_block(block,keys,matrix,rounds_count);
        ulong pi= ((long)block->re << 32 ) + block->le;
        for(int i =0;i<tail;++i){
            char c =  (pi >> i*8 ) & 0b011111111;
            out.write(&c,1);
        }
    }

    file.close();
    out.close();
}