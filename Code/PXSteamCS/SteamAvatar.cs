using System;
using System.Collections.Generic;
using System.Text;

namespace PX
{
    public enum SteamAvatarSize
    {
        X32,
        X64,
        X184
    }

    public unsafe struct SteamAvatarRaw
    {
        public void* Data;
        public uint DataSize;
        public char SideLength;

        public void Set(void* data, uint dataSize, SteamAvatarSize imageSize)
        {
            Data = data;
            DataSize = dataSize;

            switch (imageSize)
            {
                case SteamAvatarSize.X32:
                    SideLength = (char)32;
                    break;
                case SteamAvatarSize.X64:
                    SideLength = (char)64;
                    break;
                case SteamAvatarSize.X184:
                    SideLength = (char)184;
                    break;
                default:
                    SideLength = (char)0;
                    break;
            }        
        }
    }

    public class SteamAvatar
    {        
        public uint SideLength { get; protected set; }
        public uint Width { get => SideLength; }
        public uint Height { get => SideLength; }
        public byte[] Data { get; protected set; }
        public uint DataSize { get; protected set; }

        public SteamErrorCode Code { get; set; }

        public SteamAvatar()
        {
            SideLength = 0;
            Data = null;
            DataSize = 0;
        }

        public unsafe void Set(SteamAvatarRaw steamAvatarRaw)
        {
            SideLength = steamAvatarRaw.SideLength;
            Data = new byte[steamAvatarRaw.DataSize];
            DataSize = steamAvatarRaw.DataSize;

            for (int i = 0; i < steamAvatarRaw.DataSize; i++)
            {
                Data[i] = ((byte*)steamAvatarRaw.Data)[i];
            }
        }
    }
}
