using System;
using System.Collections;
using System.Globalization;

namespace OledHelperTool
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello Oled!");
            Console.WriteLine(ConvertHexToBitArray("0xFF"));
        }
        //  public static BitArray ConvertHexToBitArray(string hexData)
        public static string ConvertHexToBitArray(string hexData)
        {
            if (hexData == null)
                return null; // or do something else, throw, ...
            if (hexData[0] == '0' && hexData[1] == 'x') {
                string justhex = hexData.Substring(2);
                hexData = justhex;
            }
            
            BitArray ba = new BitArray(4 * hexData.Length);
            for (int i = 0; i < hexData.Length; i++)
            {
                byte b = byte.Parse(hexData[i].ToString(), NumberStyles.HexNumber);
                for (int j = 0; j < 4; j++)
                {
                    ba.Set(i * 4 + j, (b & (1 << (3 - j))) != 0);
                }
            }
            string s = "B";
            for (int x = 0; x < 4 * hexData.Length; x++) {
                s += (ba[x] == true ? "1" : "0");
            }
            return s;
        }
    }
    
}
