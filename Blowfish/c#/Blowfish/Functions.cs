
using System;
using System.IO;
using System.Net;
using System.Runtime.Remoting.Lifetime;

namespace  functions{

    public static class Functions
    {

        public static void Generate(string infoFile)
        {
            Random r = new Random();
            
            FileStream info= new FileStream(infoFile,FileMode.OpenOrCreate);
            Console.WriteLine("M = ");
            int M = Convert.ToInt32(Console.ReadLine());
            
            int[] m = GenerateRandomSequence(r,M);
            int[] k = GenerateRandomSequence(r,18);
            int[,] matrix = new int[4,256];
            
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 256; j++)
                    matrix[i,j] = r.Next(int.MaxValue);

            
            for (int i = 0,m_index = 0; i < 18; ++i)
            {
                k[i] = k[i] ^ m[m_index++];
                if (m_index == M)
                    m_index = 0;
            }

            Tuple tuple = new Tuple();
            for (int i = 0,matrix_i=0,matrix_j=0,k_index=0; i < 521; ++i)
            {
                ProcessBlock(tuple,k,matrix,18);
                info.Write(BitConverter.GetBytes(tuple.le),0,4);
                info.Write(BitConverter.GetBytes(tuple.re),0,4);
                if (k_index < 16)
                {
                    tuple.le = k[k_index];
                    tuple.re = k[++k_index];
                }
                else
                {
                    tuple.le = matrix[matrix_i,matrix_j];
                    tuple.re = matrix[matrix_i,++matrix_j];
                    if (matrix_j == 255)
                    {
                        matrix_i++;
                        matrix_j = 0;
                    }
                }
                    
            }
            info.Close();
        }

        public static int[] GenerateRandomSequence(Random r,int len)
        {
            int[] sequence = new int[len];
            for (int i = 0; i < len; ++i)
                sequence[i] = r.Next(int.MaxValue);
            return sequence;
        } 
        
        public static int[] ReadKeys(BinaryReader reader)
        {
            int[] keys = new int[18];
            for (int i = 0; i < 18; ++i)
                keys[i] = reader.ReadInt32();
            return keys;
        }

        public static int[,] ReadMatrix(BinaryReader reader)
        {
            int[,] matrix = new int[4, 256];
            for(int i = 0; i<4;++i)
                for (int j = 0; j < 256; j++)
                    matrix[i, j] = reader.ReadInt32();
            return matrix;
        }

        public static void ReadBlock(Tuple tuple,FileStream fstream)
        {
            byte[] integer = new byte[4];
            fstream.Read(integer, 0, 4);
            tuple.le = BitConverter.ToInt32(integer,0);
            fstream.Read(integer,0,4);
            tuple.re = BitConverter.ToInt32(integer,0);
        }


        public static void ProcessBlock(Tuple tuple, int[] keys, int[,] matrix,int count)
        {
            for (int i = 0; i < count-2; ++i)
                Round(tuple,keys[i],matrix);
            FinalSwap(tuple, keys[count-1], keys[count-2]);
        }
        
        public static void FinalSwap(Tuple tuple, int key1, int key2)
        {
            int temp = tuple.le ;
            tuple.le = tuple.re ^ key1;
            tuple.re = temp ^ key2;
        }
        public static void Round(Tuple tuple,int key,int[,]matrix)
        {
            int lek = tuple.le ^ key;
            int se = Fs(lek, matrix);
            tuple.le = tuple.re^se;
            tuple.re = lek;
        }
        
        public static int Fs(int lek, int[,] matrix)
        {
            int s1 = matrix[0, (lek >> 0) & 0b011111111];
            int s2 = matrix[1, (lek >> 8) & 0b011111111];
            int s3 = matrix[2, (lek >> 16) & 0b011111111];
            int s4 = matrix[3, (lek >> 24) & 0b011111111];
            return ((s1 + s2) ^ s3) + s4;
        }
    }

    public class Tuple
    {
        public int le;
        public int re;
    }
    
}
