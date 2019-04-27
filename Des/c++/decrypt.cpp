#include "header.h"

void decrypt(string*encrypted_file,string*decrypted_file){

    ifstream inp(*encrypted_file,ios_base::binary);
    ofstream out(*decrypted_file,ios_base::binary);

    byte* ip = read_ip(&inp);
    byte* r_ip=reverse_ip(ip,64);
    int64* keys = read_keys(&inp);
    byte** matrix = read_matrix(&inp);

   int file_size;
   inp.read(reinterpret_cast<char*>(&file_size), sizeof(file_size));

   reverse(keys,16);

   cout<<"Count of rounds[1:16] = ";
   int rounds=0;
   cin>>rounds;

   int64 b=0,pi=0;
   for (int i = 0; i < file_size/8; ++i) {
       inp.read(reinterpret_cast<char*>(&b), sizeof(b));
       pi = process_block(b,ip,r_ip,matrix,keys+(16-rounds),rounds);
       out.write(reinterpret_cast<char*>(&pi), sizeof(pi));
   }
   int tail = (file_size+8)%8;
   if (tail>0){
       inp.read(reinterpret_cast<char*>(&b), sizeof(b));
       pi = process_block(b,ip,r_ip,matrix,keys+(16-rounds),rounds);
       for (int i = 0; i < tail; ++i) {
           char c = pi>>i*8;
           out.write(reinterpret_cast<char*>(&c), sizeof(c));
       }
   }

   inp.close();
    out.close();
    delete [] keys;
    delete [] ip;
    for (int i = 0; i < 4; ++i)
        delete []matrix[i];
    delete [] matrix;
}