package com.nokinobi.stream;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class LittleEndianOutputStream extends OutputStream {


    private OutputStream fstream;

    public LittleEndianOutputStream(OutputStream fstream){
        this.fstream = fstream;
    }    


    @Override
    public void write(byte[] b) throws IOException {
        fstream.write(b,0,b.length);
    }


    @Override
    public void write(int b) throws IOException {
        this.write(ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(b).array());
    }

    public void write(byte b) throws IOException {
        this.write(new byte[]{b});
    }

}

