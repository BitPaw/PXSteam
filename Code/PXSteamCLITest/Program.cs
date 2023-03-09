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

                PX.Steam steam = new PX.Steam();

                Console.WriteLine("Initialize..");

                {
                    bool result = steam.Initialize();

                    if (!result)
                    {
                        Console.WriteLine("Initialize failed!");
                        return;
                    }

                    Console.WriteLine("User deteced: [" + steam .ProfileMine.State + "][" + steam.ProfileMine.Level + "]" + steam.ProfileMine.NameProfile);

                    SteamUser me = steam.ProfileMyself();

                    PX.SteamFriendSearchFilter steamFriendSearchFilter = new PX.SteamFriendSearchFilter(true);   
                    List<SteamFriend> firends = steam.FriendsFetch(steamFriendSearchFilter);

                    foreach (SteamUser user in firends)
                    {
                        Console.WriteLine("[" + user.State + "][" + user.Level + "] " + user.NameProfile);
                    }
                }

                steam.Dispose();

                Console.WriteLine("Dispose");
            }

            Console.WriteLine("Finished");
        }
    }
}
