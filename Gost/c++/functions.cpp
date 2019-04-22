#include "header.h"

extern int ROUNDS_COUNT;
using namespace std;

void process_block(block *b, int **matrix, vector<int> *keysequence) {
    for (int i =0 ; i < ROUNDS_COUNT ; i++) {
        round(b, matrix, keysequence->at(i));
    }
}

void round(block *b, int **matrix, uint key) {
//    cout<<"Round with key"<<key<<endl;
    int se = fs(b->re, key, matrix);
    uint temp = (b->le) ^se;
    b->le = b->re;
    b->re = temp;
}


int fs(uint re, uint key, int **matrix) {
    int s = re + key;
    int res = 0;
    for (int j = 0; j < 8; j++) {
        int i = 0b01111 & (s >> j * 4);
        res += matrix[i][j];
    }
    return rol(res, 11);
}

int rol(uint val, uint count) {
    return (val << count) + (val >> (32 - count));
}

block *read_block(ifstream *file) {
    block* b = new block();
    file->read(reinterpret_cast<char*>(b),8);
    return b;
}

vector<int>* get_keysecuence(int* keys,int count){
    vector<int>* keysequence = new vector<int>();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 8; ++j) {
            keysequence->push_back(keys[j]);
            if (keysequence->size() == count) {
                return keysequence;
            }
        }
     for(int i = 7 ; i > -1 ; --i){
        keysequence->push_back(keys[i]);
        if(keysequence->size() == count)
            return keysequence;
    }
}


int **read_matrix(ifstream* file) {
    int **matrix = new int *[16];
    for (int i = 0; i < 16; ++i)
        matrix[i] = new int[8];
    for (int j = 0; j < 8; ++j)
        for (int i = 0; i < 16; ++i) {
            int val = 0;
            file->read(reinterpret_cast<char *>(&val), 4);
            matrix[i][j] = val;
        }
    return matrix;
}

int *read_keys(ifstream* file) {
    int *keys = new int[8];
    for (int j = 0; j < 8; ++j)
        file->read(reinterpret_cast<char *>(keys+j), 4);
    return keys;
}