#!/usr/bin/python3
from random import shuffle
import struct 
import random
import sys 
import os 
from functions import *


ENCRYPTED_FILE = "encrypted"
DECRYPTED_FILE = "decrypted"

if __name__ =='__main__':
    
    inp = open(ENCRYPTED_FILE,"rb")
    out = open(DECRYPTED_FILE,"wb")

    keys = read_keys(inp)    
    h = read_substitution_matrix(inp)

    
    bytes_count = int.from_bytes(inp.read(4),"little",signed=False)    
    
    
    rounds_count = int( input("Count of rounds = ") ) 
    keysequence = (keys + keys + keys + keys[::-1])[:rounds_count]
    keysequence.reverse()
    
    for i in range(bytes_count // 8): 
        le, re = read_block(inp)
        for key in keysequence:
            le, re = round(le,re,h,key) 
        write_block(le,re,out)
    else:
        tail = bytes_count % 8
        if tail != 0:
            le ,re = read_block(inp); 
            for key in keysequence:
                le,re = round(le,re,h,key)
            pi =  ( le << 32 ) + ( re )
            for i in range(tail):
                out.write(struct.pack("B", 0b011111111 & ( pi >> i*8)))
    
    inp.close()
    out.close()  

