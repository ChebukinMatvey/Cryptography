using System;
using System.IO;
using static Des.Functions;


namespace Des
{
    class Encryptor
    {
        public static void encrypt(string theGoalFile, string mainInformationFile, string encryptedFile)
        {
            BinaryReader info = new BinaryReader(new FileStream(mainInformationFile,FileMode.Open));
            BinaryReader goal= new BinaryReader(new FileStream(theGoalFile,FileMode.Open));
            BinaryWriter output = new BinaryWriter(new FileStream(encryptedFile,FileMode.OpenOrCreate));
            byte[] ip = readIp(info);
            byte[] reversedIp = reverseIp(ip);
            long[] keys = readKeys(info);
            byte[,] matrix = readMatrix(info);
            foreach (byte val in ip)
                output.Write(val);
            foreach (long key in keys)
                output.Write(key);
            for (int i = 0; i < matrix.GetLength(0); ++i)
                for (int j = 0; j < matrix.GetLength(1); ++j)
                    output.Write(matrix[i, j]);

            int fileSize = (int)goal.BaseStream.Length;
            output.Write(fileSize);
            
            Console.WriteLine("Count of rounds[1:16] = ");
            int rounds = Convert.ToInt32(Console.ReadLine());
            Array.Resize(ref keys,rounds);
            
            for(int i = 0; i< Math.Ceiling( fileSize/8.0); ++i){
                ulong pi = readBlock(goal);
                ulong ci = processBlock(pi, ip, reversedIp, matrix, keys);
                Console.WriteLine($"{pi}  {ci}");
                output.Write(ci);
            }
            info.Close();
            goal.Close();
            output.Close();
        }
    }
}
