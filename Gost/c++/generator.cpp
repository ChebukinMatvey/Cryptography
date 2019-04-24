#include"header.h"
#include<time.h>
#include<stdlib.h>

using namespace std;


void swap(int*array,int pos1,int pos2){
    int temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}

void shuffle(int*data){
    int* array = new int[16];
    for (int i = 0; i < 16; ++i) {
        array[i] =  rand();
    }
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16 - i -1; ++j)
           if(array[j] > array[j+1]){
               swap(array,j,j+1);
               swap(data,j,j+1);
           }
}


void generate_matrix(ofstream *file) {
    int* row = new int[16]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    for (int i = 0; i < 8; ++i) {
        shuffle(row);
        for(int i =0;i<16;++i)
            cout<<row[i]<<" ";
        cout << endl;
        for (int j = 0; j < 16; ++j) {
            int m =  (row[j] << 4 * i);
            file->write(reinterpret_cast<const char *>(&m), 4);
        }
    }

}

void generate_keys(ofstream *file){
    for(int i = 0;i < 8 ; ++i){
        int r = rand();
        file->write(reinterpret_cast<const char *>(&r), 4);
    }
}


int  generate(){
    srand(time(nullptr));
    ofstream out("./info",ios_base::binary);
    generate_keys(&out);
    generate_matrix(&out);
    out.close();
    return 0;
}

