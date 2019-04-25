#!/usr/bin/python3
from functions import *
import os 
import struct 
import math



if __name__=="__main__":
    goal = open(THE_GOAL_FILE,"rb")
    info = open(MAIN_INFORMATION_FILE,"rb")
    out = open(ENCRYPTED_FILE,"wb")

    keys = read_keys(info)
    matrix = read_matrix(info)

    for key in keys:
        out.write( struct.pack("<I",key) )
    
    for row in matrix:
        for val in row:
           out.write( struct.pack("<I",val) )
 
    file_size = os.stat(THE_GOAL_FILE).st_size
    out.write(struct.pack("<I",file_size))
 
    rounds = int(input("Count of rounds = "))
    keys = keys[:rounds]

    count = int( math.ceil(file_size/8) )
    for i in range(count):
        le,re = read_block(goal)
        le,re = process_block(le,re,matrix,keys)
        out.write( struct.pack("<II",le,re))