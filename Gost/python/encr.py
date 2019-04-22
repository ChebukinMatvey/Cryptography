#!/usr/bin/python3
from random import shuffle
import struct 
import random
import sys 
import os
import math
from functions import *


MAIN_INFORMATION_FILE = "info" 
THE_GOAL_FILE = "text"
ENCRYPTED_FILE = "encrypted"
DECRYPTED_FILE = "decrypted"


if __name__ =='__main__':

    info = open( MAIN_INFORMATION_FILE, "rb")
    inp  = open( THE_GOAL_FILE, "rb")
    out  = open( ENCRYPTED_FILE, "wb")

    keys = read_keys(info)    
    h = read_substitution_matrix(info)

    for key in keys:
        out.write( struct.pack("=I",key) )
    for row in h:
        for val in row:
            out.write( struct.pack("=I",val) )
    
    file_size = os.stat(THE_GOAL_FILE).st_size
    out.write(struct.pack("=I",file_size))
    
    rounds_count = int( input("Count of rounds = ") )
    keysequence = (keys + keys + keys+keys[::-1])[:rounds_count]

    for i in range( math.ceil(file_size / 8)):
        le,re = read_block(inp)
        for key in keysequence:
            le, re = round(le,re,h,key)
        write_block(le,re,out)
   
    inp.close()
    out.close()  
