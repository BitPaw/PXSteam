#include "Steam.hpp"

PX::Steam::Steam()
{
	_pxSteam = new PXSteam();
	PXSteamConstruct(_pxSteam);
}

PX::Steam::~Steam()
{
	PXSteamDestruct(_pxSteam);
	delete _pxSteam;
}

PX::SteamUser^ PX::Steam::ProfileMine::get()
{
	if (_profileMine == nullptr)
	{
		_profileMine = gcnew SteamUser();
	}

	PXSteamUser pxSteamUser;

	const bool isSuccessful = PXSteamUserFetchMe(_pxSteam, &pxSteamUser);

	if (isSuccessful)
	{
		_profileMine->ID = pxSteamUser.ID;
		_profileMine->State = (SteamUserActiveState)pxSteamUser.State;
		_profileMine->Level = pxSteamUser.Level;
		_profileMine->NameProfile = gcnew System::String(pxSteamUser.NameProfile, 0, pxSteamUser.NameProfileLength, System::Text::Encoding::UTF8);
	}
	else
	{
		_profileMine->ID = 0;
		_profileMine->State = SteamUserActiveState::Invalid;
		_profileMine->Level = 0;
		_profileMine->NameProfile = System::String::Empty;
	}

	return _profileMine;
}

bool PX::Steam::Initialize()
{
	const bool result = PXSteamInitialize(_pxSteam);

	if (!result)
	{
		return false;
	}

	_isInitialized = true;

	return true;
}

void PX::Steam::Shutdown()
{
	PXSteamShutdown(_pxSteam);
}

System::Collections::Generic::List<PX::SteamFriend^>^ PX::Steam::FriendsFetch(PX::SteamFriendSearchFilter^ fiendSearchFilter)
{
	const unsigned short flags = fiendSearchFilter->FlagID;
	const unsigned int numberOfTargets = PXSteamFriendsFetch(_pxSteam, flags);

	PXSteamFriend* userList = new PXSteamFriend[numberOfTargets];

	PXSteamFriendsFetchList(_pxSteam, flags, userList, numberOfTargets);

	auto listUser = gcnew System::Collections::Generic::List<SteamFriend^>(numberOfTargets);
	
	for (size_t i = 0; i < numberOfTargets; ++i)
	{
		SteamFriend^ const steamFriend = gcnew SteamFriend();
		PXSteamFriend* const pxSteamFriend = &userList[i];

		steamFriend->ID = pxSteamFriend->User.ID;
		steamFriend->Level = pxSteamFriend->User.Level;
		steamFriend->Friendship = (SteamFriendshipStatus)pxSteamFriend->Friendship;
		steamFriend->State = (SteamUserActiveState)pxSteamFriend->User.State;

		if (pxSteamFriend->User.NameProfileLength > 0)
		{
			steamFriend->NameProfile = gcnew System::String(pxSteamFriend->User.NameProfile, 0, pxSteamFriend->User.NameProfileLength, System::Text::Encoding::UTF8);
		}
		else
		{
			steamFriend->NameProfile = System::String::Empty;
		}
		
		if (pxSteamFriend->NameNickLength > 0)
		{
			steamFriend->NameNick = gcnew System::String(pxSteamFriend->NameNick, 0, pxSteamFriend->NameNickLength, System::Text::Encoding::UTF8);
		}
		else
		{
			steamFriend->NameNick = System::String::Empty;
		}	

		listUser->Add(steamFriend);
	}

	delete[] userList;

	return listUser;
}
