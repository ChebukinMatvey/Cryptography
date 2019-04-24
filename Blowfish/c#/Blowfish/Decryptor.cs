using System;
using System.IO;
using System.Net;
using functions;
using Tuple = functions.Tuple;
using static functions.Functions;

namespace Blowfish
{
    class Decryptor
    {
        public static void Decrypt(string encryptedFile, string decryptedFile)
        {
            FileStream inputStream = new FileStream(encryptedFile,FileMode.Open);
            BinaryReader reader= new BinaryReader(inputStream);
            BinaryWriter writer= new BinaryWriter(new FileStream(decryptedFile, FileMode.OpenOrCreate));

            int[] keys = ReadKeys(reader);
            int[,] matrix = ReadMatrix(reader);
            
             
            Console.Write("Count of rounds = ");
            int roundsCount = Convert.ToInt32(Console.ReadLine());
            Array.Resize(ref keys,roundsCount);
            Array.Reverse(keys);
            
            int fileLength = reader.ReadInt32();
            
            Tuple tuple = new Tuple();
            for (int i = 0; i < fileLength / 8; i++)
            {
                ReadBlock(tuple, inputStream);
                ProcessBlock(tuple, keys, matrix,roundsCount);
                writer.Write(tuple.le);
                writer.Write(tuple.re);
            }

            int tail = fileLength % 8;
            if (tail > 0)
            {
                ReadBlock(tuple, inputStream);
                ProcessBlock(tuple, keys, matrix,roundsCount);
                long pi = ((long) tuple.re << 32) + tuple.le;
                for (int i = 0; i < tail; ++i)
                    writer.Write(new[] {(byte) (pi >> i * 8)}, 0, 1);
            }
            inputStream.Close();
            writer.Close();
        }
    }
}