#include "Steam.hpp"

PX::Stream::Stream()
{
	_pxSteam = new PXSteam();
	PXSteamConstruct(_pxSteam);
}

PX::Stream::~Stream()
{
	PXSteamDestruct(_pxSteam);
	delete _pxSteam;
}

System::String^ PX::Stream::ProfileName::get()
{
	if (!_isInitialized)
	{
		return System::String::Empty;
	}

	char buffer[64];
	unsigned int size = 0;

	bool sucess = PXSteamProfileNameFetch(_pxSteam, buffer, 64, &size);

	if (!sucess)
	{
		return System::String::Empty;
	}

	System::String^ cliName = gcnew	System::String(buffer, 0, size);

	return cliName;
}

unsigned int PX::Stream::ProfileLevel::get()
{
	if (!_isInitialized)
	{
		return -1;
	}

	unsigned int steamLevel = PXSteamProfileLevel(_pxSteam);

	return steamLevel;
}

bool PX::Stream::Initialize()
{
	const bool result = PXSteamInitialize(_pxSteam);

	if (!result)
	{
		return false;
	}

	_isInitialized = true;

	return true;
}

void PX::Stream::Shutdown()
{
	PXSteamShutdown(_pxSteam);
}

System::Collections::Generic::List<PX::SteamUser^>^ PX::Stream::FriendsFetch(PX::SteamFriendSearchFilter^ fiendSearchFilter)
{
	const unsigned short flags = fiendSearchFilter->FlagID;
	const unsigned int numberOfTargets = PXSteamFriendsFetch(_pxSteam, flags);

	PXSteamFriend* userList = new PXSteamFriend[numberOfTargets];

	PXSteamFriendsFetchList(_pxSteam, flags, userList, numberOfTargets);

	auto listUser = gcnew System::Collections::Generic::List<SteamUser^>(numberOfTargets);
	
	for (size_t i = 0; i < numberOfTargets; ++i)
	{
		SteamUser^ user = gcnew SteamUser();
		PXSteamFriend* pyUser = &userList[i];

		user->ID = pyUser->ID;
		user->Level = pyUser->Level;
		user->NameProfile = gcnew System::String(pyUser->NameProfile);
		user->NameNick = gcnew System::String(pyUser->NameNick);
		user->Friendship = (SteamFriendshipStatus)pyUser->Friendship;
		user->State = (SteamUserActiveState)pyUser->State;

		listUser->Add(user);
	}

	delete[] userList;

	return listUser;
}
