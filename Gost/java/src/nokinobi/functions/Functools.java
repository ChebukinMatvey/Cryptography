package nokinobi.functions;

import nokinobi.stream.LittleEndianInputStream;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.List;


public class Functools {

    public static void processBlock(Tuple block, int[][] matrix, int[] keys){
        for (int key : keys )
            round(block, matrix, key);
    }

    public static void round(Tuple block, int[][] h, int key){
        int se = fs(block.re,key,h);
        int temp = block.le;
        block.le = block.re;
        block.re = temp ^ se;
    }

    private static int fs(int re,int key, int[][]h){
        int s = re + key;
        int res = 0;
        for(int i = 0 ; i < 8;i++){
            int j = (s >>> i*4) & 0b01111;
            res = res | h[j][i];
        }
        return rol(res,11);
    }

    private static  int rol(int val , int count){
        int tail = val >>> (32 - count);
        return ( (val << count) + tail );
    }

    public static int[] getKeysequence(int[] keys,int count){
        int[] keysequence = new int[count];
        int index = 0;
        for(int i = 0 ; i < 3 ; ++i )
            for(int j=0 ; j<8 ; j++ ){
                keysequence[index++] = keys[j];
                if(index ==count)
                    return keysequence;
            }
        for(int i = 7 ; i > -1 ; --i ){
            keysequence[index++] = keys[i];
            if(index == count)
                return keysequence;
        }
        return null;
    }

    public static void reverse(int[] array){
        for(int i=0 ; i<array.length / 2; ++i) {
            int temp = array[i];
            array[i] = array[array.length - i - 1];
            array[array.length - i - 1] = temp;
        }
    }

    public static int[] readKeys(LittleEndianInputStream input) throws IOException {
        int[] keys = new int[8];
        for(int i = 0; i < 8 ; i++)
            keys[i] = input.readInt();
        input.close();
        return keys;
    }

    public static int[][] readMatrix(LittleEndianInputStream input) throws IOException {
        int[][] matrix= new int[16][8];
        for(int i =0; i<8;i++)
            for (int j = 0; j<16 ; j++)
                matrix[j][i] = input.readInt();
        input.close();
        return matrix;
    }

    public static Tuple readBlock(LittleEndianInputStream input) throws IOException {
        return new Tuple(input.readInt(),input.readInt());
    }
}

