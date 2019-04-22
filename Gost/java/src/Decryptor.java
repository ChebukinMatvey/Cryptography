
import nokinobi.functions.Tuple;
import nokinobi.stream.LittleEndianInputStream;
import nokinobi.stream.LittleEndianOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Scanner;

import static nokinobi.functions.Functools.*;

public class Decryptor {

    public static void decrypt(String ecnryptedFile,String decryptedFile) throws Exception {
        LittleEndianInputStream input =new LittleEndianInputStream( new FileInputStream(ecnryptedFile) );
        LittleEndianOutputStream output = new LittleEndianOutputStream(new FileOutputStream(decryptedFile));

        int[] keys = readKeys(input);
        int[][] matrix = readMatrix(input);

        int fileSize = input.readInt();

        System.out.println("Count of rounds = ");
        Scanner scanner = new Scanner(System.in);
        int rounds =  scanner.nextInt();
        int[] keysequence = getKeysequence(keys,rounds);

        reverse(keysequence);

        Tuple block;
        for (int i = 0; i < fileSize / 8; ++i) {
            block = readBlock(input);
            processBlock(block, matrix, keysequence);
            output.write(block.re);
            output.write(block.le);
        }

        int tail = (fileSize + 8) % 8;
        if(tail !=0){
            block = readBlock(input);
            processBlock(block,matrix,keysequence);
            long pi = (((long)block.le)<<32) + block.re;
            for(int i=0;i<tail;++i)
                output.write((byte) (pi >>> i*8));
        }

    }
}