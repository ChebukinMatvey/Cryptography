using System;
using System.IO;
using System.Linq;
using static Des.Functions;


namespace Des
{
    internal class Decryptor
    {
        public static void decrypt(string encryptedFile , string decryptedFile)
        {
            BinaryReader input  = new BinaryReader(new FileStream(encryptedFile, FileMode.Open));
            BinaryWriter output = new BinaryWriter(new FileStream(decryptedFile, FileMode.OpenOrCreate));

            byte[] ip = readIp(input);
            byte[] reversedIp = reverseIp(ip);
            long[] keys = readKeys(input);
            byte[,] matrix = readMatrix(input);

            int fileSize = input.ReadInt32();
            
            
            Console.WriteLine("Count of rounds[1:16] = ");
            int rounds = Convert.ToInt32(Console.ReadLine());
            Array.Resize(ref keys,rounds);
            
            keys = keys.Reverse().ToArray();

            for(int i=0; i< fileSize/8; ++i){
                ulong c = readBlock(input);
                ulong p = processBlock(c, ip, reversedIp, matrix, keys);
                output.Write(p);
            }

            int tail = (fileSize + 8) % 8;
            if(tail > 0){
                ulong c = readBlock(input);
                ulong p = processBlock(c, ip, reversedIp, matrix, keys);
                for (int i = 0; i < tail; ++i)
                    output.Write((byte)(p >> i * 8));
            }
            input.Close();
            output.Close();
        }
    }
}