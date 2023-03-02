#pragma once

namespace PX
{
	public ref class SteamFriendSearchFilter
	{
		public:
		bool Blocked;
		bool FriendshipRequested;
		bool Immediate;
		bool ClanMember;
		bool OnGameServer;
		bool RequestingFriendship;
		bool RequestingInfo;
		bool Ignored;
		bool IgnoredFriend;
		bool ChatMember;

		property unsigned short FlagID { unsigned short get(); }

		SteamFriendSearchFilter();
		SteamFriendSearchFilter(bool defaultOption);
	};
}