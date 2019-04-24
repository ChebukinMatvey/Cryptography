using System;
using System.IO;
using Tuple = functions.Tuple;
using static functions.Functions;

namespace Blowfish
{
    class Encryptor
    {
        public static void Encrypt(string textFile,string infoFile,string encryptedFile)
        {
            BinaryReader info = new BinaryReader(new FileStream(infoFile,FileMode.Open));
            FileStream input = new FileStream(textFile,FileMode.Open);
            BinaryWriter writer= new BinaryWriter(new FileStream(encryptedFile,FileMode.OpenOrCreate));


            int[] keys = ReadKeys(info);
            int[,] matrix = ReadMatrix(info);

            
            
            foreach (var key in keys)
                writer.Write(key);
            for (int i = 0; i < 4; i++)
                for(int j=0;j<256;++j)
                    writer.Write(matrix[i,j]);

            int fileLen = (int) input.Length;
            writer.Write(fileLen);
            
            Console.Write("Count of rounds = ");
            int roundsCount = Convert.ToInt32(Console.ReadLine());
            
            Tuple tuple=new Tuple();
            for (int i = 0; i < Math.Ceiling(fileLen/8d); i++)
            {
                ReadBlock(tuple,input);
                ProcessBlock(tuple,keys,matrix,roundsCount);
                writer.Write(tuple.le);
                writer.Write(tuple.re);
            }
            
            info.Close();
            input.Close();
            writer.Close();
        }
    }
}