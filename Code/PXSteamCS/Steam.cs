using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace PX
{
    public class Steam : IDisposable
    {   
        //---<PXSteam C-Callbacks>---------------------------------------------
        [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamConstruct(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamDestruct(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern bool PXSteamInitialize(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static unsafe extern void PXSteamShutdown(SteamContext* steamContext);
        [DllImport("PXSteam.dll")] private static extern bool PXSteamAppIDCreateFile(uint appID);
        [DllImport("PXSteam.dll")] private static extern bool PXSteamAppIDCreateFileTest();

        [DllImport("PXSteam.dll")] private static unsafe extern bool PXSteamUserFetchMe(SteamContext* steamContext, SteamUserRaw* steamUser);
        //[DllImport("PXSteam.dll")] private static extern bool PXSteamUserFetchMe(IntPtr steamContext, IntPtr steamUser);

        [DllImport("PXSteam.dll")] private static unsafe extern uint PXSteamFriendsFetch(SteamContext* pxSteam, ushort searchFlags);
        [DllImport("PXSteam.dll")] private static unsafe extern uint PXSteamFriendsFetchList(SteamContext* pxSteam, ushort searchFlags, SteamFriendRaw* pxSteamFriendList, uint pxSteamFriendListSize);

        [DllImport("PXSteam.dll")] private static unsafe extern uint PXSteamFriendAvatarFetch(SteamContext* pxSteam, Int64 steamUserID, SteamAvatarRaw* steamAvatar);
        //---------------------------------------------------------------------

        //---------------------------------------------------------------------
        private SteamUser _profileMine = new SteamUser();
        private SteamContext _context = new SteamContext();
        //---------------------------------------------------------------------

        public void Dispose()
        {
            Shutdown();
        }

        public unsafe bool Initialize()
        {
            bool sucess = false;

            fixed (SteamContext* steamContext = &_context)
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
        }

        public static bool SteamAppIDCreateFile(uint appID)
        {
            return PXSteamAppIDCreateFile(appID);
        }

        public static bool SteamAppIDCreateFileTest()
        {
            return PXSteamAppIDCreateFileTest();
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


        public unsafe SteamAvatar UserImage(Int64 steamUserID, SteamAvatarSize steamAvatarSize)
        {
            SteamAvatarRaw steamAvatarRaw = new SteamAvatarRaw();
            SteamAvatar steamAvatar = null;

            const int imageBufferSizeMax = 184 * 184 * 4;
            byte[] imageBufferCache = new byte[imageBufferSizeMax];

            fixed (SteamContext* steamContext = &_context)
            {        
                fixed(byte* imageBufferAdress = &imageBufferCache[0])
                {
                    steamAvatarRaw.Set(imageBufferAdress, imageBufferSizeMax, steamAvatarSize);

                    steamAvatar = new SteamAvatar();
                    steamAvatar.Code = (SteamErrorCode)PXSteamFriendAvatarFetch(steamContext, steamUserID, &steamAvatarRaw);
                    steamAvatar.Set(steamAvatarRaw);
                }
            }          

            return steamAvatar;
        }
    }
}