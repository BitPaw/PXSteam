#include "SteamFriendSearchFilter.hpp"

#include "../../PXSteam/Source/PXSteam.h"

unsigned short PX::SteamFriendSearchFilter::FlagID::get()
{
	const bool selectedAll =
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

	const unsigned short flagID =
		((selectedAll * PXSteamFriendFlagAll))
		+
		(!selectedAll) * (
		Blocked * PXSteamFriendFlagBlocked |
		FriendshipRequested * PXSteamFriendFlagFriendshipRequested |
		Immediate * PXSteamFriendFlagImmediate |
		ClanMember * PXSteamFriendFlagClanMember |
		OnGameServer * PXSteamFriendFlagOnGameServer |
		RequestingFriendship * PXSteamFriendFlagRequestingFriendship |
		RequestingInfo * PXSteamFriendFlagRequestingInfo |
		Ignored * PXSteamFriendFlagIgnored |
		IgnoredFriend * PXSteamFriendFlagIgnoredFriend |
		ChatMember * PXSteamFriendFlagChatMember);

	return flagID;
}

PX::SteamFriendSearchFilter::SteamFriendSearchFilter()
{
	SteamFriendSearchFilter(false);
}

PX::SteamFriendSearchFilter::SteamFriendSearchFilter(bool defaultOption)
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