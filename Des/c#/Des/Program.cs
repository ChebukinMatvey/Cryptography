using System;
using System.IO;
using static Des.Functions;

using System.Linq;

namespace Des
{
    class Program
    {

        public static string THE_GOAL_FILE="./text";
        public static string MAIN_INFORMATION_FILE="./info";
        public static string ENCRYPTED_FILE="./encrypted";
        public static string DECRYPTED_FILE="./decrypted";


        static void Main(string[] args)
        {
            //generateMainInformation(MAIN_INFORMATION_FILE);
            Encryptor.encrypt(THE_GOAL_FILE,MAIN_INFORMATION_FILE,ENCRYPTED_FILE);
            Decryptor.decrypt(ENCRYPTED_FILE,DECRYPTED_FILE);
        }
    }

}
