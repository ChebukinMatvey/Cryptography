import nokinobi.stream.LittleEndianOutputStream;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Generator {

    public static void main(String[] args) throws IOException {
        int[][] matrix = generate_matrix();
        int[] keys = generate_keys();
        File file = new File("./info");
        LittleEndianOutputStream out = new LittleEndianOutputStream(new FileOutputStream(file));
        for (int key : keys)
            out.write(key);
        for (int i =0; i < 8; ++i)
            for (int j = 0; j < 16; j++)
                out.write(matrix[j][i]);
        out.close();
    }

    private static int[] generate_keys(){
        Random rand = new Random();
        int[] keys = new int[8];
        for (int i =0 ; i < 8 ; i++)
            keys[i] = rand.nextInt();
        return  keys;
    }

    private static int[][] generate_matrix(){
        int [][] matrix = new int[16][8];
        for(int i = 0 ; i < 8 ; i++){
            List<Integer> row = Arrays.asList(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
            Collections.shuffle(row);
            for(int j =0 ; j < row.size();j++)
                matrix[j][i] = row.get(j) << i*4;
        }
        return matrix;
    }
}
