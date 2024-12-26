using System;
using System.IO;
using System.Text;
namespace ConvertAnsiToKoi
{
    class Program
    {
        static void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            string file1, file2;
            if (args.Length > 2)
            {
                file1 = args[0];
                file2 = args[1];
            }
            else
            {
                file1 = "ansi.txt";
                file2 = "KOI.txt";
            }
            ConvertFile(file1, file2);
        }
        static void ConvertFile(string inputNameFile, string
        outputNameFile)
        {
            try
            {
                var inFile = new StreamReader(new FileStream(inputNameFile, FileMode.Open), Encoding.GetEncoding(1251));
                var outFile = new StreamWriter(new FileStream(outputNameFile, FileMode.Create), Encoding.GetEncoding(21866));
                outFile.Write(inFile.ReadToEnd());
                inFile.Close();
                outFile.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}