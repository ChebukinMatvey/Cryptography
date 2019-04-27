#include "header.h"

void encrypt(string* goal_file,string*info_file,string*encrypted_file){
    ifstream goal(*goal_file,ios_base::binary|ios_base::ate);
    ifstream info(*info_file,ios_base::binary);
    ofstream out(*encrypted_file,ios_base::binary);

    byte*  ip = read_ip(&info);
    byte* r_ip = reverse_ip(ip,64);
    int64* keys = read_keys(&info);
    byte** matrix = read_matrix(&info);

    out.write(reinterpret_cast<char*>(ip), sizeof(byte)*64);
    out.write(reinterpret_cast<char*>(keys), sizeof(int64)*16);
    for(int i=0;i<4;++i)
        out.write(reinterpret_cast<char*>(matrix[i]), sizeof(byte)*16);

    int file_size = goal.tellg();
    goal.seekg(0);

    out.write(reinterpret_cast<char*>(&file_size), sizeof(int));

    cout<<"Count of rounds[1:16] = ";
    int rounds = 0;
    cin>>rounds;

    int64 b=0,ci=0;
    for(int i=0;i<file_size/8.0;++i){
        goal.read(reinterpret_cast<char*>(&b), sizeof(b));
        ci = process_block(b,ip,r_ip,matrix,keys,rounds);
        out.write(reinterpret_cast<char*>(&ci), sizeof(ci));
    }

    info.close();
    goal.close();
    out.close();
    delete [] keys;
    delete [] ip;
    for (int i = 0; i < 4; ++i)
        delete []matrix[i];
    delete [] matrix;
}