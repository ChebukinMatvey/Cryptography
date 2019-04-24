package com.nokinobi;

import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import com.nokinobi.functions.Functions;
import java.util.Arrays;
import java.util.Scanner;


public class Decryptor {


    public static void Decrypt(String encryptedFile,String decryptedFile) throws IOException {

        LittleEndianInputStream reader = new LittleEndianInputStream(new FileInputStream(encryptedFile));
        LittleEndianOutputStream writer = new LittleEndianOutputStream(new FileOutputStream(decryptedFile));

        int[] keys = Functions.ReadKeys(reader);
        int[][] matrix = Functions.ReadMatrix(reader);
        int fileLen = reader.readInt();


        System.out.println("Count of rounds = ");
        Scanner scanner = new Scanner(System.in);
        int roundsCount = scanner.nextInt();

        keys = Arrays.copyOf(keys,roundsCount);
        Reverse(keys);

        Tuple block = new Tuple();
        for(int i=0;i< fileLen/8;++i){
            Functions.ReadBlock(block, reader);
            Functions.ProcessBlock(block, Arrays.copyOf(keys,roundsCount), matrix);
            writer.write(block.le);
            writer.write(block.re);
        }

        int tail = (fileLen + 8) % 8;
        if(tail != 0){
            Functions.ReadBlock(block, reader);
            Functions.ProcessBlock(block, Arrays.copyOf(keys,roundsCount), matrix);
            long pi = ( ((long)block.re)<<32 ) + block.le;
            for(int i=0;i<tail;++i)
              writer.write( (byte)(pi>>>i*8 ) );
        }

        reader.close();
        writer.close();
    }

    public static void Reverse(int[] arr){
        for(int i = 0; i < arr.length / 2; i++)
        {
            int temp = arr[i];
            arr[i] = arr[arr.length - i - 1];
            arr[arr.length - i - 1] = temp;
        }
    }
}
