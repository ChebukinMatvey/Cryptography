package com.nokinobi;

import com.nokinobi.stream.LittleEndianInputStream;
import com.nokinobi.stream.LittleEndianOutputStream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.ConcurrentModificationException;
import java.util.Scanner;

import static com.nokinobi.Functions.*;

public class Encryptor {

    public static void encrypt(String goalFileName,String infoFileName,String encryptedFileName) throws IOException {

        File goalFile = new File(goalFileName);

        LittleEndianInputStream goal = new LittleEndianInputStream(new FileInputStream(goalFile));
        LittleEndianInputStream info = new LittleEndianInputStream(new FileInputStream(infoFileName));
        LittleEndianOutputStream out = new LittleEndianOutputStream(new FileOutputStream(encryptedFileName));

        byte[] ip = readIp(info);
        byte[] reversedIp = reverseIp(ip);
        ArrayList<Long> keys = readKeys(info);
        byte[][] matrix = readMatrix(info);

        for (byte val : ip)
            out.write(val);
        for (long key : keys)
            out.write(key);
        for (byte[]row:matrix)
            for (byte val : row)
                out.write(val);

        int fileSize = (int) goalFile.length();
        out.write(fileSize);

        Scanner scanner = new Scanner(System.in);
        System.out.print("Count of rounds = ");
        int rounds = scanner.nextInt();
        keys = resize(keys,rounds);

        long pi;
        for(int i=0;i<Math.ceil(fileSize/8.0);++i){
            pi = goal.readLong();
            long ci = processBlock(pi,ip,reversedIp,matrix,keys);
            System.out.println(pi+" "+ci);
            out.write(ci);
        }
        goal.close();
        info.close();
        out.close();
    }
}