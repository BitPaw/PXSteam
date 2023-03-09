namespace PX
{
	public class SteamFriendSearchFilter
    {
		public bool Blocked { get; set; }
		public bool FriendshipRequested { get; set; }
		public bool Immediate { get; set; }
		public bool ClanMember { get; set; }
		public bool OnGameServer { get; set; }
		public bool RequestingFriendship { get; set; }
		public bool RequestingInfo { get; set; }
		public bool Ignored { get; set; }
		public bool IgnoredFriend { get; set; }
		public bool ChatMember { get; set; }

		public ushort FlagID
		{
            get
            {
				bool selectedAll =
					Blocked &&
					FriendshipRequested &&
					Immediate &&
					ClanMember &&
					OnGameServer &&
					RequestingFriendship &&
					RequestingInfo &&
					Ignored &&
					IgnoredFriend &&
					ChatMember;

				int extended = 
					(Blocked ? 0x01 : 0x0) |
					(FriendshipRequested ? 0x02 : 0x0) |
					(Immediate ? 0x04 : 0x0) |
					(ClanMember ?  0x08 : 0) |
					(OnGameServer ? 0x10 : 0) |
					(RequestingFriendship ? 0x80 : 0) |
					(RequestingInfo ? 0x100 : 0) |
					(Ignored ? 0x200 : 0) |
					(IgnoredFriend ? 0x400 : 0) |
					(ChatMember ? 0x1000 : 0);

				int flagID = (selectedAll ? 0xFFFF : 0x0) + ((!selectedAll) ? extended : 0x0);

				return (ushort)flagID;
			}
		}

		public SteamFriendSearchFilter() : this(false)
        {
		
		}

		public SteamFriendSearchFilter(bool defaultOption)
        {
			Blocked = defaultOption;
			FriendshipRequested = defaultOption;
			Immediate = defaultOption;
			ClanMember = defaultOption;
			OnGameServer = defaultOption;
			RequestingFriendship = defaultOption;
			RequestingInfo = defaultOption;
			Ignored = defaultOption;
			IgnoredFriend = defaultOption;
			ChatMember = defaultOption;
		}
	}
}