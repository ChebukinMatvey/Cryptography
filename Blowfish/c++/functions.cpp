#include"functions.h"
extern char* KEYS_FILE;
extern char* MATRIX_FILE;

void generate_info()
{
    int M;
    std::cout << "M = ";
    std::cin >> M;
    int *m = generate_random_sequence(M);
    int *k = generate_random_sequence(18);

    int** matrix = new int*[4];
    for(int i =0; i<4 ; ++i)
        matrix[i] = generate_random_sequence(256);

    for(int i = 0,j=0; i<18 ; ++i,++j){
        k[i] = k[i]^m[j];
        if(j==M)
            j=0;
    }

    ofstream info(MAIN_INFORMATION_FILE,ios_base::binary);
    _tuple block;
    for(int i = 0,k_index=0,matrix_i=0,matrix_j=0 ; i<521; ++i){
        process_block(&block,k,matrix,18);
        if(i < 9)
            info.write(reinterpret_cast<char*>(&block),8);
        else
            info.write(reinterpret_cast<char*>(&block),8);
        
        if(k_index<16){ 
            block.le = k[k_index];
            block.re = k[++k_index];
        }
        else {
            block.le = matrix[matrix_i][matrix_j];
            block.re = matrix[matrix_i][++matrix_j];
            if(matrix_j == 255){
                matrix_i++;
                matrix_j = 0;
            }
        }
    }    

    info;
    delete [] k;
    delete [] m;
    for(int i =0; i<4 ; ++i)
        delete[] matrix[i];
    delete [] matrix;
}


int* generate_random_sequence(int N)
{
    int *sequence= new int[N];
    for(int i = 0; i < N ; ++i){
        sequence[i] = rand();
    }
    return sequence;
}


int* read_keys(ifstream* info)
{
    ifstream file(KEYS_FILE);
    int* keys = new int[18];
    for(int i = 0; i<18 ; ++i)
        info->read(reinterpret_cast<char*>(keys + i),4);
    return keys;
}

int** read_matrix(ifstream* info)
{
    int** matrix = new int*[4];
    for(int i = 0; i < 4 ; ++i)
        matrix[i] = new int[256];
    for(int i=0;i<4;++i)
        for(int j = 0; j<256 ; ++j )
            info->read(reinterpret_cast<char*>((*(matrix + i ) + j)),4);
    return matrix;
}

void reverse(int* arr,int len)
{
    for(int i = 0; i<len/2 ; ++i){
        int temp = arr[i];
        arr[i] = arr[len-i-1];
        arr[len-i-1] = temp;
    }
}

void process_block(_tuple* block,int*keys,int**matrix,int rounds_count)
{
    for(int i = 0 ; i < rounds_count-2; ++i )
        round(block,keys[i],matrix);
    finish_swap(block,keys[rounds_count-1],keys[rounds_count-2]);
}

_tuple* read_block(std::ifstream* file)
{
    _tuple* t = new _tuple();
    file->read(reinterpret_cast<char*>(t),8);
    return t;
}

void round(_tuple* block,int key,int**matrix)
{
    int lek = block->le ^ key;
    block->le = fs(lek,matrix) ^ block->re;    
    block->re = lek;
}

int fs(int lek,int**matrix)
{   
    int s1 = matrix[0][ (lek >> 0)  & 0b011111111 ];
    int s2 = matrix[1][ (lek >> 8)  & 0b011111111 ];
    int s3 = matrix[2][ (lek >> 16) & 0b011111111 ];
    int s4 = matrix[3][ (lek >> 24) & 0b011111111 ];
    return ( ( s1+s2 ) ^ s3 ) + s4;
}

void finish_swap(_tuple* block,int key1,int key2)
{
    int temp = block->le;
    block->le = block->re ^ key1;
    block->re = temp ^ key2;
}