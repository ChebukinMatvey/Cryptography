#!/usr/bin/python3
import sys
import struct 
from random import shuffle, randint


def write_keys(out):
    keys = []
    for i in range(8):
        out.write( struct.pack( "=I",randint(0,4294967295)))

def write_matrix(out):
    for j in range(8):
        col = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
        shuffle(col)
        for i in range(16):
             out.write(struct.pack("=I",(col[i] << 4*j)))

if __name__ == '__main__':

    out = open("./info","ab+")    
    write_keys(out)
    write_matrix(out)
    out.close()
