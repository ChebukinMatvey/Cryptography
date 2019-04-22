using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Gost;
using static Functions.Functions;
using Tuple = Functions.Tuple;

class Decryptor
{
        public static void Decrypt(string ENCRYPTED_FILE,string DECRYPTED_FILE)
        {
            FileStream fstream= new FileStream(Program.ENCRYPTED_FILE, FileMode.Open);
            BinaryReader inputRead=new BinaryReader(fstream);
            BinaryWriter output =new BinaryWriter( new FileStream(Program.DECRYPTED_FILE, FileMode.OpenOrCreate));

            List<uint> keys = ReadKeys(inputRead);
            uint[,] matrix = ReadMatrix(inputRead);
                
            List<uint> keysequence = new List<uint>();
            
            uint fileSize = inputRead.ReadUInt32();

            
            Console.Write("Count of rounds = ");
            int roundsCount = Convert.ToInt32(Console.ReadLine());

            keysequence = GetKeysequence(keys, roundsCount);
            keysequence.Reverse();
            
            Tuple block;
            for (int i = 0; i < fileSize / 8; i++)
            {
                block = ReadBlock(fstream);
                ProcessBlock(block, matrix, keysequence,roundsCount);
                output.Write(block.re);
                output.Write(block.le);
            }
            uint tail = (fileSize+8) % 8;
            if(tail != 0)
            {
                block = ReadBlock(fstream);
                ProcessBlock(block,matrix,keysequence,roundsCount);
                uint temp = block.le;
                block.le = block.re;
                block.re = temp;
                long pi= ((long)block.re << 32 ) + block.le;
                for(int i =0;i<tail;++i){
                    char c =  (char) ((pi >> i*8 ) & 0b011111111);
                    output.Write(c);
                }
            }
        }
    
}
