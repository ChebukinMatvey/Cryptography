package com.nokinobi;

public class Tuple {

    public int le;
    public int re;

    public Tuple(){}

    public Tuple(int le,int re){
        this.le = le;
        this.re = re;
    }

    public Tuple(long val) {
        this.le = (int) (val>>>32);
        this.re = (int) val;
    }


    public long toLong(){
        return ((long)this.le)<<32 | Integer.toUnsignedLong(this.re);
    }
}
