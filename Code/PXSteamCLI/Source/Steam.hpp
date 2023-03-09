#pragma once

#include "../../PXSteam/Source/PXSteam.h"

#include "SteamFriendSearchFilter.hpp"

namespace PX
{
	public enum class SteamUserActiveState
	{
		Invalid,
		Offline,			// friend is not currently logged on
		Online,			// friend is logged on
		Busy,			// user is on, but busy
		Away,			// auto-away feature
		Snooze,			// auto-away for a long time
		LookingToTrade,	// Online, trading
		LookingToPlay,	// Online, wanting to play
		Invisible		// Online, but appears offline to friends.  This status is never published to clients.
	};

	public enum class SteamFriendshipStatus
	{
		Invalid,
		None,
		Blocked,			// this doesn't get stored; the user has just done an Ignore on an friendship invite
		RequestRecipient,
		Friend,
		PRequestInitiator,
		Ignored,			// this is stored; the user has explicit blocked this other user from comments/chat/etc
		IgnoredFriend,
		Suggested_DEPRECATED,		// was used by the original implementation of the facebook linking feature, but now unused.
	};




	public ref class SteamUser
	{
		public:
		PXSteamUserID ID;
		SteamUserActiveState State;
		unsigned int Level;
		System::String^ NameProfile;
	};

	public ref class SteamFriend : public SteamUser
	{
		public:
		System::String^ NameNick;
		SteamFriendshipStatus Friendship;

		bool IsInGame;
		//SteamFriendGameInfo GameInfo;
	};

	public ref class Steam
	{
		private:
		bool _isInitialized;
		PXSteam* _pxSteam;
		SteamUser^ _profileMine;

		public:
		Steam();
		~Steam();

		// propertys
		property bool IsInitialized
		{
			bool get()
			{
				return _isInitialized;
			}
			private:
			void set(bool value)
			{
				_isInitialized = value;
			}
			public:
		}

		property SteamUser^ ProfileMine { SteamUser^ get(); }

		bool Initialize();
		void Shutdown();

		System::Collections::Generic::List<SteamFriend^>^ FriendsFetch(SteamFriendSearchFilter^ fiendSearchFilter);
	};
}