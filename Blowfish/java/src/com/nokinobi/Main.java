package com.nokinobi;

import java.io.IOException;
import com.nokinobi.functions.Functions;

import static com.nokinobi.Decryptor.Decrypt;
import static com.nokinobi.Encryptor.Encrypt;

public class Main {

    public static final String THE_GOAL_FILE="./text";
    public static final String MAIN_INFORMATION_FILE="./info";
    public static final String ENCRYPTED_FILE = "./encrypted";
    public static final String DECRYPTED_FILE ="./decrypted";

    public static void main(String[] args) throws IOException {
        Functions.GenerateMainInformation();
        Encrypt(MAIN_INFORMATION_FILE,THE_GOAL_FILE,ENCRYPTED_FILE);
        Decrypt(ENCRYPTED_FILE,DECRYPTED_FILE);
    }
}
