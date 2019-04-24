#include<fstream>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<math.h>
#include <string>
using namespace std;

static const std::string THE_GOAL_FILE = "./text";
static const std::string MAIN_INFORMATION_FILE= "./info";
static const std::string ENCRYPTED_FILE = "./encrypted";
static const std::string DECRYPTED_FILE = "./decrypted";


struct _tuple{
    int le;
    int re;

    _tuple(){
        this->le = 0;
        this->re = 0;
    }
};

int* generate_random_sequence(int);
void generate_info();
int* read_keys(ifstream*);
int* *read_matrix(ifstream*);

void reverse(int*,int);

void process_block(_tuple*,int*,int**,int);
_tuple* read_block(ifstream*);
void round(_tuple*,int,int**);
int fs(int,int**);
void finish_swap(_tuple*,int,int);