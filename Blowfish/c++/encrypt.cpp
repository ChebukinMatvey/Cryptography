#include "functions.h"


void encrypt()
{
    ifstream info(MAIN_INFORMATION_FILE,ios_base::binary);
    ifstream file(THE_GOAL_FILE,ios_base::binary | ios_base::ate);
    std::ofstream out(ENCRYPTED_FILE,ios_base::binary);

    int* keys = read_keys(&info);
    int** matrix = read_matrix(&info);

    for(int i=0;i<18;++i)
        out.write(reinterpret_cast<const char*>(keys+i),4);
    for(int i=0;i<4;++i)
        out.write(reinterpret_cast<const char*>(matrix[i]),256 * sizeof(int));


    int file_len = file.tellg();
    file.seekg(0);
    out.write(reinterpret_cast<const char*>(&file_len),4);

    int rounds_count;
    cout<<"Count of rounds = ";
    cin>>rounds_count;


    _tuple* block;
    for(int i = 0; i < ceil(file_len/(double)8); ++i)
    {
        block = read_block(&file);
        process_block(block,keys,matrix,rounds_count);
        out.write(reinterpret_cast<char*>(block),8);
    }

    delete [] keys;
    for(int i=0;i<4;++i)
        delete [] matrix[i];
    delete [] matrix;

    info.close();
    file.close();
    out.close();
}
