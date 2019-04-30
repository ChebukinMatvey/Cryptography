#!/usr/bin/python3

from functions import *
import struct 
import os 
import math 

def encrypt(goal_file,main_information_file,encrypted_file):
    goal = open(goal_file,"rb")
    info = open(main_information_file,"rb")
    out = open(encrypted_file,"wb")

    ip = read_ip(info)
    reversed_ip = reverse_ip(ip)
    keys = read_keys(info)
    matrix = read_matrix(info)

    for val in ip:
        out.write(struct.pack("B",val))
    for key in keys:
        out.write(struct.pack("<Q",key))
    for row in matrix:
        for val in row:
            out.write(struct.pack("B",val))
 
    rounds = int(input("Count of rounds = "))
    keys = keys[:rounds]

    file_size = os.stat(goal_file).st_size
    out.write(struct.pack("<i",file_size))

    for i in range(math.ceil(file_size/8)):
        p = int.from_bytes(goal.read(8),"little")
        c = process_block(p,ip,reversed_ip,matrix,keys)
        out.write(struct.pack("<Q",c))



if __name__ == "__main__":
    encrypt("./text","./info","./encrypted")
