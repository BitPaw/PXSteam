namespace PX
{
    public enum SteamUserActiveState
    {
		Invalid,
		Offline,            // friend is not currently logged on
		Online,         // friend is logged on
		Busy,           // user is on, but busy
		Away,           // auto-away feature
		Snooze,         // auto-away for a long time
		LookingToTrade, // Online, trading
		LookingToPlay,  // Online, wanting to play
		Invisible       // Online, but appears offline to friends.  This status is never published to clients.
	}
}