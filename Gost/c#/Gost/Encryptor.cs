using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Functions;
using static Functions.Functions;
using Tuple = Functions.Tuple;

class Encryptor
{
    
    
    public static void Encrypt(string  THE_GOAL_FILE,string MAIN_INFORATION_FILE,string ENCRYPTED_FILE)
        {
            BinaryReader info = new BinaryReader( new FileStream(MAIN_INFORATION_FILE, FileMode.Open));
            FileStream input = new FileStream(THE_GOAL_FILE, FileMode.Open);
            BinaryWriter output = new BinaryWriter(new FileStream(ENCRYPTED_FILE, FileMode.OpenOrCreate));
            
            
            List<uint> keysequence = new List<uint>();
            List<uint> keys = ReadKeys(info);
            uint[,] matrix = ReadMatrix(info);


            foreach (uint key in keys)
                output.Write(key);
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 16; j++)
                    output.Write(matrix[j,i]);


            Console.Write("Count of rounds = ");
            int roundsCount = Convert.ToInt32(Console.ReadLine());
            
            keysequence = GetKeysequence(keys,roundsCount);

            uint fileSize = (uint) input.Length;
            output.Write(fileSize);

            Tuple block = new Tuple();
            for (int i = 0; i < Math.Ceiling(fileSize / 8d); i++)
            {
                block = ReadBlock(input);
                ProcessBlock(block, matrix, keysequence,roundsCount);
                output.Write(block.re);
                output.Write(block.le);
            }
            
            info.Close();
            input.Close();
            output.Close();
        }
}
