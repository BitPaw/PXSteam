#ifndef PXSteamINCLUDE
#define PXSteamINCLUDE

#define PXSteamPrivate static
#define PXSteamPublic __declspec(dllexport)

#define PXSteamFriendFlagNone	0x00
#define PXSteamFriendFlagBlocked	0x01	// Benutzer, dessen Kontaktaufnahme mit dem aktuellen Benutzer von diesem blockiert wurde.
#define PXSteamFriendFlagFriendshipRequested	0x02	// Benutzer, die eine Freundschaftsanfrage an den aktuellen Benutzer geschickt haben.
#define PXSteamFriendFlagImmediate	0x04	// Die „regulären“ Freunde des aktuellen Benutzers.
#define PXSteamFriendFlagClanMember	0x08	// Benutzer, die sich in einer derselben(kleinen) Steam - Gruppen wie der aktuelle Benutzer befinden.
#define PXSteamFriendFlagOnGameServer	0x10	// Spieler, die sich auf demselben Spielserver befinden, wie durch SetPlayedWith festgelegt.
#define PXSteamFriendFlagRequestingFriendship	0x80	// Benutzer, an die der aktuelle Benutzer Freundschaftsanfragen geschickt hat.
#define PXSteamFriendFlagRequestingInfo	0x100	// Benutzer, die nach einem Aufruf von RequestUserInformation derzeit zusätzliche Informationen über sich selbst senden.
#define PXSteamFriendFlagIgnored	0x200	// Benutzer, deren Kontaktaufnahme der aktuelle Benutzer ignoriert hat.
#define PXSteamFriendFlagIgnoredFriend	0x400	// Benutzer, die den aktuellen Benutzer ignoriert haben, dem aktuellen Benutzer jedoch weiterhin bekannt sind.
#define PXSteamFriendFlagChatMember	0x1000	// Benutzer in einem derselben Chats.
#define PXSteamFriendFlagAll	0xFFFF	// Gibt alle Freund - Flags zurück.

#ifdef __cplusplus
extern "C"
{
#endif

	typedef unsigned char PXSteamBool;
	typedef __int64 PXSteamUserID;
	typedef __int64 PXSteamID;
	typedef unsigned short PXSteamFriendsGroupID;
	typedef int PXSteamImageHandle;

	typedef enum PXSteamState_
	{
		PXSteamStateInvalid,
		PXSteamStateInit,
		PXSteamStateLinked,
		PXSteamStateStopped
	}
	PXSteamState;

	typedef enum PXSteamUserActiveState_
	{
		PXSteamUserActiveStateInvalid,
		PXSteamUserActiveStateOffline,			// friend is not currently logged on
		PXSteamUserActiveStateOnline,			// friend is logged on
		PXSteamUserActiveStateBusy,			// user is on, but busy
		PXSteamUserActiveStateAway,			// auto-away feature
		PXSteamUserActiveStateSnooze,			// auto-away for a long time
		PXSteamUserActiveStateLookingToTrade,	// Online, trading
		PXSteamUserActiveStateLookingToPlay,	// Online, wanting to play
		PXSteamUserActiveStateInvisible		// Online, but appears offline to friends.  This status is never published to clients.
	}
	PXSteamUserActiveState;

	typedef enum PXSteamFriendshipStatus_
	{
		PXSteamFriendshipStatusInvalid,
		PXSteamFriendRelationshipNone,
		PXSteamFriendRelationshipBlocked,			// this doesn't get stored; the user has just done an Ignore on an friendship invite
		PXSteamFriendRelationshipRequestRecipient,
		PXSteamFriendRelationshipFriend,
		PXSteamFriendRelationshipRequestInitiator,
		PXSteamFriendRelationshipIgnored ,			// this is stored; the user has explicit blocked this other user from comments/chat/etc
		PXSteamFriendRelationshipIgnoredFriend ,
		PXSteamFriendRelationshipSuggested_DEPRECATED,		// was used by the original implementation of the facebook linking feature, but now unused.
	}
	PXSteamFriendshipStatus;

	typedef enum PXSteamCommunityProfileItemType_
	{
		PXSteamCommunityProfileItemTypeInvalid,
		PXSteamCommunityProfileItemType_AnimatedAvatar,
		PXSteamCommunityProfileItemType_AvatarFrame,
		PXSteamCommunityProfileItemType_ProfileModifier,
		PXSteamCommunityProfileItemType_ProfileBackground,
		PXSteamCommunityProfileItemType_MiniProfileBackground
	}
	PXSteamCommunityProfileItemType;

	typedef enum PXSteamCommunityProfileItemProperty_
	{
		PXSteamCommunityProfileItemPropertyInvalid,
		PXSteamCommunityProfileItemProperty_ImageSmall, // string
		PXSteamCommunityProfileItemProperty_ImageLarge, // string
		PXSteamCommunityProfileItemProperty_InternalName, // string
		PXSteamCommunityProfileItemProperty_Title, // string
		PXSteamCommunityProfileItemProperty_Description, // string
		PXSteamCommunityProfileItemProperty_AppID, // uint32
		PXSteamCommunityProfileItemProperty_TypeID, // uint32
		PXSteamCommunityProfileItemProperty_Class, // uint32
		PXSteamCommunityProfileItemProperty_MovieWebM, // string
		PXSteamCommunityProfileItemProperty_MovieMP4, // string
		PXSteamCommunityProfileItemProperty_MovieWebMSmall, // string
		PXSteamCommunityProfileItemProperty_MovieMP4Small, // string
	}
	PXSteamCommunityProfileItemProperty;

	typedef enum PXSteamChatEntryType_
	{
		PXSteamChatEntryTypeInvalid = 0,
		PXSteamChatEntryTypeChatMsg = 1,		// Normal text message from another user
		PXSteamChatEntryTypeTyping = 2,			// Another user is typing (not used in multi-user chat)
		PXSteamChatEntryTypeInviteGame = 3,		// Invite from other user into that users current game
		PXSteamChatEntryTypeEmote = 4,			// text emote message (deprecated, should be treated as ChatMsg)
		//PXSteamChatEntryTypeLobbyGameStart = 5,	// lobby game is starting (dead - listen for LobbyGameCreated_t callback instead)
		PXSteamChatEntryTypeLeftConversation = 6, // user has left the conversation ( closed chat window )
		// Above are previous FriendMsgType entries, now merged into more generic chat entry types
		PXSteamChatEntryTypeEntered = 7,		// user has entered the conversation (used in multi-user chat and group chat)
		PXSteamChatEntryTypeWasKicked = 8,		// user was kicked (data: 64-bit steamid of actor performing the kick)
		PXSteamChatEntryTypeWasBanned = 9,		// user was banned (data: 64-bit steamid of actor performing the ban)
		PXSteamChatEntryTypeDisconnected = 10,	// user disconnected
		PXSteamChatEntryTypeHistoricalChat = 11,	// a chat message from user's chat history or offilne message
		//PXSteamChatEntryTypeReserved1 = 12, // No longer used
		//PXSteamChatEntryTypeReserved2 = 13, // No longer used
		PXSteamChatEntryTypeLinkBlocked = 14, // a link was removed by the chat filter.
	}
	PXSteamChatEntryType;

	typedef enum PXActivateGameOverlayToWebPageMode_
	{
		PXSteamActivateGameOverlayToWebPageMode_Default = 0,		// Browser will open next to all other windows that the user has open in the overlay.
																// The window will remain open, even if the user closes then re-opens the overlay.

		PXSteamActivateGameOverlayToWebPageMode_Modal = 1			// Browser will be opened in a special overlay configuration which hides all other windows
																														// that the user has open in the overlay. When the user closes the overlay, the browser window
																														// will also close. When the user closes the browser window, the overlay will automatically close.
	}
	PXActivateGameOverlayToWebPageMode;

	typedef enum PXSteamOverlayToStoreFlag
	{
		PXSteamOverlayToStoreFlag_None = 0,
		PXSteamOverlayToStoreFlag_AddToCart = 1,
		PXSteamOverlayToStoreFlag_AddToCartAndShow = 2,
	}
	PXSteamOverlayToStoreFlag;


	typedef struct PXSteam_
	{
		PXSteamState State;
		unsigned int AppID;

		void* Friends;
		void* User;
		void* Utility;

		unsigned char Listener[64];
	}
	PXSteam;

	typedef struct PXSteamFriendGameInfo_
	{
		__int64 GameID; // 64Bit
		__int64 SteamIDLobby; // 64Bit
		unsigned int GameIP; // 32Bit
		unsigned short GamePort; // 16Bit
		unsigned short QueryPort; // 16Bit
	}
	PXSteamFriendGameInfo;

	typedef struct PXSteamUser_
	{
		PXSteamUserID ID;
		PXSteamUserActiveState State;
		unsigned int Level;
		char NameProfile[64];
		unsigned int NameProfileLength;
	}
	PXSteamUser;

	typedef struct PXSteamFriend_
	{
		PXSteamUser User;
		char NameNick[64];
		unsigned int NameNickLength;
		PXSteamFriendshipStatus Friendship;

		unsigned char IsInGame;
		PXSteamFriendGameInfo GameInfo;
	}
	PXSteamFriend;

	typedef struct PXSteamAvatar_
	{
		void* Data;
		unsigned int DataSize;
		unsigned char SideLength;
	}
	PXSteamAvatar;

	typedef enum PXSteamErrorCode
	{
		PXSteamErrorInvalid,
		PXSteamErrorSuccess,

		PXSteamErrorInvalidImageSize,
		PXSteamErrorNoImage,
		PXSteamErrorImageLoadFailed,
		PXSteamErrorInputBufferTooSmal
	}
	PXSteamErrorCode;

	typedef struct PXSteamPersonaChangeInfo_
	{
		unsigned char Name;
		unsigned char Status;
		unsigned char ComeOnline;
		unsigned char GoneOffline;
		unsigned char GamePlayed;
		unsigned char GameServer;
		unsigned char Avatar;
		unsigned char JoinedSource;
		unsigned char LeftSource;
		unsigned char RelationshipChanged;
		unsigned char NameFirstSet;
		unsigned char FacebookInfo;
		unsigned char Nickname;
		unsigned char SteamLevel;
	}
	PXSteamPersonaChangeInfo;

	//---<Core>--------------------
	PXSteamPublic void PXSteamConstruct(PXSteam* const pxSteam);
	PXSteamPublic void PXSteamDestruct(PXSteam* const pxSteam);

	PXSteamPublic PXSteamBool PXSteamInitialize(PXSteam* const pxSteam);
	PXSteamPublic void PXSteamShutdown(PXSteam* const pxSteam);
	PXSteamPublic PXSteamBool PXSteamAppIDCreateFile(const unsigned int appID);
	PXSteamPublic PXSteamBool PXSteamAppIDCreateFileTest();
	//-------------------------------------------------------------------------

	PXSteamPrivate void PXSteamMemoryClear(void* __restrict const target, const unsigned int targetSize);
	PXSteamPrivate unsigned int PXSteamNameCopy(const void* __restrict const source, void* __restrict destination, const unsigned int destinationMaxSize);

	//-------------------------------------------------------------------------
	PXSteamPublic PXSteamUserActiveState PXSteamProfileStateFromID(const unsigned char stateID);
	PXSteamPublic PXSteamFriendshipStatus PXSteamFriendshipStatusFromID(const unsigned char stateID);
	PXSteamPrivate void PXSteamPersonaChangeInfoFromID(PXSteamPersonaChangeInfo* const steamPersonaChangeInfo, unsigned short flagID);
	//-------------------------------------------------------------------------


	//---<Profile - you>-------------------------------------------------------
	// Get your profilename, formatted in UTF-8. Guranteed not to be null.
	PXSteamPublic PXSteamBool PXSteamProfileNameFetch(PXSteam* const pxSteam, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* writtenSize); // Written size?

	PXSteamPublic PXSteamBool PXSteamProfileNameSet(PXSteam* const pxSteam, const void* const inputBuffer, const unsigned int inputBufferSize);

	PXSteamPublic unsigned int PXSteamProfileLevel(PXSteam* const pxSteam);
	PXSteamPublic PXSteamID PXSteamProfileID(PXSteam* const pxSteam);

	PXSteamPublic PXSteamUserActiveState PXSteamProfileState(PXSteam* const pxSteam);


	PXSteamPublic PXSteamBool PXSteamUserFetchMe(PXSteam* const pxSteam, PXSteamUser* const pxSteamUser);
	//-------------------------------------------------------------------------


	//---<Friends>---------------------
	PXSteamPublic unsigned int PXSteamFriendsFetch(PXSteam* const pxSteam, const unsigned short searchFlags);



	PXSteamPublic PXSteamFriendshipStatus PXSteamFriendsRelationship(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);
	PXSteamPublic PXSteamUserActiveState PXSteamFriendsPersonaState(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);

	PXSteamPublic PXSteamBool PXSteamFriendsName(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* const outputBufferWritten);

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	PXSteamPublic PXSteamBool PXSteamFriendsGamePlayed(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, PXSteamFriendGameInfo* const pxSteamFriendGameInfoList);

	// accesses old friends names - returns an empty string when their are no more items in the history
	//const char* PXSteamFriendsPersonaNameHistory(const PXSteamID steamIDFriend, int iPersonaName);

	// friends steam level
	PXSteamPublic int PXSteamFriendsSteamLevel(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);

	// Returns nickname the current user has set for the specified player. Returns NULL if the no nickname has been set for that player.
	// DEPRECATED: GetPersonaName follows the Steam nickname preferences, so apps shouldn't need to care about nicknames explicitly.
	PXSteamPublic PXSteamBool PXSteamFriendsNickname(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, void* const outputBuffer, const unsigned int outputBufferSize, unsigned int* const outputBufferWritten);


	PXSteamPublic PXSteamErrorCode PXSteamFriendAvatarFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, PXSteamAvatar* const pxSteamAvatar);

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	PXSteamPublic PXSteamImageHandle PXSteamFriendAvatar32(PXSteam* const pxSteam, const PXSteamID steamIDFriend);

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	PXSteamPublic PXSteamImageHandle PXSteamFriendAvatar64(PXSteam* const pxSteam, const PXSteamID steamIDFriend);

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	PXSteamPublic PXSteamImageHandle PXSteamFriendAvatar184(PXSteam* const pxSteam, const PXSteamID steamIDFriend);





	//---<friend grouping (tag) apis>---------------------------------------------
	// returns the number of friends groups
	PXSteamPublic unsigned int PXSteamFriendsGroupCount(PXSteam* const pxSteam);

	// returns the friends group ID for the given index (invalid indices return k_FriendsGroupID_Invalid)
	PXSteamPublic unsigned short PXSteamFriendsGroupIDByIndex(PXSteam* const pxSteam, const unsigned int index);

	// returns the name for the given friends group (NULL in the case of invalid friends group IDs)
	PXSteamPublic PXSteamBool PXSteamFriendsGroupName(PXSteam* const pxSteam, const PXSteamFriendsGroupID friendsGroupID, void* const outputBuffer, const unsigned int outputBufferSize);

	// returns the number of members in a given friends group
	PXSteamPublic unsigned int PXSteamFriendsGroupMembersCount(PXSteam* const pxSteam, const PXSteamFriendsGroupID friendsGroupID);

	// gets up to nMembersCount members of the given friends group, if fewer exist than requested those positions' SteamIDs will be invalid
	//void GetFriendsGroupMembersList(FriendsGroupID_t friendsGroupID, STEAM_OUT_ARRAY_CALL(nMembersCount, GetFriendsGroupMembersCount, friendsGroupID) const PXSteamID* pOutSteamIDMembers, int nMembersCount);

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	PXSteamPublic PXSteamBool PXSteamFriendCheck(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iFriendFlags);

	// clan (group) iteration and access functions
	PXSteamPublic unsigned int PXSteamClanCount(PXSteam* const pxSteam);
	PXSteamPublic PXSteamID PXSteamClanByIndex(PXSteam* const pxSteam, int iClan);
	PXSteamPublic PXSteamBool PXSteamClanName(PXSteam* const pxSteam, const PXSteamID pxSteamID, void* const outputBuffer, const unsigned int outputBufferSize);
	PXSteamPublic PXSteamBool PXSteamClanTag(PXSteam* const pxSteam, const PXSteamID pxSteamID, void* const outputBuffer, const unsigned int outputBufferSize);
	// returns the most recent information we have about what's happening in a clan
	PXSteamPublic PXSteamBool PXSteamClanActivityCounts(PXSteam* const pxSteam, const PXSteamID pxSteamID, int* pnOnline, int* pnInGame, int* pnChatting);

	// for clans a user is a member of, they will have reasonably up-to-date information, but for others you'll have to download the info to have the latest
	//SteamAPICall_t DownloadClanActivityCounts(STEAM_ARRAY_COUNT(cClansToRequest) const PXSteamID* psteamIDClans, int cClansToRequest);

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// note that the current user must be in a lobby to retrieve const PXSteamIDs of other users in that lobby
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	PXSteamPublic unsigned int PXSteamFriendCountFromSource(PXSteam* const pxSteam, const PXSteamID steamIDSource);
	PXSteamPublic PXSteamID PXSteamFriendFromSourceByIndex(PXSteam* const pxSteam, const PXSteamID steamIDSource, int iFriend);

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	PXSteamPublic PXSteamBool PXSteamIsUserInSource(PXSteam* const pxSteam, const PXSteamID pxSteamID, const PXSteamID steamIDSource);

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	PXSteamPublic void PXSteamSetInGameVoiceSpeaking(PXSteam* const pxSteam, const PXSteamID pxSteamID, bool bSpeaking);

	// activates the game overlay, with an optional dialog to open 
	// valid options include "Friends", "Community", "Players", "Settings", "OfficialGameGroup", "Stats", "Achievements",
	// "chatroomgroup/nnnn"
	PXSteamPublic void PXSteamActivateGameOverlay(PXSteam* const pxSteam, const char* pchDialog);

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"jointrade" - opens a window to a Steam Trading session that was started with the ISteamEconomy/StartTrade Web API
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	//		"friendadd" - opens the overlay in minimal mode prompting the user to add the target user as a friend
	//		"friendremove" - opens the overlay in minimal mode prompting the user to remove the target friend
	//		"friendrequestaccept" - opens the overlay in minimal mode prompting the user to accept an incoming friend invite
	//		"friendrequestignore" - opens the overlay in minimal mode prompting the user to ignore an incoming friend invite
	PXSteamPublic void PXSteamActivateGameOverlayToUser(PXSteam* const pxSteam, const char* pchDialog, const PXSteamID steamID);

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	PXSteamPublic void ActivateGameOverlayToWebPage(PXSteam* const pxSteam, const char* pchURL, PXActivateGameOverlayToWebPageMode eMode);

	// activates game overlay to store page for app
	PXSteamPublic void PXSteamActivateGameOverlayToStore(PXSteam* const pxSteam, unsigned int nAppID, PXSteamOverlayToStoreFlag eFlag);

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is in game 
	PXSteamPublic void PXSteamSetPlayedWith(PXSteam* const pxSteam, const PXSteamID pxSteamIDPlayedWith);

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	PXSteamPublic void PXSteamActivateGameOverlayInviteDialog(PXSteam* const pxSteam, const PXSteamID steamIDLobby);



	




	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	PXSteamPublic PXSteamBool PXSteamRequestUserInformation(PXSteam* const pxSteam, const PXSteamID pxSteamID, const PXSteamBool bRequireNameOnly);

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	PXSteamPublic __int64 PXSteamRequestClanOfficerList(PXSteam* const pxSteam, const PXSteamID pxSteamID);

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	PXSteamPublic PXSteamID PXSteamGetClanOwner(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	// returns the number of officers in a clan (including the owner)
	PXSteamPublic int PXSteamGetClanOfficerCount(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	PXSteamPublic PXSteamID PXSteamGetClanOfficerByIndex(PXSteam* const pxSteam, const PXSteamID pxSteamID, int iOfficer);
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	PXSteamPublic unsigned int PXSteamGetUserRestrictions(PXSteam* const pxSteam);

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Note the following limits: k_cchMaxRichPresenceKeys, k_cchMaxRichPresenceKeyLength, k_cchMaxRichPresenceValueLength
	// There are five magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	//		"steam_display"				- Names a rich presence localization token that will be displayed in the viewing user's selected language
	//									  in the Steam client UI. For more info: https://partner.steamgames.com/doc/api/ISteamFriends#richpresencelocalization
	//		"steam_player_group"		- When set, indicates to the Steam client that the player is a member of a particular group. Players in the same group
	//									  may be organized together in various places in the Steam UI.
	//		"steam_player_group_size"	- When set, indicates the total number of players in the steam_player_group. The Steam client may use this number to
	//									  display additional information about a group when all of the members are not part of a user's friends list.
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	PXSteamPublic PXSteamBool PXSteamRichPresenceChange(PXSteam* const pxSteam, const char* pchKey, const char* pchValue);
	PXSteamPublic void PXSteamClearRichPresence(PXSteam* const pxSteam);
	PXSteamPublic PXSteamBool PXSteamFriendRichPresenceFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchKey, void* const outputBuffer, const unsigned int outputBufferSize);
	PXSteamPublic int PXSteamFriendRichPresenceKeyCountFetch(PXSteam* const pxSteam, const PXSteamID steamIDFriend, void* const outputBuffer, const unsigned int outputBufferSize);
	PXSteamPublic PXSteamBool PXSteamFriendRichPresenceKeyByIndex(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iKey);
	// Requests rich presence for a specific user.
	PXSteamPublic void PXSteamRequestFriendRichPresence(PXSteam* const pxSteam, const PXSteamID steamIDFriend);

	// Rich invite support.
	// If the target accepts the invite, a GameRichPresenceJoinRequested_t callback is posted containing the connect string.
	// (Or you can configure your game so that it is passed on the command line instead.  This is a deprecated path; ask us if you really need this.)
	PXSteamPublic PXSteamBool PXSteamUserInviteToGame(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchConnectString);

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	PXSteamPublic int PXSteamGetCoplayFriendCount(PXSteam* const pxSteam);
	PXSteamPublic PXSteamID PXSteamGetCoplayFriend(PXSteam* const pxSteam, int iCoplayFriend);
	PXSteamPublic int PXSteamGetFriendCoplayTime(PXSteam* const pxSteam, const PXSteamID steamIDFriend);
	PXSteamPublic unsigned int PXSteamGetFriendCoplayGame(PXSteam* const pxSteam, const PXSteamID steamIDFriend);

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	PXSteamPublic __int64 PXSteamJoinClanChatRoom(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	PXSteamPublic PXSteamBool PXSteamLeaveClanChatRoom(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	PXSteamPublic int PXSteamGetClanChatMemberCount(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	PXSteamPublic PXSteamID PXSteamGetChatMemberByIndex(PXSteam* const pxSteam, const PXSteamID pxSteamID, int iUser);
	PXSteamPublic PXSteamBool PXSteamSendClanChatMessage(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, const char* pchText);
	PXSteamPublic int PXSteamGetClanChatMessage(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, int iMessage, void* prgchText, int cchTextMax, PXSteamChatEntryType* peChatEntryType, PXSteamID* psteamidChatter);
	PXSteamPublic PXSteamBool PXSteamIsClanChatAdmin(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat, const PXSteamID pxSteamID);

	// interact with the Steam (game overlay / desktop)
	PXSteamPublic PXSteamBool PXSteamIsClanChatWindowOpenInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat);
	PXSteamPublic PXSteamBool PXSteamOpenClanChatWindowInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat);
	PXSteamPublic PXSteamBool PXSteamCloseClanChatWindowInSteam(PXSteam* const pxSteam, const PXSteamID pxSteamIDChat);

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	PXSteamPublic PXSteamBool PXSteamSetListenForFriendsMessages(PXSteam* const pxSteam, bool bInterceptEnabled);
	PXSteamPublic PXSteamBool PXSteamReplyToFriendMessage(PXSteam* const pxSteam, const PXSteamID steamIDFriend, const char* pchMsgToSend);
	PXSteamPublic int PXSteamGetFriendMessage(PXSteam* const pxSteam, const PXSteamID steamIDFriend, int iMessageID, void* pvData, int cubData, PXSteamChatEntryType* peChatEntryType);

	// following apis

	PXSteamPublic __int64 PXSteamGetFollowerCount(PXSteam* const pxSteam, const PXSteamID steamID);
	PXSteamPublic __int64 PXSteamIsFollowing(PXSteam* const pxSteam, const PXSteamID steamID);
	PXSteamPublic __int64 PXSteamEnumerateFollowingList(PXSteam* const pxSteam, unsigned int unStartIndex);

	PXSteamPublic PXSteamBool PXSteamIsClanPublic(PXSteam* const pxSteam, const PXSteamID pxSteamID);
	PXSteamPublic PXSteamBool PXSteamIsClanOfficialGameGroup(PXSteam* const pxSteam, const PXSteamID pxSteamID);

	/// Return the number of chats (friends or chat rooms) with unread messages.
	/// A "priority" message is one that would generate some sort of toast or
	/// notification, and depends on user settings.
	///
	/// You can register for UnreadChatMessagesChanged_t callbacks to know when this
	/// has potentially changed.
	PXSteamPublic int PXSteamGetNumChatsWithUnreadPriorityMessages(PXSteam* const pxSteam);

	// activates game overlay to open the remote play together invite dialog. Invitations will be sent for remote play together
	PXSteamPublic void PXSteamActivateGameOverlayRemotePlayTogetherInviteDialog(PXSteam* const pxSteam, const PXSteamID steamIDLobby);

	// Call this before calling ActivateGameOverlayToWebPage() to have the Steam Overlay Browser block navigations
	// to your specified protocol (scheme) uris and instead dispatch a OverlayBrowserProtocolNavigation_t callback to your game.
	// ActivateGameOverlayToWebPage() must have been called with k_EActivateGameOverlayToWebPageMode_Modal
	PXSteamPublic PXSteamBool PXSteamRegisterProtocolInOverlayBrowser(PXSteam* const pxSteam, const char* pchProtocol);

	// Activates the game overlay to open an invite dialog that will send the provided Rich Presence connect string to selected friends
	PXSteamPublic void PXSteamActivateGameOverlayInviteDialogConnectString(PXSteam* const pxSteam, const char* pchConnectString);

	// Steam Community items equipped by a user on their profile
	// You can register for EquippedProfileItemsChanged_t to know when a friend has changed their equipped profile items
	PXSteamPublic __int64 PXSteamRequestEquippedProfileItems(PXSteam* const pxSteam, const PXSteamID steamID);
	PXSteamPublic PXSteamBool PXSteamBHasEquippedProfileItem(PXSteam* const pxSteam, const PXSteamID steamID, const PXSteamCommunityProfileItemType itemType);
	PXSteamPublic PXSteamBool PXSteamGetProfileItemPropertyString(PXSteam* const pxSteam, const PXSteamID steamID, const PXSteamCommunityProfileItemType itemType, const PXSteamCommunityProfileItemProperty prop, void* const outputBuffer, const unsigned int outputBufferSize);
	PXSteamPublic unsigned int PXSteamGetProfileItemPropertyUint(PXSteam* const pxSteam, const PXSteamID steamID, const PXSteamCommunityProfileItemType itemType, const PXSteamCommunityProfileItemProperty prop);














	//-------------------------------------------------------------------------




	// Custom 
	PXSteamPublic unsigned int PXSteamFriendsFetchList(PXSteam* const pxSteam, const unsigned short searchFlags, PXSteamFriend* const pxSteamFriendList, const unsigned int pxSteamFriendListSize);
	//-------------------------------------------------------------------------



		//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------



#ifdef __cplusplus
}
#endif

#endif