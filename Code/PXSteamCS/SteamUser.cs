using System;
using System.Text;

namespace PX
{
    public unsafe struct SteamUserRaw
    {
        public Int64 ID;
        public uint State;
        public uint Level;
        public fixed sbyte NameProfile[64];
        public uint NameProfileLength;
    }

    public class SteamUser
    {
        public Int64 ID { get; protected set; }
        public SteamUserActiveState State { get; protected set; }
        public uint Level { get; protected set; }
        public string NameProfile { get; protected set; }

        public SteamUser()
        {
            Set(0, SteamUserActiveState.Invalid, 0, string.Empty);
        }

        public SteamUser(Int64 id, SteamUserActiveState state, uint level, string nameProfile)
        {
            Set(id, state, level, nameProfile);
        }

        public unsafe SteamUser(SteamUserRaw steamUserRaw)
        {
            Set(steamUserRaw);
        }

        public unsafe void Set(SteamUserRaw steamUserRaw)
        {
            ID = steamUserRaw.ID;
            State = (SteamUserActiveState)steamUserRaw.State;
            Level = steamUserRaw.Level;

            if (steamUserRaw.NameProfileLength > 0)
            {
                //NameProfile = new string(steamUserRaw.NameProfile, 0, (int)steamUserRaw.NameProfileLength, Encoding.UTF8);
                NameProfile = new string(steamUserRaw.NameProfile, 0, (int)steamUserRaw.NameProfileLength);
            }
            else
            {
                NameProfile = string.Empty;
            }
        }

        public void Set(Int64 id, SteamUserActiveState state, uint level, string nameProfile)
        {
            ID = id;
            State = state;
            Level = level;
            NameProfile = nameProfile;
        }
    }
}