using static Blowfish.Encryptor;
using static functions.Functions;
using static Blowfish.Decryptor;

namespace Blowfish
{
    internal class Program
    {

        private static string THE_GOAL_FILE = "text";
        private static string MAIN_INFORMATION_FILE = "info";
        private static string ENCRYPTION_FILE = "encrypted";
        private static string DECRYPTION_FILE = "decrypted";
        
        
        public static void Main(string[] args)
        {
//            Generate(MAIN_INFORMATION_FILE);
            Encrypt(THE_GOAL_FILE,MAIN_INFORMATION_FILE,ENCRYPTION_FILE);
            Decrypt(ENCRYPTION_FILE,DECRYPTION_FILE);
        }

        


        
    }
}