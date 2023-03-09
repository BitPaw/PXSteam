#include "PXSteam.h"

#include <Steam/steam_api.h>
#include <Steam/isteamutils.h>
#include <Steam/isteamuser.h>
#include <string.h>

#define PXSteamIDBlockFromID(id) (*(CSteamID*)&id)
#define PXSteamIDBlockToID(block) (*(__int64*)&block)


unsigned int PXSteamNameCopy(const void* __restrict const source, void* __restrict destination, const unsigned int destinationMaxSize)
{
	// Check if call is valid
	{
		const unsigned char validCall = source && destination && destinationMaxSize;

		if (!validCall)
		{
			return 0;
		}
	}

	unsigned int i = 0;

	while ((i < destinationMaxSize) && (((unsigned char*)source)[i] != '\0'))
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		++i;
	}

	((unsigned char*)destination)[i] = '\0';

	return i;
}

void PXSteamMemoryClear(void* __restrict const target, const unsigned int targetSize)
{
	for (size_t i = 0; i < targetSize; ++i)
	{
		((unsigned char*)target)[i] = 0;
	}
}

void PXSteamConstruct(PXSteam* const pxSteam)
{
    PXSteamMemoryClear(pxSteam, sizeof(PXSteam));
}

void PXSteamDestruct(PXSteam* const pxSteam)
{
}

PXSteamBool PXSteamInitialize(PXSteam* const pxSteam)
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

	pxSteam->State = PXSteamStateInit;

	// Extended init
	{
		pxSteam->Friends = SteamFriends();
		pxSteam->User = SteamUser();
		pxSteam->Utility = SteamUtils();
	}

	pxSteam->State = PXSteamStateLinked;

	return true;
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
		case k_EFriendRelationshipNone:
			return PXSteamFriendRelationshipNone;

		case k_EFriendRelationshipBlocked:
			return PXSteamFriendRelationshipBlocked;

		case k_EFriendRelationshipRequestRecipient:
			return PXSteamFriendRelationshipRequestRecipient;

		case k_EFriendRelationshipFriend:
			return PXSteamFriendRelationshipFriend;

		case k_EFriendRelationshipRequestInitiator:
			return PXSteamFriendRelationshipRequestInitiator;

		case k_EFriendRelationshipIgnored:
			return PXSteamFriendRelationshipIgnored;

		case k_EFriendRelationshipIgnoredFriend:
			return PXSteamFriendRelationshipIgnoredFriend;

		case k_EFriendRelationshipSuggested_DEPRECATED:
			return PXSteamFriendRelationshipSuggested_DEPRECATED;

		default:
			return PXSteamFriendshipStatusInvalid;
	}
}

PXSteamBool PXSteamProfileNameFetch(PXSteam* const pxSteam, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* writtenSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const char* const name = steamFriends->GetPersonaName();

	*writtenSize = PXSteamNameCopy(name, outputBuffer, outputBufferSize);

	return 	1;
}

PXSteamBool PXSteamProfileNameSet(PXSteam* const pxSteam, const void* const inputBuffer, const unsigned int inputBufferSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;

	const SteamAPICall_t result = steamFriends->SetPersonaName((char*)inputBuffer);

	return 0;
}

unsigned int PXSteamProfileLevel(PXSteam* const pxSteam)
{
	ISteamUser* const steamUser = (ISteamUser*)pxSteam->User;
	const int level = steamUser->GetPlayerSteamLevel();

	return level;
}

PXSteamID PXSteamProfileID(PXSteam* const pxSteam)
{
	ISteamUser* const steamUser = (ISteamUser*)pxSteam->User;
	const CSteamID steamID = steamUser->GetSteamID();
	const PXSteamID pxSteamID = PXSteamIDBlockToID(steamID);

	return pxSteamID;
}

PXSteamUserActiveState PXSteamProfileState(PXSteam* const pxSteam)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const EPersonaState state = steamFriends->GetPersonaState();
	const PXSteamUserActiveState pxSteamUserActiveState = PXSteamProfileStateFromID(state);

	return pxSteamUserActiveState;
}

unsigned int PXSteamFriendsFetch(PXSteam* const pxSteam, const unsigned short searchFlags)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const int numberOfMatches = steamFriends->GetFriendCount(searchFlags);

	if (numberOfMatches == -1)
	{
		return 0;
	}

	return numberOfMatches;
}

PXSteamFriendshipStatus PXSteamFriendsRelationship(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const EFriendRelationship relation = steamFriends->GetFriendRelationship(steamID);
	const PXSteamFriendshipStatus pxSteamFriendshipStatus = PXSteamFriendshipStatusFromID(relation);

	return pxSteamFriendshipStatus;
}

PXSteamUserActiveState PXSteamFriendsPersonaState(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const EPersonaState personaState = steamFriends->GetFriendPersonaState(steamID);
	const PXSteamUserActiveState pxSteamUserActiveState = PXSteamProfileStateFromID(personaState);

	return pxSteamUserActiveState;
}

PXSteamBool PXSteamFriendsName(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* const outputBufferWritten)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const char* name = steamFriends->GetFriendPersonaName(steamID);

	*outputBufferWritten = PXSteamNameCopy(name, outputBuffer, outputBufferSize);

	return name != nullptr;
}

PXSteamBool PXSteamFriendsGamePlayed(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, PXSteamFriendGameInfo* const pxSteamFriendGameInfoList)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
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
	}
	else
	{
		PXSteamMemoryClear(pxSteamFriendGameInfoList, sizeof(PXSteamFriendGameInfo));
	}

	return sucessful;
}

int PXSteamFriendsSteamLevel(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const int level = steamFriends->GetFriendSteamLevel(steamID);

	return level;
}

PXSteamBool PXSteamFriendsNickname(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* const outputBufferWritten)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamUserID);
	const char* const name = steamFriends->GetPlayerNickname(steamID);

	if (name)
	{
		*outputBufferWritten = PXSteamNameCopy(name, outputBuffer, outputBufferSize);
	}
	else
	{
		*outputBufferWritten = 0;
		PXSteamMemoryClear(outputBuffer, outputBufferSize);
	}

	return 0;
}

unsigned int PXSteamFriendsGroupCount(PXSteam* const pxSteam)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const int friendsGroupCount = steamFriends->GetFriendsGroupCount();

	return friendsGroupCount;
}

PXSteamBool PXSteamFriendsGroupName(PXSteam* const pxSteam, const PXSteamFriendsGroupID friendsGroupID, void* const outputBuffer, const unsigned int outputBufferSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const char* groupName = steamFriends->GetFriendsGroupName(friendsGroupID);

	PXSteamNameCopy(groupName, outputBuffer, outputBufferSize);

	return 1u;
}

unsigned int PXSteamFriendsGroupMembersCount(PXSteam* const pxSteam, const PXSteamFriendsGroupID friendsGroupID)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	unsigned int number = steamFriends->GetFriendsGroupMembersCount(friendsGroupID);

	return number;
}

PXSteamBool PXSteamUserFetchMe(PXSteam* const pxSteam, PXSteamUser* const pxSteamUser)
{
	if (pxSteam->State != PXSteamStateLinked)
	{
		PXSteamMemoryClear(pxSteamUser, sizeof(PXSteamUser));
		return 0u;
	}

	PXSteamProfileNameFetch(pxSteam, pxSteamUser->NameProfile, 64, &pxSteamUser->NameProfileLength);
	pxSteamUser->ID = PXSteamProfileID(pxSteam);
	pxSteamUser->Level = PXSteamProfileLevel(pxSteam);
	pxSteamUser->State = PXSteamProfileState(pxSteam);

	return 1;
}

PXSteamBool PXSteamFriendCheck(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iFriendFlags)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDFriend);
	const bool has = steamFriends->HasFriend(steamID, iFriendFlags);

	return has;
}

unsigned int PXSteamClanCount(PXSteam* const pxSteam)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const unsigned int count = steamFriends->GetClanCount();

	return count;
}

PXSteamID PXSteamClanByIndex(PXSteam* const pxSteam, int iClan)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = steamFriends->GetClanByIndex(iClan);
	const PXSteamID pxSteamID = PXSteamIDBlockToID(steamID);

	return pxSteamID;
}

PXSteamBool PXSteamClanName(PXSteam* const pxSteam, const PXSteamID pxSteamID, void* const outputBuffer, const unsigned int outputBufferSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamID);
	const char* clanName = steamFriends->GetClanName(steamID);

	PXSteamNameCopy(clanName, outputBuffer, outputBufferSize);

	return 1u;
}

PXSteamBool PXSteamClanTag(PXSteam* const pxSteam, const PXSteamID pxSteamID, void* const outputBuffer, const unsigned int outputBufferSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamID);
	const char* clanName = steamFriends->GetClanTag(steamID);

	PXSteamNameCopy(clanName, outputBuffer, outputBufferSize);

	return 1u;
}

PXSteamBool PXSteamClanActivityCounts(PXSteam* const pxSteam, const PXSteamID pxSteamID, int* pnOnline, int* pnInGame, int* pnChatting)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(pxSteamID);


	return 1u;
}

unsigned int PXSteamFriendCountFromSource(PXSteam* const pxSteam, const PXSteamID steamIDSource)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDSource);
	const int count = steamFriends->GetFriendCountFromSource(steamID);

	return count;
}

PXSteamID PXSteamFriendFromSourceByIndex(PXSteam* const pxSteam, const PXSteamID steamIDSource, int iFriend)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDSource);
	const CSteamID friendID = steamFriends->GetFriendFromSourceByIndex(steamID, iFriend);
	const PXSteamUserID pxfriendID = PXSteamIDBlockToID(steamID);

	return pxfriendID;
}

PXSteamBool PXSteamIsUserInSource(PXSteam* const pxSteam, const PXSteamID pxSteamID, const PXSteamID steamIDSource)
{
	return 0;
}

void PXSteamSetInGameVoiceSpeaking(PXSteam* const pxSteam, const PXSteamID pxSteamID, bool bSpeaking)
{
}

void PXSteamActivateGameOverlay(PXSteam* const pxSteam, const char* pchDialog)
{
}

void PXSteamActivateGameOverlayToUser(PXSteam* const pxSteam, const char* pchDialog, const PXSteamID steamID)
{
}

void ActivateGameOverlayToWebPage(PXSteam* const pxSteam, const char* pchURL, EActivateGameOverlayToWebPageMode eMode)
{
}

void PXSteamActivateGameOverlayToStore(PXSteam* const pxSteam, AppId_t nAppID, EOverlayToStoreFlag eFlag)
{
}

void PXSteamSetPlayedWith(PXSteam* const pxSteam, const PXSteamID pxSteamIDPlayedWith)
{
}

void PXSteamActivateGameOverlayInviteDialog(PXSteam* const pxSteam, const PXSteamID steamIDLobby)
{
}

PXSteamBool PXSteamFriendAvatarFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, PXSteamAvatar* const pxSteamAvatar)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	ISteamUtils* const steamUtility = (ISteamUtils*)pxSteam->Utility;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDFriend);

	int imageID;

	switch (pxSteamAvatar->SideLength)
	{
		case 32u:
			imageID = steamFriends->GetSmallFriendAvatar(steamID);
			break;

		case 64u:
			imageID = steamFriends->GetMediumFriendAvatar(steamID);
			break;

		case 184u:
			imageID = steamFriends->GetLargeFriendAvatar(steamID);
			break;

		default:
			return -1; // not a valid size
	}

	// check if big engougn
	{
		const bool isBigEnough = pxSteamAvatar->DataSize >= pxSteamAvatar->SideLength * 8;

		if (!isBigEnough)
		{
			return -3;
		}
	}

	const bool sucessful = steamUtility->GetImageRGBA(imageID, (uint8*)pxSteamAvatar->Data, pxSteamAvatar->DataSize);

	if (!sucessful)
	{
		return -2;
	}

	return 0;
}

PXSteamImageHandle PXSteamFriendAvatar32(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDFriend);
	const PXSteamImageHandle imageID = steamFriends->GetSmallFriendAvatar(steamID);

	return imageID;
}

PXSteamImageHandle PXSteamFriendAvatar64(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDFriend);
	const PXSteamImageHandle imageID = steamFriends->GetSmallFriendAvatar(steamID);

	return imageID;
}

PXSteamImageHandle PXSteamFriendAvatar184(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const CSteamID steamID = PXSteamIDBlockFromID(steamIDFriend);
	const PXSteamImageHandle imageID = steamFriends->GetSmallFriendAvatar(steamID);

	return imageID;
}

PXSteamBool PXSteamRequestUserInformation(PXSteam* const pxSteam, const PXSteamID pxSteamID, const PXSteamBool bRequireNameOnly)
{
	return 0;
}

__int64 PXSteamRequestClanOfficerList(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

const PXSteamID PXSteamGetClanOwner(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

int PXSteamGetClanOfficerCount(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

const PXSteamID PXSteamGetClanOfficerByIndex(PXSteam* const pxSteam, const PXSteamID pxSteamID, int iOfficer)
{
	return 0;
}

unsigned int PXSteamGetUserRestrictions(PXSteam* const pxSteam)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const unsigned int restrictionFlags = steamFriends->GetUserRestrictions();

	return restrictionFlags;
}

unsigned short PXSteamFriendsGroupIDByIndex(PXSteam* const pxSteam, const unsigned int index)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
	const FriendsGroupID_t friendsGroupID = steamFriends->GetFriendsGroupIDByIndex(index);

	return friendsGroupID;
}

unsigned int PXSteamFriendsFetchList(PXSteam* const pxSteam, const unsigned short searchFlags, PXSteamFriend* const pxSteamFriendList, const unsigned int pxSteamFriendListSize)
{
	ISteamFriends* const steamFriends = (ISteamFriends*)pxSteam->Friends;
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

		pxSteamFriend->User.ID = userID;
		pxSteamFriend->User.State = PXSteamFriendsPersonaState(pxSteam, userID);
		pxSteamFriend->User.Level = PXSteamFriendsSteamLevel(pxSteam, userID);
		PXSteamFriendsName(pxSteam, userID, pxSteamFriend->User.NameProfile, 64, &pxSteamFriend->User.NameProfileLength);

		pxSteamFriend->Friendship = PXSteamFriendsRelationship(pxSteam, userID);
		pxSteamFriend->IsInGame = PXSteamFriendsGamePlayed(pxSteam, userID, &pxSteamFriend->GameInfo);
		PXSteamFriendsNickname(pxSteam, userID, pxSteamFriend->NameNick, 64, &pxSteamFriend->NameNickLength);
	}

	return numberOfResults;
}

PXSteamBool PXSteamRichPresenceChange(PXSteam* const pxSteam, const char* pchKey, const char* pchValue)
{
	return 0;
}

void PXSteamClearRichPresence(PXSteam* const pxSteam)
{
}

PXSteamBool PXSteamFriendRichPresenceFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchKey, void* const outputBuffer, const unsigned int outputBufferSize)
{
	return 0;
}

int PXSteamFriendRichPresenceKeyCountFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, void* const outputBuffer, const unsigned int outputBufferSize)
{
	return 0;
}

PXSteamBool PXSteamFriendRichPresenceKeyByIndex(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iKey)
{
	return 0;
}

void PXSteamRequestFriendRichPresence(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
}

PXSteamBool PXSteamUserInviteToGame(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchConnectString)
{
	return 0;
}

int PXSteamGetCoplayFriendCount(PXSteam* const pxSteam)
{
	return 0;
}

PXSteamID PXSteamGetCoplayFriend(PXSteam* const pxSteam, int iCoplayFriend)
{
	return 0;
}

int PXSteamGetFriendCoplayTime(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
	return 0;
}

unsigned int PXSteamGetFriendCoplayGame(PXSteam* const pxSteam, const PXSteamID steamIDFriend)
{
	return 0;
}

__int64 PXSteamJoinClanChatRoom(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

PXSteamBool PXSteamLeaveClanChatRoom(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

int PXSteamGetClanChatMemberCount(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

PXSteamID PXSteamGetChatMemberByIndex(PXSteam* const pxSteam, const PXSteamID pxSteamID, int iUser)
{
	return 0;
}

PXSteamBool PXSteamSendClanChatMessage(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, const char* pchText)
{
	return 0;
}

int PXSteamGetClanChatMessage(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, int iMessage, void* prgchText, int cchTextMax, EChatEntryType* peChatEntryType, STEAM_OUT_STRUCT() const PXSteamID* psteamidChatter)
{
	return 0;
}

PXSteamBool PXSteamIsClanChatAdmin(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, const PXSteamID pxSteamID)
{
	return 0;
}

PXSteamBool PXSteamIsClanChatWindowOpenInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat)
{
	return 0;
}

PXSteamBool PXSteamOpenClanChatWindowInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat)
{
	return 0;
}

PXSteamBool PXSteamCloseClanChatWindowInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat)
{
	return 0;
}

PXSteamBool PXSteamSetListenForFriendsMessages(PXSteam* const pxSteam, bool bInterceptEnabled)
{
	return 0;
}

PXSteamBool PXSteamReplyToFriendMessage(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchMsgToSend)
{
	return 0;
}

int PXSteamGetFriendMessage(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iMessageID, void* pvData, int cubData, EChatEntryType* peChatEntryType)
{
	return 0;
}

__int64 PXSteamGetFollowerCount(PXSteam* const pxSteam, const PXSteamID steamID)
{
	return 0;
}

__int64 PXSteamIsFollowing(PXSteam* const pxSteam, const PXSteamID steamID)
{
	return 0;
}

__int64 PXSteamEnumerateFollowingList(PXSteam* const pxSteam, unsigned int unStartIndex)
{
	return 0;
}

PXSteamBool PXSteamIsClanPublic(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

PXSteamBool PXSteamIsClanOfficialGameGroup(PXSteam* const pxSteam, const PXSteamID pxSteamID)
{
	return 0;
}

int PXSteamGetNumChatsWithUnreadPriorityMessages(PXSteam* const pxSteam)
{
	return 0;
}

void PXSteamActivateGameOverlayRemotePlayTogetherInviteDialog(PXSteam* const pxSteam, const PXSteamID steamIDLobby)
{
}

PXSteamBool PXSteamRegisterProtocolInOverlayBrowser(PXSteam* const pxSteam, const char* pchProtocol)
{
	return 0;
}

void PXSteamActivateGameOverlayInviteDialogConnectString(PXSteam* const pxSteam, const char* pchConnectString)
{
}

__int64 PXSteamRequestEquippedProfileItems(PXSteam* const pxSteam, const PXSteamID steamID)
{
	return 0;
}

PXSteamBool PXSteamBHasEquippedProfileItem(PXSteam* const pxSteam, const PXSteamID steamID, ECommunityProfileItemType itemType)
{
	return 0;
}

PXSteamBool PXSteamGetProfileItemPropertyString(PXSteam* const pxSteam, const PXSteamID steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop, void* const outputBuffer, const unsigned int outputBufferSize)
{
	return 0;
}

unsigned int PXSteamGetProfileItemPropertyUint(PXSteam* const pxSteam, const PXSteamID steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop)
{
	return 0;
}