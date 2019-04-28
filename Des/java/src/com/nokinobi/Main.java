package com.nokinobi;

import java.io.IOException;

import static com.nokinobi.Decryptor.decrypt;
import static com.nokinobi.Encryptor.encrypt;

class Main{

    public static final String THE_GOAL_FILE="./text";
    public static final String MAIN_INFORMATION_FILE="./info";
    public static final String ENCYPTED_FILE="./encrypted";
    public static final String DECRYPTED_FILE="./decrypted";


    public static void main(String[] args) throws IOException {
//        generate("./info");
        encrypt(THE_GOAL_FILE,MAIN_INFORMATION_FILE,ENCYPTED_FILE);
        decrypt(ENCYPTED_FILE,DECRYPTED_FILE);
    }
}