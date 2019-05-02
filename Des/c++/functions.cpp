#include "header.h"

byte* E = new byte[48] {31,0,1,2,3,4,
                        3,4,5,6,7,8,
                        7,8,9,10,11,12,
                        11,12,13,14,15,16,
                        15,16,17,18,19,20,
                        19,20,21,22,23,24,
                        23,24,25,26,27,28,
                        27,28,29,30,31,0};


char* rol_count = new char[16]{1,2,1,2,1,1,2,1,2,1,2,2,1,2,1,2};


int64 process_block(int64 pi,byte*ip,byte*r_ip,byte**matrix,int64*keys,int rounds){
    pi = select_permutation(ip,pi,64);
    block* b = reinterpret_cast<block*>(&pi);

    int temp;
    for(int i=0;i<rounds;++i){
        temp = b->le;
        b->le=b->re;
        b->re = temp ^ fs(b->re,matrix,keys[i]);
    }
    temp = b->le;
    b->le=b->re;
    b->re=temp;

    return select_permutation(r_ip,pi,64);
}

int fs(int re,byte**matrix,int64 key){
    int res = 0;
    int64 pe = select_permutation(E,re,48);
    pe ^=key;
    for(int c =0,i,b,j;c<8;++c) {
        b = (pe>>c*6)&0b111111;
        i = (b&0b1) | ((b&0b100000)>>4);
        j = (b&0b011110)>>1;
        res |= ((int)matrix[i][j]) << c*4 ;
    }
    return res;
}

byte* read_ip(ifstream*in){
    byte*ip=new byte[64];
    in->read(reinterpret_cast<char*>(ip), 1*64);
    return ip;
}

int64* read_keys(ifstream*in){
    int64* keys=new int64[16];
    in->read(reinterpret_cast<char*>(keys), 8*16);
    return keys;
}

byte** read_matrix(ifstream*in){
    byte**matrix = new byte*[4];
    for(int i=0;i<4;++i)
        matrix[i]=new byte[16];
    for (int i = 0; i < 4; ++i)
        in->read(reinterpret_cast<char*>(matrix[i]), 1*16);
    return matrix;
}


int find_value_index(byte*array,byte value,int length){
    for (int i = 0; i < length; ++i)
        if(array[i]==value)
            return i;
}
// ip^-1
byte* reverse_ip(byte* ip,int length){
    byte* res=new byte[length];
    for(int i=0;i<length;++i)
        res[i] = find_value_index(ip,i,length);
    return res;
}

int64 select_permutation(byte* ip,int64 source,int count){
    int64 destination=0,current_bit=0;
    for(int i=0;i<count;++i){
        current_bit =  source &  ((int64)1)<<ip[i];
        if(i > ip[i])
            current_bit <<=  (i-(ip[i]));
        if(ip[i]> i)
            current_bit >>=  ((ip[i]) - i);
        destination |=  current_bit;
    }
    return destination;
}

int rol28(int val, int count) {
    val&=0xfffffff;
    return ((val << count)&0xfffffff) + (val >> (28 - count));
}


void generate(string* file) {
    ofstream out(*file);
    srand(time(NULL));

    byte* ip64 = get_shuffled_sequence(64);
    out.write(reinterpret_cast<const char *>(ip64),64);

    byte* ip48 = get_shuffled_sequence(56);
    byte* ip56 = get_shuffled_sequence(64);
    int64 k = ((int64)rand()) << 32 | rand();

    int64 temp = select_permutation(ip56,k,56);
    int c = temp>>28;
    int d = temp&0xfffffff;
    for(int i=0;i<16;++i){
        c = rol28(c, rol_count[i]);
        d = rol28(d, rol_count[i]);
        temp = ((int64)c<<28) | d;
        int64 key = select_permutation(ip48,temp,48);
        out.write(reinterpret_cast<const char *>(&key), 8);
    }
    for (int i = 0; i < 4; ++i) {
        byte* sequence = get_shuffled_sequence(16);
        out.write(reinterpret_cast<const char *>(sequence),16);
        delete [] sequence;
    }
    out.close();
    delete [] ip48;
    delete [] ip56;
    delete [] ip64;
}

void shuffle(byte*data,int length){
    int* array = new int[length];
    for (int i = 0; i <length; ++i) {
        array[i] =  rand();
    }
    for (int i = 0; i <length; ++i)
        for (int j = 0; j <length - i -1; ++j)
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
    delete[]array;
}

byte* get_shuffled_sequence(int length) {
    byte *sequence = new byte[length];
    for(int i=0;i<length;++i)
        sequence[i] = i;
    shuffle(sequence,length);
    return sequence;
}


void reverse(int64* arr,int len)
{
    for(int i = 0; i<len/2 ; ++i){
        int64 temp = arr[i];
        arr[i] = arr[len-i-1];
        arr[len-i-1] = temp;
    }
}
