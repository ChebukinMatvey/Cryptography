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


    block* block;
    for(int i = 0; i < ceil(file_len/8.0); ++i)
    {
        block = read_block(&file);
        process_block(block,keys,matrix,rounds_count);
        out.write(reinterpret_cast<char*>(block), i*8 <= (file_len-8) ? 8 : (file_len+8)%8 );
    }


    file.close();
    out.close();
}