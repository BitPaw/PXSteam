#include "PXSteam.h"

#include <OS/Memory/PXMemory.h>
#include <Text/PXText.h>

#include <Steam/steam_api.h>

#define PXSteamIDBlockFromID(id) (*(CSteamID*)&id)
#define PXSteamIDBlockToID(block) (*(__int64*)&block)

void PXSteamConstruct(PXSteam* const pxSteam)
{
    MemoryClear(pxSteam, sizeof(PXSteam));
}

void PXSteamDestruct(PXSteam* const pxSteam)
{
}

bool PXSteamInitialize(PXSteam* const pxSteam)
{
	// Create file "steam_appid.txt" with ID "480" as the content. Needed for init.
	// This file is for debuggin only and is forbidden in release builds.
	{
		pxSteam->AppID = 480;
	}

	// if not called over steam, start steam first and call this application over steam.
#if 0
	{
		const bool restartNeeded = SteamAPI_RestartAppIfNecessary(pxSteam->AppID);

		if (restartNeeded)
		{
			return true; // Restart as fast a spossible, program will be restarted by steam.
		}

		// Proceed..
	}
#endif

	// init
	{
		const bool sucessful = SteamAPI_Init();

		if (!sucessful)
		{
			return false; // Steam is not running, cannot link.
		}
	}

	// Extended init
	{
		
	}

    return false;
}

void PXSteamShutdown(PXSteam* const pxSteam)
{
	SteamAPI_Shutdown();
}

PXSteamUserActiveState PXSteamProfileStateFromID(const unsigned char stateID)
{
	switch (stateID)
	{
		case k_EPersonaStateOffline:
			return PXSteamUserActiveStateOffline;

		case k_EPersonaStateOnline: 
			return PXSteamUserActiveStateOnline;

		case k_EPersonaStateBusy:
			return PXSteamUserActiveStateBusy;

		case k_EPersonaStateAway:
			return PXSteamUserActiveStateAway;

		case k_EPersonaStateSnooze: 
			return PXSteamUserActiveStateSnooze;

		case k_EPersonaStateLookingToTrade: 
			return PXSteamUserActiveStateLookingToTrade;

		case k_EPersonaStateLookingToPlay: 
			return PXSteamUserActiveStateLookingToPlay;

		case k_EPersonaStateInvisible: 
			return PXSteamUserActiveStateInvisible;

		case k_EPersonaStateMax:
		default:
			return PXSteamUserActiveStateInvalid;
	}
}

PXSteamFriendshipStatus PXSteamFriendshipStatusFromID(const unsigned char stateID)
{
	switch (stateID)
	{
		default:
			return PXSteamFriendshipStatusInvalid;
	}
}

unsigned char PXSteamProfileNameFetch(PXSteam* const pxSteam, void* const exportBuffer, const unsigned int exportBufferSize)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const char* const name = steamFriends->GetPersonaName();

	PXTextCopyA(name, -1, (char*)exportBuffer, exportBufferSize);

	return 0;
}

unsigned char PXSteamProfileNameSet(PXSteam* const pxSteam, const void* const inputBuffer, const unsigned int inputBufferSize)
{
	ISteamFriends* const steamFriends = SteamFriends();

	const SteamAPICall_t result = steamFriends->SetPersonaName((char*)inputBuffer);

	return 0;
}

PXSteamUserActiveState PXSteamProfileState(PXSteam* const pxSteam)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const EPersonaState state = steamFriends->GetPersonaState();
	const PXSteamUserActiveState pxSteamUserActiveState = PXSteamProfileStateFromID(state);

	return pxSteamUserActiveState;
}

unsigned int PXSteamFriendsFetch(PXSteam* const pxSteam, const unsigned short searchFlags)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const int numberOfMatches = steamFriends->GetFriendCount(searchFlags);

	if (numberOfMatches == -1)
	{
		return 0;
	}

	return numberOfMatches;
}

PXSteamFriendshipStatus PXSteamFriendsRelationship(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const EFriendRelationship relation = steamFriends->GetFriendRelationship(steamID);	
	const PXSteamFriendshipStatus pxSteamFriendshipStatus = PXSteamFriendshipStatusFromID(relation);

	return pxSteamFriendshipStatus;
}

PXSteamUserActiveState PXSteamFriendsPersonaState(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const EPersonaState personaState = steamFriends->GetFriendPersonaState(steamID);
	const PXSteamUserActiveState pxSteamUserActiveState = PXSteamProfileStateFromID(personaState);

	return pxSteamUserActiveState;
}

unsigned char PXSteamFriendsName(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, const void* outputBuffer, const unsigned int outputBufferSize)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const char* name = steamFriends->GetFriendPersonaName(steamID);

	PXTextCopyA(name, -1, (char*)outputBuffer, outputBufferSize);

	return 0;
}

unsigned char PXSteamFriendsGamePlayed(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, PXSteamFriendGameInfo* const pxSteamFriendGameInfoList)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);

	FriendGameInfo_t friendGameInfo_t;

	const bool sucessful = steamFriends->GetFriendGamePlayed(steamID, &friendGameInfo_t);

	if (sucessful)
	{
		pxSteamFriendGameInfoList->GameID = PXSteamIDBlockToID(friendGameInfo_t.m_gameID);
		pxSteamFriendGameInfoList->SteamIDLobby = PXSteamIDBlockToID(friendGameInfo_t.m_steamIDLobby);
		pxSteamFriendGameInfoList->GameIP = friendGameInfo_t.m_unGameIP;
		pxSteamFriendGameInfoList->GamePort = friendGameInfo_t.m_usGamePort;
		pxSteamFriendGameInfoList->QueryPort = friendGameInfo_t.m_usQueryPort;
		return 1;
	}
	else
	{
		MemoryClear(pxSteamFriendGameInfoList, sizeof(PXSteamFriendGameInfo));
		return 0;
	}
}

int PXSteamFriendsSteamLevel(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const int level = steamFriends->GetFriendSteamLevel(steamID);

	return level;
}

unsigned char PXSteamFriendsNickname(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, const void* outputBuffer, const unsigned int outputBufferSize)
{
	ISteamFriends* const steamFriends = SteamFriends();
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const char* const name = steamFriends->GetPlayerNickname(steamID);

	PXTextCopyA(name, -1, (char*)outputBuffer, outputBufferSize);

	return 0;
}

unsigned int PXSteamFriendsFetchList(PXSteam* const pxSteam, const unsigned short searchFlags, PXSteamFriend* const pxSteamFriendList, const unsigned int pxSteamFriendListSize)
{
	ISteamFriends* const steamFriends = SteamFriends();

	const unsigned int numberOfResults = PXSteamFriendsFetch(pxSteam, searchFlags);

	if (numberOfResults == -1)
	{
		return -1;
	}

	for (size_t i = 0; i < numberOfResults; ++i)
	{
		const CSteamID steamID = steamFriends->GetFriendByIndex(i, searchFlags);
		const PXSteamUserID userID = PXSteamIDBlockToID(steamID);

		PXSteamFriend* const pxSteamFriend = &pxSteamFriendList[i];

		pxSteamFriend->ID = userID;
		pxSteamFriend->Friendship = PXSteamFriendsRelationship(pxSteam, userID);
		pxSteamFriend->State = PXSteamFriendsPersonaState(pxSteam, userID);
		pxSteamFriend->IsInGame = PXSteamFriendsGamePlayed(pxSteam, userID, &pxSteamFriend->GameInfo);
		pxSteamFriend->Level = PXSteamFriendsSteamLevel(pxSteam, userID);

		PXSteamFriendsName(pxSteam, userID, pxSteamFriend->NameProfile, 64);
		PXSteamFriendsNickname(pxSteam, userID, pxSteamFriend->NameNick, 64);
	}

	return numberOfResults;
}