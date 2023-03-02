using System;

namespace PXSteamCLITest
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("[C#] PX Steam test starting...");

            {

                Console.WriteLine("Creating object..");

                PX.Stream stream = new PX.Stream();

                Console.WriteLine("Initialize..");

                {
                    bool result = stream.Initialize();

                    if (!result)
                    {
                        Console.WriteLine("Initialize failed!");
                        return;
                    }

                    Console.WriteLine("User deteced: " + stream.ProfileName);
                }

                stream.Dispose();

                Console.WriteLine("Dispose");
            }

            Console.WriteLine("Finished");
        }
    }
}
