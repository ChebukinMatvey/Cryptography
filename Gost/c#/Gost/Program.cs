using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using Functions;
using static Functions.Functions;
using Tuple = Functions.Tuple;
using static Generator.Generator;
namespace Gost
{
    class Program
    {
        public static string THE_GOAL_FILE = "./text";
        public static string MAIN_INFORATION_FILE = "./info";
        public static string ENCRYPTED_FILE= "./encrypted";
        public static string DECRYPTED_FILE= "./decrypted";
        
        public static void Main(string[] args)
        {
            Generate();
            Encryptor.Encrypt(THE_GOAL_FILE,MAIN_INFORATION_FILE,ENCRYPTED_FILE);
            Decryptor.Decrypt(ENCRYPTED_FILE,DECRYPTED_FILE);
        }
    }
}