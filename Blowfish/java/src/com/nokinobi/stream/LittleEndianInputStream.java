package com.nokinobi.stream;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.Collections;

public class LittleEndianInputStream extends InputStream {

    private FileInputStream fstream;
 
    private ByteBuffer bf;

    
    public LittleEndianInputStream(FileInputStream fstream){
        this.fstream = fstream;
        bf = ByteBuffer.allocate(4);
        bf.clear();
        bf.order(ByteOrder.LITTLE_ENDIAN);
    }

    public int readInt() throws IOException {
        byte[] integer = new byte[4];
        this.read(integer);
        bf.clear();
        bf.put(integer);
        return bf.getInt(0);
    }


    @Override
    public int read(byte[] data) throws IOException {
        int read =  fstream.read(data);
        Collections.reverse(Arrays.asList(data));
        return read;
    }
 
    @Override
    public int read() throws IOException {
        return 0;
    }
}
