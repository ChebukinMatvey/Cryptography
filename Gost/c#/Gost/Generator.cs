using System;
using System.IO;
using Gost;

namespace Generator
{
    public static class Generator
    {
        delegate void function( int[] array,int pos1,int pos2) ;

        public static void Generate()
        {
            BinaryWriter writer = new BinaryWriter(new FileStream(Program.MAIN_INFORATION_FILE,FileMode.OpenOrCreate));
            GenerateKeys(writer);
            GenerateMatrix(writer);
            writer.Close();
        }
        
        public static void GenerateMatrix(BinaryWriter writer)
        {
            int[] row = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
            for (int i = 0; i < 8; i++)
            {
                Shuffle(row);
                for (int j = 0; j < 16; j++)
                    writer.Write(row[j]);
            }
        }

        public static void GenerateKeys(BinaryWriter writer)
        {
            Random random = new Random();
            for (int i = 0; i < 8; i++)
                writer.Write(random.Next(int.MaxValue));
        }

        private static void Shuffle(int[] data )
        {
            Random random = new Random();

            function swap = (values, pos1, pos2) =>
            {
                int temp =  values[pos1];
                values[pos1] = values[pos2];
                values[pos2] = temp;
            };
            
            Int32[] array = new int[16];
            
            for (int i = 0; i < 16; i++)
            {
                array[i] = random.Next(int.MaxValue);
            }
            
            for(int i = 0;i < data.Length;++i)
            for (int j = 0; j < data.Length - i -1; j++)
                if (array[j].CompareTo(array[j + 1]) > 0)
                {
                    swap(array, j, j + 1);
                    swap(data, j, j + 1);           
                }
        }
    }

}