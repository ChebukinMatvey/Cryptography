using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Des
{
    static class Functions
    {

        private static byte[] E = new byte[]
           {       31, 0, 1, 2, 3, 4,
                    3, 4, 5, 6, 7, 8,
                    7, 8, 9, 10, 11, 12,
                    11, 12, 13, 14, 15, 16,
                    15, 16, 17, 18, 19, 20,
                    19, 20, 21, 22, 23, 24,
                    23, 24, 25, 26, 27, 28,
                    27, 28, 29, 30, 31, 0};

        public static int[] rolСount = new int[] { 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2 };



        #region Algorithm 

        public static ulong processBlock(ulong p,byte[]ip,byte[]reversedIp,byte[,]matrix,long[] keys)
        {
            p = selectPermutation(p, ip, 64);


            var (le,re) = ( (uint)(p >>32) ,(uint)p);
            foreach(long key in keys)
                (le, re) = (re, le^fs(re,matrix,key));
            (le, re) = (re, le);
            return selectPermutation(((ulong)le << 32) | re, reversedIp, 64);
        }


        public static uint fs(uint re,byte[,] matrix,long key)
        {
            uint res = 0;
            long pe= (long)selectPermutation(re, E, 48);
            pe ^= key;
            for (int c = 0, b, j, i; c < 8; ++c)
            {
                b = (int)((pe & ((long)0b111111 << c * 6)) >> c * 6);
                i = b & 1 | ((b & 0b100000) >> 4);
                j = (b & 0b011110) >> 1;
                res |= (uint)matrix[i,j] << c * 4;
            }
            return res;
        }
        #endregion


        #region Generate main information 

        public static void generateMainInformation(string file)
        {
            Random r = new Random();
            BinaryWriter writer = new BinaryWriter(new FileStream(file, FileMode.OpenOrCreate)); ;

            byte[] ip64 = getShuffledSequence(64);
            byte[] ip48 = getShuffledSequence(48);
            byte[] ip56 = getShuffledSequence(56);

            for (int i = 0; i < 64; ++i)
                writer.Write(ip64[i]);

            long k = ((long)r.Next()) << 32 | (long)r.Next();
            Console.WriteLine(k);

            uint c =  (uint)(k>>32 );
            uint d =  (uint)(k & 0xfffffff);

            ulong temp;
            for (int i = 0; i < 16; ++i)
            {
                c = rol28(c, rolСount[i]);
                d = rol28(d, rolСount[i]);
                temp = ((ulong)c) << 28 | (uint)d;
                ulong key = selectPermutation(temp, ip48, 48);
                writer.Write(key);
            }

            for (int i = 0; i < 4; ++i)
            {
                byte[] row = getShuffledSequence(16);
                foreach(byte b in row)
                    writer.Write(b);
            }
            writer.Close();
        }
        #endregion


        #region  Utils function 


        public static ulong selectPermutation(ulong source, byte[] ip, int count)
        {
            ulong currentBit, destination = 0;
            for (int i = 0; i < count; ++i)
            {
                currentBit = (source & ((ulong)1 << ip[i]));
                if (i > ip[i])
                    currentBit <<= (i - ip[i]);
                if (i < ip[i])
                    currentBit >>= (ip[i] - i);
                destination |= currentBit;
            }
            //Console.WriteLine("Destination: " + (long)destination);
            return destination;
        }

        public static uint rol28(uint val, int count)
        {
            return ( ((val << count) & 0xfffffff) | val >> (28 - count) );
        }

        public static byte[]  getShuffledSequence(int length)
        {
            Random r = new Random();
            byte[] sequence = new byte[length];
            for (int i = 0; i < length; ++i)
                sequence[i] = (byte)i;
            for(int i = 0; i < sequence.Length; ++i)
            {
                int randomI = r.Next(sequence.Length-1);
                int randomJ = r.Next(sequence.Length-1);
                byte temp = sequence[randomI];
                sequence[randomI] = sequence[randomJ];
                sequence[randomJ] = temp;
            }
            return sequence;
        }

        public static byte[] reverseIp(byte[] ip)
        {
            byte[] rIp = new byte[ip.Length];
            for (int i = 0; i < ip.Length; ++i)
                rIp[i] =  ((byte)indexOf(ip, i));
            return rIp;
        }


        private static int indexOf(byte[] ip, int val)
        {
            for (int i = 0; i < ip.Length; ++i)
                if (ip[i] == val)
                    return i;
            return -1;
        }

        public static byte[] readIp(BinaryReader reader)
        {
            byte[] ip = new byte[64];
            for (int i = 0; i < 64; ++i)
                ip[i] = reader.ReadByte();
            return ip;
        }

        public static long[] readKeys(BinaryReader reader)
        {
            long[] keys = new long[16];
            for (int i = 0; i < 16; ++i)
                keys[i] = reader.ReadInt64();
            return keys;
        }

        public static byte[,] readMatrix(BinaryReader reader)
        {
            byte[,] matrix = new byte[4,16];
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 16; ++j)
                    matrix[i, j] = reader.ReadByte();
            return matrix;
        }


        public static ulong readBlock(BinaryReader reader)
        {
            byte[] _long = new byte[8];
            reader.BaseStream.Read(_long, 0, 8);
            return BitConverter.ToUInt64(_long, 0);
        }


        #endregion

    }
}
