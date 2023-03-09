using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace PX
{
    public static class AdressFetch
    {
        public static unsafe UIntPtr GetAdress(this object obj)
        {
            TypedReference typedReference = __makeref(obj);
            UIntPtr adress = **(UIntPtr**)(&typedReference);

            return adress;
        }
    }



    public class Steam : IDisposable
    {
        private SteamUser _profileMine = new SteamUser();
        private SteamContext _context = new SteamContext();
        //private IntPtr _contextAdress = IntPtr.Zero;
        //private GCHandle handle;
      //  public SteamContext Context { get => _context; }


      [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamConstruct(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamDestruct(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern bool PXSteamInitialize(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamShutdown(SteamContext* steamContext);

        [DllImport("PXSteam.dll")] private static unsafe extern bool PXSteamUserFetchMe(SteamContext* steamContext, SteamUserRaw* steamUser);
        //[DllImport("PXSteam.dll")] private static extern bool PXSteamUserFetchMe(IntPtr steamContext, IntPtr steamUser);


        [DllImport("PXSteam.dll")] private static unsafe extern uint PXSteamFriendsFetch(SteamContext* pxSteam, ushort searchFlags);
        [DllImport("PXSteam.dll")] private static unsafe extern uint PXSteamFriendsFetchList(SteamContext* pxSteam, ushort searchFlags, SteamFriendRaw* pxSteamFriendList, uint pxSteamFriendListSize);







        //public unsafe SteamUser ProfileMine { get => ProfileMyself(); }
        //public bool IsInitialized { get; private set; }


        public unsafe Steam()
        {
            
        }

        public unsafe bool Initialize()
        {
            bool sucess = false;

            //handle = GCHandle.Alloc(_context, GCHandleType.Pinned);
            //_contextAdress = GCHandle.ToIntPtr(handle);

            //TypedReference typedReference = __makeref(_context);
            //_contextAdress = **(UIntPtr**)(&typedReference);

            fixed(SteamContext* steamContext = &_context)
            {
                PXSteamConstruct(steamContext);
                sucess = PXSteamInitialize(steamContext);
            }

            return sucess;
        }

        public unsafe void Shutdown()
        {
            fixed (SteamContext* steamContext = &_context)
            {
                PXSteamShutdown(steamContext);
                PXSteamDestruct(steamContext);
            }          

            //handle.Free();
        }

        public unsafe SteamUser ProfileMyself()
        {
            SteamUserRaw steamUserRaw = new SteamUserRaw();

            fixed (SteamContext* steamContext = &_context)
            {
                SteamUserRaw* steamUserAdress = &steamUserRaw;

                bool successful = PXSteamUserFetchMe(steamContext, steamUserAdress);

                if (successful)
                {
                    _profileMine.Set(steamUserRaw);
                }
            }
       
            return _profileMine;
        }



        public unsafe List<SteamFriend> FriendsFetch(SteamFriendSearchFilter friendSearchFilter)
        {
            ushort flags = friendSearchFilter.FlagID;
            uint amount = 0;
            SteamFriendRaw[] steamFriendRawList = null;
            List<SteamFriend> steamFriends = null;

            fixed (SteamContext* steamContext = &_context)
            {
                amount = PXSteamFriendsFetch(steamContext, flags);

                steamFriendRawList = new SteamFriendRaw[amount];

                fixed (SteamFriendRaw* listAdress = &steamFriendRawList[0])
                {
                    PXSteamFriendsFetchList(steamContext, flags, listAdress, amount);
                }
            }

            steamFriends = new List<SteamFriend>((int)amount);

            foreach (SteamFriendRaw steamFriendRaw in steamFriendRawList)
            {
                SteamFriend steamFriend = new SteamFriend();

                steamFriend.Set(steamFriendRaw);

                steamFriends.Add(steamFriend);
            }

            return steamFriends;
        }

        public void Dispose()
        {
            Shutdown();
        }
    }
}
