using System;
using System.Text;

namespace PX
{
    public unsafe struct SteamFriendRaw
    {
        public Int64 ID;
        public uint State;
        public uint Level;
        public fixed sbyte NameProfile[64];
        public uint NameProfileLength;

        // Allignmant
        public uint HotAir;

        public fixed sbyte NameNick[64];
        public uint NameNickLength;
        public uint Friendship;

        public char IsInGame;
        Int64 GameID; // 64Bit
        Int64 SteamIDLobby; // 64Bit
        uint GameIP; // 32Bit
        ushort GamePort; // 16Bit
        ushort QueryPort; // 16Bit
    }

    public class SteamFriend : SteamUser
    {
        public string NameNick { get; protected set; }
        public SteamFriendshipStatus Friendship { get; protected set; }

        public bool IsInGame { get; protected set; }
        //SteamFriendGameInfo GameInfo;

        public unsafe void Set(SteamFriendRaw steamFriendRaw)
        {
            ID = steamFriendRaw.ID;
            State = (SteamUserActiveState)steamFriendRaw.State;
            Level = steamFriendRaw.Level;

            if (steamFriendRaw.NameProfileLength > 0)
            {
               // NameNick = new string(steamFriendRaw.NameNick, 0, (int)steamFriendRaw.NameNickLength, Encoding.UTF8);
                NameNick = new string(steamFriendRaw.NameNick, 0, (int)steamFriendRaw.NameNickLength);
            }
            else
            {
                NameNick = string.Empty;
            }

            if (steamFriendRaw.NameProfileLength > 0)
            {
               // NameProfile = new string(steamFriendRaw.NameProfile, 0, (int)steamFriendRaw.NameProfileLength, Encoding.UTF8);
                NameProfile = new string(steamFriendRaw.NameProfile, 0, (int)steamFriendRaw.NameProfileLength);
            }
            else
            {
                NameProfile = string.Empty;
            }

            Friendship = (SteamFriendshipStatus)steamFriendRaw.Friendship;
            IsInGame = steamFriendRaw.IsInGame != 0;
        }
    }
}