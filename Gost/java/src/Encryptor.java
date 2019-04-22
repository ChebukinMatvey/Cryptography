
import nokinobi.functions.Tuple;
import javafx.scene.Scene;
import nokinobi.stream.LittleEndianInputStream;
import nokinobi.stream.LittleEndianOutputStream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import static nokinobi.functions.Functools.*;


public class Encryptor {


    public static void encrypt(String mainInformationFile,String theGoalFile,String encryptedFile) throws Exception {

        File inpitFile = new File(theGoalFile);

        LittleEndianInputStream info = new LittleEndianInputStream(new FileInputStream(mainInformationFile));
        LittleEndianInputStream input= new LittleEndianInputStream(new FileInputStream(theGoalFile));
        LittleEndianOutputStream output= new LittleEndianOutputStream(new FileOutputStream(encryptedFile));

        int[] keys = readKeys(info);
        int[][] matrix = readMatrix(info);

        for(int i=0;i<8;++i)
            output.write(keys[i]);
        for(int j =0; j<8 ; ++j)
            for(int i=0;i<16;++i)
                output.write(matrix[i][j]);

        int file_size = (int) inpitFile.length();
        output.write(file_size);

        System.out.println("Count of rounds = ");
        Scanner scanner = new Scanner(System.in);
        int rounds =  scanner.nextInt();
        int[] keysequence = getKeysequence(keys,rounds);

        Tuple block;
        for (int i = 0; i < Math.ceil(file_size / 8d); ++i) {
            block = readBlock(input);
            processBlock(block, matrix, keysequence);
            output.write(block.re);
            output.write(block.le);
        }

        info.close();
        output.close();
        input.close();
    }

}

