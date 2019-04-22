using System;
using System.Collections.Generic;
using System.IO;

namespace Functions
{
    public static class Functions
    {
        public static void ProcessBlock(Tuple block, uint[,] matrix, List<uint> keys, int roundsCount)
        {
            for (int i = 0; i < roundsCount; i++)
            {
                block = Round(block, matrix, keys[i]);
            }
        }

        public static Tuple Round(Tuple block, uint[,] matrix, uint key)
        {
            uint se = Fs(block.re, matrix, key);
            uint temp = block.re;
            block.re = block.le ^ se;
            block.le = temp;
            return block;
        }

        public static uint Fs(uint re, uint[,] matrix, uint key)
        {
            uint s = re + key;
            uint res = 0;
            for (int j = 0; j < 8; j++)
            {
                int i = (int) (0b01111 & (s >> j * 4));
                res += matrix[i, j];
            }

            return Rol(res, 11);
        }

        public static uint Rol(uint val, int shift)
        {
            return (val << shift) + (val >> (32 - shift));
        }



        public static List<uint> GetKeysequence(List<uint> keys,int count)
        {
            List<uint> keysequence = new List<uint>();
            for(int i=0;i<3;++i)
                for (int j = 0; j < 8; j++)
                {
                    keysequence.Add(keys[j]);
                    if (keysequence.Count == count)
                        return keysequence;
                }

            for (int i = 7; i > -1; --i)
            {
                keysequence.Add(keys[i]);
                if (keysequence.Count == count)
                    return keysequence;
            }
            return null;
        }
        

        public static Tuple ReadBlock(FileStream input)
        {
            byte[] integer = new byte[8];
            input.Read(integer, 0, 8);
            ulong value  = BitConverter.ToUInt64(integer, 0);
            return new Tuple((uint) value,(uint) (value>>32));
        }

        public static uint[,] ReadMatrix(BinaryReader reader)
        {
            uint[,] matrix = new uint[16, 8];
                for (int i = 0; i < 8; i++) // for column 
                    for (int j = 0; j < 16; j++) // for row 
                        matrix[j, i] = reader.ReadUInt32();
            return matrix;
        }

        public static List<uint> ReadKeys(BinaryReader reader)
        {
            List<uint> keys = new List<uint>(8);
            for (int i = 0; i < 8; i++)
                keys.Add(reader.ReadUInt32());
            return keys;
        }
    }

    public class Tuple
    {
        public uint le;
        public uint re;

        public Tuple()
        {
        }

        public Tuple(uint le, uint re)
        {
            this.le = le;
            this.re = re;
        }

        public override string ToString()
        {
            return $" Touple state le={le}   re={re}";
        }
    }
}