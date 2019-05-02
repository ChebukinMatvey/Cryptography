#ifndef __HEADER__
#define __HEADER__

#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>


using namespace std;

typedef unsigned long long int64;
typedef unsigned char byte;

struct block{
    int re;
    int le;
};

void encrypt(string*,string*,string*);
void decrypt(string*,string*);

int64 process_block(int64 pi,byte*ip,byte*r_ip,byte**matrix,int64*keys,int count);
int fs(int re,byte**matrix,int64 k);
int64 select_permutation(byte* ip,int64 source,int count);
byte* reverse_ip(byte*,int);

byte*  read_ip(ifstream*);
int64* read_keys(ifstream*);
byte** read_matrix(ifstream*);
void reverse(int64*,int);

// Generate random permutation and keys
int rol28(int val,int count);
void generate(string*file);
byte* get_shuffled_sequence(int length);

#endif