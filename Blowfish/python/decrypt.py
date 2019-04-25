#!/usr/bin/python3
from functions import *
import os 
import struct 
import math

if __name__=="__main__":
    inp = open(ENCRYPTED_FILE,"rb")
    out = open(DECRYPTED_FILE,"wb")

    keys = read_keys(inp)
    matrix = read_matrix(inp)
    file_size = int.from_bytes(inp.read(4),"little")   

    rounds = int(input("Count of rounds = "))
    keys = keys[:rounds]
    keys.reverse()
 
    count = int(file_size//8)
    for i in range(count):
        le,re = read_block(inp)
        le,re = process_block(le,re,matrix,keys)
        out.write( struct.pack("<II",le,re))

    tail = file_size % 8
    if tail > 0:
        le,re = read_block(inp)
        le,re = process_block(le,re,matrix,keys)
        pi = (re<<32) | le
        for i in range(tail):
            b = 0b11111111&(pi >> i*8 )
            out.write(struct.pack("B",b))

