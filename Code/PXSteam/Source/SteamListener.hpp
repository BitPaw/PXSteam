#pragma once

#include <Steam/steam_api.h>
#include <Steam/isteamutils.h>
#include <Steam/isteamuser.h>
#include <Steam/isteamfriends.h>

namespace PX
{
	class SteamListener
	{
		public:
		void* PXSteamReference;

		STEAM_CALLBACK(PX::SteamListener, OnAvatarImageLoaded, AvatarImageLoaded_t);

		//void OnAvatarImageLoaded(AvatarImageLoaded_t* const avatarImageLoaded);
		void OnPersonaStateChange(PersonaStateChange_t* const personaStateChange);

#if 0
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(ClanOfficerListResponse_t* clanOfficerListResponse);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(DownloadClanActivityCountsResult_t* downloadClanActivityCountsResult);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendRichPresenceUpdate_t* friendRichPresenceUpdate);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendsEnumerateFollowingList_t* friendsEnumerateFollowingList);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendsGetFollowerCount_t* friendsGetFollowerCount);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendsIsFollowing_t* friendsIsFollowing);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameConnectedChatJoin_t* gameConnectedChatJoin);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameConnectedChatLeave_t* gameConnectedChatLeave);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameConnectedClanChatMsg_t* gameConnectedClanChatMsg);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameConnectedFriendChatMsg_t* gameConnectedFriendChatMsg);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameLobbyJoinRequested_t* gameLobbyJoinRequested);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(GameServerChangeRequested_t* gameServerChangeRequested);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(JoinClanChatRoomCompletionResult_t* joinClanChatRoomCompletionResult);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(PersonaStateChange_t* personaStateChange);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(SetPersonaNameResponse_t* setPersonaNameResponse);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendGameInfo_t* friendGameInfo);
		//void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(FriendSessionStateInfo_t* friendSessionStateInfo_t);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(EquippedProfileItemsChanged_t* equippedProfileItemsChanged_t);
		void xxxxxxxxxxxxxxxxxxxxxxxxxxxx(EquippedProfileItems_t* equippedProfileItems_t);
#endif

		//void OnGameOverlayActivated(GameOverlayActivated_t* gameOverlayActivated);
	};
}