using PX;
using System;
using System.Collections.Generic;

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


                    PX.SteamFriendSearchFilter steamFriendSearchFilter = new PX.SteamFriendSearchFilter(true);   
                    List<SteamUser> firends = stream.FriendsFetch(steamFriendSearchFilter);

                    foreach (SteamUser user in firends)
                    {
                        Console.WriteLine(user.NameProfile +  "[" + user.ID + "]");
                    }
                }

                stream.Dispose();

                Console.WriteLine("Dispose");
            }

            Console.WriteLine("Finished");
        }
    }
}
