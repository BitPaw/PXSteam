#ifndef PXSteamINCLUDE
#define PXSteamINCLUDE


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

	typedef __int64 PXSteamUserID;

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
		PXSteamFriendshipStatusInvalid
	}
	PXSteamFriendshipStatus;

	typedef struct PXSteam_
	{
		PXSteamState State;
		unsigned int AppID;
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

	typedef struct PXSteamFriend_
	{
		PXSteamUserID ID;
		unsigned int Level;
		char NameProfile[64];
		char NameNick[64];
		PXSteamFriendshipStatus Friendship;
		PXSteamUserActiveState State;

		unsigned char IsInGame;
		PXSteamFriendGameInfo GameInfo;
	}
	PXSteamFriend;




	//---<Core>--------------------
	void PXSteamConstruct(PXSteam* const pxSteam);
	void PXSteamDestruct(PXSteam* const pxSteam);

	bool PXSteamInitialize(PXSteam* const pxSteam);
	void PXSteamShutdown(PXSteam* const pxSteam);


	PXSteamUserActiveState PXSteamProfileStateFromID(const unsigned char stateID);
	PXSteamFriendshipStatus PXSteamFriendshipStatusFromID(const unsigned char stateID);

	// Profile - you


	// Get your profilename, formatted in UTF-8. Guranteed not to be null.
	unsigned char PXSteamProfileNameFetch(PXSteam* const pxSteam, void* const exportBuffer, const unsigned int exportBufferSize); // Written size?

	unsigned char PXSteamProfileNameSet(PXSteam* const pxSteam, const void* const inputBuffer, const unsigned int inputBufferSize);

	PXSteamUserActiveState PXSteamProfileState(PXSteam* const pxSteam);


	//---<Friends>---------------------



	unsigned int PXSteamFriendsFetch(PXSteam* const pxSteam, const unsigned short searchFlags);



	PXSteamFriendshipStatus PXSteamFriendsRelationship(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);	
	PXSteamUserActiveState PXSteamFriendsPersonaState(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);

	unsigned char PXSteamFriendsName(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, const void* outputBuffer, const unsigned int outputBufferSize);

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	unsigned char PXSteamFriendsGamePlayed(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, PXSteamFriendGameInfo* const pxSteamFriendGameInfoList);

	// accesses old friends names - returns an empty string when their are no more items in the history
	//const char* PXSteamFriendsPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName);
	
	// friends steam level
	int PXSteamFriendsSteamLevel(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID);

	// Returns nickname the current user has set for the specified player. Returns NULL if the no nickname has been set for that player.
	// DEPRECATED: GetPersonaName follows the Steam nickname preferences, so apps shouldn't need to care about nicknames explicitly.
	unsigned char  PXSteamFriendsNickname(PXSteam* const pxSteam, const PXSteamUserID pxSteamUserID, const void* outputBuffer, const unsigned int outputBufferSize);








	unsigned int PXSteamFriendsFetchList(PXSteam* const pxSteam, const unsigned short searchFlags, PXSteamFriend* const pxSteamFriendList, const unsigned int pxSteamFriendListSize);



#ifdef __cplusplus
}
#endif

#endif // !PXSteam