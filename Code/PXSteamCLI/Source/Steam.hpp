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
		Invalid
	};

	public ref class SteamUser
	{
		public:
		PXSteamUserID ID;
		unsigned int Level;
		System::String^ NameProfile;
		System::String^ NameNick;
		SteamFriendshipStatus Friendship;
		SteamUserActiveState State;

		SteamUser() {};
	};

	public ref class Stream
	{
		private:
		bool _isInitialized;
		PXSteam* _pxSteam;

		public:
		Stream();
		~Stream();

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

		property System::String^ ProfileName { System::String^ get(); }
		property unsigned int ProfileLevel { unsigned int get(); }

		bool Initialize();
		void Shutdown();

		System::Collections::Generic::List<SteamUser^>^ FriendsFetch(SteamFriendSearchFilter^ fiendSearchFilter);
	};
}