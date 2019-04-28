package com.nokinobi;

import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;

import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;

public class Functions {

    private static byte[] E = new byte[]
            {       31, 0, 1, 2, 3, 4,
                    3, 4, 5, 6, 7, 8,
                    7, 8, 9, 10, 11, 12,
                    11, 12, 13, 14, 15, 16,
                    15, 16, 17, 18, 19, 20,
                    19, 20, 21, 22, 23, 24,
                    23, 24, 25, 26, 27, 28,
                    27, 28, 29, 30, 31, 0};

    public static byte[] rol_count = new byte[]{1,2,1,2,1,1,2,1,2,1,2,2,1,2,1,2};



    public static long processBlock(long pi,byte[] ip,byte[]reversedIp,byte[][] matrix,ArrayList<Long> keys){
        pi = selectPermutation(pi,ip,64);

        Tuple block = new Tuple(pi);
        for (long key:keys){
            int t = block.le;
            block.le = block.re;
            block.re = t^fs(block.re,matrix,key);
        }
        int t = block.le;
        block.le = block.re;
        block.re = t;

        return selectPermutation(block.toLong(),reversedIp,64);
    }


    public static int fs(int re, byte[][] matrix, long key) {
        int res=0;
        long pe = selectPermutation(re,E,48);
        pe^=key;
        for(int c=0,b,j,i;c<8;++c){
           b = (int) ((pe & ((long) 0b111111 << c * 6)) >>> c * 6);
           i = b&1 | ( (b&0b100000) >>4 );
           j = (b&0b011110)>>1;
           res|= matrix[i][j]<<c*4;
        }
        return res;
    }


    public static void generate(String filrName) throws IOException {
        LittleEndianOutputStream out = new LittleEndianOutputStream(new FileOutputStream(filrName));
        Random r = new Random();
        byte[] ip64 = getShuffledSequence(64);
        byte[] ip56 = getShuffledSequence(56);
        byte[] ip48 = getShuffledSequence(48);

        for (byte b : ip64)
            out.write(b);
        long temp;
        long k = r.nextLong();
        int c = (int) (k>>>28);
        int d = (int) (k&0xfffffff);
        for (int i=0;i<16;++i){
            c = rol28(c,rol_count[i]);
            d = rol28(d,rol_count[i]);
            temp = (long)c<<28 | d;
            long key = selectPermutation(temp,ip48,48);
            out.write(key);
        }

        for (int i=0;i<4;++i){
            byte[] row = getShuffledSequence(16);
            for (byte b : row )
                out.write(b);
        }
    }


    public static byte[] reverseIp(byte[] ip){
        byte[] rIp= new byte[ip.length] ;
        for (int i = 0; i < ip.length; ++i)
            rIp[i]=((byte) indexOf(ip,i));
        return rIp;
    }

    private static int indexOf(byte[]ip,int val){
        for(int i=0;i<ip.length;++i)
            if(ip[i]==val)
                return i;
        return -1;
    }


    public static long selectPermutation(long source, byte[] ip, int count) {
        long currentBit, destination = 0;
        for (int i = 0; i < count; ++i) {
            currentBit = source & ((long) 1 << ip[i]);
            if (i > ip[i])
                currentBit <<= (i - ip[i]);
            if (i < ip[i])
                currentBit >>>= (ip[i] - i);
            destination |= currentBit;
        }
        return  destination;
    }

    public static byte[] getShuffledSequence(int length) {
        ArrayList<Byte> sequence = new ArrayList<Byte>();
        for (int i = 0; i < length; ++i)
            sequence.add((byte) i);
        Collections.shuffle(sequence);
        byte[]arr= new byte[sequence.size()];
        for (int i=0;i<sequence.size();++i)
            arr[i] = sequence.get(i);
        return arr;
    }

    public static int rol28(int val, int count) {
        return ((val << count) & 0xfffffff) | val >>> (28 - count);
    }


    public static byte[] readIp(LittleEndianInputStream inp) throws IOException {
        byte[] ip = new byte[64];
        for (int i=0;i<64;++i)
            ip[i] = (byte) inp.read();
        return ip;
    }

    public static ArrayList<Long> readKeys(LittleEndianInputStream inp) throws IOException {
        ArrayList<Long> keys = new ArrayList<>();
        for(int i=0;i<16;++i)
            keys.add(inp.readLong());
        return keys;
    }

    public static byte[][] readMatrix(LittleEndianInputStream inp) throws IOException {
        byte[][] matrix = new byte[4][16];
        for (int i=0;i<4;++i)
            for (int j=0;j<16;++j)
                matrix[i][j] = (byte) inp.read();
        return matrix;
    }


    public static ArrayList<Long> resize(ArrayList<Long> old, int size){
        ArrayList<Long> newList = new ArrayList<>();
        for (int i=0;i<size;++i)
            newList.add(old.get(i));
        return newList;
    }


}
