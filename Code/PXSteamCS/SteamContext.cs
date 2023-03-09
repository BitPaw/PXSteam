namespace PX
{    
    public unsafe struct SteamContext
    {
        public uint State;
        public uint AppID;

        public void* Friends;
        public void* User;
        public void* Utility;
    }
}