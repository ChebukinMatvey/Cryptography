import os 
import struct 
import random 

"""

- process_block 
- fs 
- read_ip
- read_keys 
- read_matrix
- reverse_ip
- select_permutation
- rol28
- generate
- get_random_sequence

"""

MAX_LONG = 9223372036854775807

E =[31,0,1,2,3,4,
    3,4,5,6,7,8,
    7,8,9,10,11,12,
    11,12,13,14,15,16,
    15,16,17,18,19,20,
    19,20,21,22,23,24,
    23,24,25,26,27,28,
    27,28,29,30,31,0]



rol_count = [1,2,1,2,1,1,2,1,2,1,2,2,1,2,1,2]


def process_block(p,ip,reversed_ip,matrix,keys):
    p = select_permutation(ip,p)
    
    le,re = p>>32,p&0xffffffff
    for key in keys:
        le,re = re, le^fs(re,matrix,key)
    le,re=re,le
    return select_permutation(reversed_ip,le<<32|re) 

    

def fs(re,matrix,key):
    s = 0
    pe = select_permutation(E,re)
    pe ^= key
    for c in range(8):
        b = (pe>>c*6)&0b111111
        i = ((b&0b100000)  >> 4) | (b&1)
        j = (b&0b011110) >> 1
        s|= matrix[i][j] << c*4
    return s

def read_ip(inp):
    ip = []
    for i in range(64):
        ip.append(int.from_bytes(inp.read(1),"little"))
    return ip

def read_keys(inp):
    keys = []
    for i in range(16):
        keys.append(int.from_bytes(inp.read(8),"little"))
    return keys 


def read_matrix(inp):
    matrix = [[],[],[],[]]
    for i in range(4):
        for j in range(16):
            matrix[i].append(int.from_bytes(inp.read(1),"little"))
    return matrix 



def select_permutation(ip,source):
    destination = 0
    for i,val in enumerate(ip):
        destination |= ((source & (0b1 << val)) >> val ) << i
    return destination


def rol28(val,count):
    val = val & 0xfffffff # 28 bits 
    return  (val << count)&0xfffffff | val >>( 28 - count)


def reverse_ip(ip):
    new_ip = []
    for i in range(len(ip)):
        new_ip.append(ip.index(i))
    return new_ip

def generate(filename):
    file = open(filename,"wb")

    ip64 = get_random_sequence(64)
    ip56 = get_random_sequence(56)
    ip48 = get_random_sequence(48)
    
    for val in ip64:
        file.write(struct.pack("B",val))

    k = random.randint(0,MAX_LONG)
    t = select_permutation(ip56,k)
    c,d = t>>28,t&0xfffffff
    
    for i in range(16):
        c,d = rol28(c,rol_count[i]),rol28(d,rol_count[i])
        file.write( struct.pack("<Q", select_permutation(ip48,c<<28|d)))

    for i in range(4):
        sequence = get_random_sequence(16)
        for j in range(16):
            file.write(struct.pack("B",sequence[j]))


def get_random_sequence(len):
    sequence = [i for i in range(len)]
    random.shuffle(sequence)
    return sequence 
