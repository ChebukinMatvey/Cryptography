#ifndef __HEADER__
#define __HEADER__

#include<fstream>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<math.h>
#include <string>
using namespace std;

static const string THE_GOAL_FILE = "./text";
static const string MAIN_INFORMATION_FILE= "./info";
static const string ENCRYPTED_FILE = "./encrypted";
static const string DECRYPTED_FILE = "./decrypted";


typedef unsigned long ulong;

struct block{
    int le;
    int re;

    block(){
        this->le = 0;
        this->re = 0;
    }
};

int* generate_random_sequence(int);
void generate_info();
int* read_keys(ifstream*);
int* *read_matrix(ifstream*);

void reverse(int*,int);

void process_block(block*,int*,int**,int);
block* read_block(ifstream*);
void round(block*,int,int**);
int fs(int,int**);
void finish_swap(block*,int,int);

#endif 