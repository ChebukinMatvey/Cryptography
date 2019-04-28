package com.nokinobi;

import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

import static com.nokinobi.Functions.*;

public class Decryptor {


    public static void decrypt(String encryptedFile,String decryptedFile) throws IOException {
        LittleEndianInputStream in= new LittleEndianInputStream(new FileInputStream(encryptedFile));
        LittleEndianOutputStream out = new LittleEndianOutputStream(new FileOutputStream(decryptedFile));


        byte[] ip = readIp(in);
        byte[] reversedIp = reverseIp(ip);
        ArrayList<Long> keys = readKeys(in);
        byte[][] matrix = readMatrix(in);


        int fileSize = in.readInt();

        Scanner scanner = new Scanner(System.in);
        System.out.print("Count of rounds = ");
        int rounds = scanner.nextInt();
        keys = resize(keys,rounds);
        Collections.reverse(keys);


        for(int i=0;i<fileSize/8;++i){
            long ci = in.readLong();
            long pi = processBlock(ci,ip,reversedIp,matrix,keys);
            out.write(pi);
        }
        int tail = (fileSize+8)%8;
        if(tail>0){
            long ci = in.readLong();
            long pi = processBlock(ci,ip,reversedIp,matrix,keys);
            for (int i=0;i<tail;++i)
                out.write((byte)(pi>>i*8));
        }
        in.close();
        out.close();
    }

}
