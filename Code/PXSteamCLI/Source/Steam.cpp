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