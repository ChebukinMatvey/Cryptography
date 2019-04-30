#!/usr/bin/python3
from functions import * 
from encrypt import encrypt
from decrypt import decrypt




if __name__=="__main__":
    encrypt("./text","./info","./encrypted")
    decrypt("./encrypted","./decrypted")

