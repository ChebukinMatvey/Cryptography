#ifndef __HEADER__
#define __HEADER__
#include<iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned long ulong;

// global constants
const string THE_GOAL_FILE="../text";
const string MAIN_INFORMATION_FILE="../info";
const string ENCRYPTED_FILE="../encrypted";
const string DECRYPTED_FILE="../decrypted";


struct block{
    uint le;
    uint re;
    block(uint le,uint  re){
        this->le = le;
        this->re = re;
    }
    block() {
        this->le =0;
        this->re =0;
    }
};

block* read_block(ifstream* file);
void process_block(block*,int**,std::vector<int>*);

int **read_matrix(ifstream* info);
int *read_keys(ifstream* info);

vector<int>* get_keysecuence(int*,int);
void round(block*,int**,uint);
int fs(uint,uint,int**);
int rol(uint,uint);

#endif
