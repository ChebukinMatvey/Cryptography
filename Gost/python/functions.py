import struct 

def read_substitution_matrix(inp):
    h = []
    for j in range(8):
        row = []
        for i in range(16):
            row.append(int.from_bytes(inp.read(4),'little',signed=False))
        h.append(row)
    return h


def read_keys(inp):
    keys = []
    for i in range(8):
        keys.append(int.from_bytes(inp.read(4),'little',signed=False))
    return keys

def ROL(data, shift, size=32):
    shift %= size
    remains = data >> (size - shift)
    body = (data << shift) - (remains << size )
    return (body + remains)


def fs(re,h,k):
    res = 0
    s = re + k
    for j in range(8):
        i = ( s >> j*4 ) & 0b01111
        res = res + h[j][i]
    return ROL(res,11)


def round(le,re,h,k):
    se = fs(re,h,k)
    return re, le^se


def read_block(inp):
    le = int.from_bytes(inp.read(4), 'little', signed = False)
    integer = inp.read(4)
    if len(integer) < 4:
        #print(type(integer))
        re = int.from_bytes(integer,'little',signed = False)
        re = re << (4 - len(integer))*8
    else:
        re = struct.unpack('<I',integer)[0]
    return le , re

def write_block(le,re,out):
    out.write(struct.pack("<I",re)) # final le-re swap 
    out.write(struct.pack("<I",le))
