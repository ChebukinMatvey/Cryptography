#!/usr/bin/python3
from random import randint as rand
import struct

THE_GOAL_FILE = "./text"
MAIN_INFORMATION_FILE = "./info"
ENCRYPTED_FILE = "encrypted"
DECRYPTED_FILE = "decrypted"
MAX_INT  = 2**32 - 1


def process_block(le,re ,matrix,keys):
    for i in range(0,len(keys)-2):
        le,re = round(le,re,keys[i],matrix)
    le,re = re^keys[len(keys)-1], le ^ keys[len(keys)-2] 
    return le,re


def round(le,re,key,matrix):
    lek = le ^ key
    return  (fs(lek,matrix) ^ re) , lek


def fs(lek,matrix):
    s1 = matrix[0][(lek >> 0)  & 0b011111111]
    s2 = matrix[1][(lek >> 8)  & 0b011111111]
    s3 = matrix[2][(lek >> 16) & 0b011111111]
    s4 = matrix[3][(lek >> 24) & 0b011111111]
    return (((s1+s2)^s3)+s4) & 0xffffffff

def read_block(inp):
    block = read_list(inp,2)
    return block[0],block[1]

def read_keys(inp):
    return read_list(inp,18)

def read_matrix(inp):
    matrix = []
    for i in range(4):
        matrix.append(read_list(inp,256))
    return matrix

def read_list(inp,n):
    nums = []
    for i in range(n):
        nums.append( int.from_bytes(inp.read(4),"little") )
    return nums


def generate_info():
    M = int(input("M = "))
    m = random_list(M)
    k = random_list(18)
    j = 0
    for i in range(18):
        k[i] =k[i] ^ m[j]
        j = j+1 if j+1<len(m) else 0

    matrix = []
    for i in range(4):
        matrix.append(random_list(256))

    out = open("./info","wb")
    sequence = k + matrix[0]+matrix[1]+matrix[2]+matrix[3]


    le,re= 0,0
    for i in range(521):
        le,re = process_block(le,re,matrix,k)
        out.write(struct.pack("<II",le,re))
        le = sequence[i]
        i+=1
        re = sequence[i]
                

def random_list(n):
    return [ rand(0,MAX_INT) for i in range(n) ]   

if __name__=="__main__":
    generate_info()