#!/usr/bin/python3
from functions import * 
from encrypt import encrypt
from decrypt import decrypt




if __name__=="__main__":
    file = open("./info","rb")
    ip = read_ip(file)
    r_ip = reverse_ip(ip)
    keys = read_keys(file)
    matrix = read_matrix(file)
    test = 17179869187
    ci = process_block(test,ip,r_ip,matrix,keys)
    print(process_block(ci,ip,r_ip,matrix,keys))

    input()
    #encrypt("./text","./info","./encrypted")
    #decrypt("./encrypted","./decrypted")

