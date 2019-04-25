package com.nokinobi.functions;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

import com.nokinobi.Main;
import com.nokinobi.Tuple;
import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;
import javafx.scene.transform.Scale;

public class Functions {

    public static void GenerateMainInformation() throws IOException {
        Random r = new Random();
        System.out.println("Enter m = ");
        int M = new Scanner(System.in).nextInt();
        int[] m = GenerateRandomSequence(r, M);
        int[] k = GenerateRandomSequence(r, 18);
        int [][] matrix = new int[4][256];
        for(int i =0;i<4;++i)
            for(int j=0;j<256;++j)
                matrix[i][j] = r.nextInt();
        
        for(int i=0,m_index=0;i<18;++i,++m_index){
            k[i] = k[i]^m[m_index];
            if(m_index == M-1)
                m_index=0;
        }

        LittleEndianOutputStream writer= new LittleEndianOutputStream(new FileOutputStream(Main.MAIN_INFORMATION_FILE));

        Tuple block = new Tuple();
        for(int i=0,k_i=0,m_j=0,m_i=0;i<521;++i){
            ProcessBlock(block, k, matrix);
            writer.write(block.le);
            writer.write(block.re);
            if(k_i < 16){
                block.le = k[k_i];
                block.re = k[++k_i];
            }
            else{
                block.le = matrix[m_i][m_j];   
                block.le = matrix[m_i][++m_j];
                if(m_j == 255){
                    m_i++;
                    m_j=0;
                }   
            }
        }
        writer.close();
    }

    public static int[] GenerateRandomSequence(Random r, int len){
        int[] sequence = new int[len];
        for(int i=0;i<len;++i)
            sequence[i] = r.nextInt();
        return sequence;
    }



    public static int[] ReadKeys(LittleEndianInputStream reader) throws IOException {
        int[] keys = new int[18];
        for(int i =0; i<18;i++){
            keys[i] = reader.readInt();
        }
        return keys;
    }


    public static int[][] ReadMatrix(LittleEndianInputStream reader) throws IOException {
        int[][] matrix = new int[4][256];
        for(int i =0; i<4; ++i)
            for(int j=0;j<256;++j)
                matrix[i][j] = reader.readInt();
        return matrix;
    }

    public static void ReadBlock(Tuple tuple,LittleEndianInputStream reader) throws IOException {
        tuple.le = reader.readInt();
        tuple.re = reader.readInt();
    }


    public static void ProcessBlock(Tuple tuple,int[]keys,int[][]matrix){
        for(int i=0;i<keys.length-2;++i)
            Round(tuple, keys[i], matrix);
        FinalSwap(tuple, keys[keys.length-1], keys[keys.length-2]);
    }


    public static void Round(Tuple tuple,int key,int[][]matrix){
        int lek = tuple.le^key;
        tuple.le = Fs(lek, matrix) ^ tuple.re;
        tuple.re = lek; 
    }

    public static void FinalSwap(Tuple tuple,int key1,int key2){
        int temp = tuple.le;
        tuple.le = tuple.re^key1;        
        tuple.re = temp^key2;        
    }

    private static int Fs(int lek,int[][] matrix){
        int s1 = matrix[0][ (lek>>>0)  & 0b011111111 ];
        int s2 = matrix[1][ (lek>>>8)  & 0b011111111 ];
        int s3 = matrix[2][ (lek>>>16) & 0b011111111 ];
        int s4 = matrix[3][ (lek>>>24) & 0b011111111 ];
        return ( ( s1+s2 )^s3 )+s4;
    }

}