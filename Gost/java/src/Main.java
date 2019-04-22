
class Main{

    public static final String MAIN_INFORMATION_FILE = "./info";
    public static final String THE_GOAL_FILE = "./text";
    public static final String ENCRYPTED_FILE = "./encrypted";
    public static final String DECRYPTED_FILE = "./decrypted";

    public static void main(String[] args) throws Exception {
//        Generator.main(args);
        Encryptor.encrypt(MAIN_INFORMATION_FILE,THE_GOAL_FILE,ENCRYPTED_FILE);
        Decryptor.decrypt(ENCRYPTED_FILE,DECRYPTED_FILE);
    }

}

