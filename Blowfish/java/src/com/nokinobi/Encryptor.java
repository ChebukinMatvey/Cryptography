package com.nokinobi;


import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

import com.nokinobi.functions.Functions;


public class Encryptor {


    public static void Encrypt(String infoFileName , String textFileName, String toEncrypt) throws IOException {

        File file = new File(textFileName);

        LittleEndianInputStream info = new LittleEndianInputStream(new FileInputStream(infoFileName));
        LittleEndianInputStream reader = new LittleEndianInputStream(new FileInputStream(textFileName));
        LittleEndianOutputStream writer = new LittleEndianOutputStream(new FileOutputStream(toEncrypt));


        // read keys and matrix  from generated 'info' file
        int[] keys = Functions.ReadKeys(info);
        int[][]matrix = Functions.ReadMatrix(info);

        // Write info to encrypted file
        for(int key : keys )
            writer.write(key);
        for(int i =0;i<4;++i)
            for(int j=0;j<256;++j)
                writer.write(matrix[i][j]);

        int fileLen = (int) file.length();
        writer.write(fileLen);


        System.out.println("Count of rounds = ");
        Scanner scanner = new Scanner(System.in);

        int roundsCount = scanner.nextInt();
        keys = Arrays.copyOf(keys,roundsCount);

        Tuple block = new Tuple();
        for(int i=0;i< Math.ceil(fileLen/8d);++i){
            Functions.ReadBlock(block, reader);
            Functions.ProcessBlock(block, keys , matrix);
            writer.write(block.le);
            writer.write(block.re);
        }


        info.close();
        reader.close();
        writer.close();
    }
}
