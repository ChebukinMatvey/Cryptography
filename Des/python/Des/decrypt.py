#!/usr/bin/python3

from functions import *
import struct 

def decrypt(encrypted_file,decrypted_file):
    
    inp = open(encrypted_file,"rb")
    out = open(decrypted_file,"wb")

    ip = read_ip(inp)
    reversed_ip = reverse_ip(ip)
    keys = read_keys(inp)
    matrix = read_matrix(inp)

    file_size = int.from_bytes(inp.read(4),"little")

    rounds = int(input("Count of rounds = "))
    keys = keys[:rounds]
    keys.reverse()
    

    for i in range(file_size//8):
        c = int.from_bytes(inp.read(8),"little")
        p = process_block(c,ip,reversed_ip,matrix,keys)
        out.write(struct.pack("<Q",p))
    tail = file_size % 8 
    if tail > 0:
        c = int.from_bytes(inp.read(8),"little")
        p = process_block(c,ip,reversed_ip,matrix,keys)
        for i in range(tail):
            out.write(struct.pack("B",0b11111111&(p>>i*8)))

if __name__=="__main__":
    decrypt("./encrypted","./decrypted")


