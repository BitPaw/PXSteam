namespace PX
{
    public enum SteamFriendshipStatus
    {
		Invalid,
		None,
		Blocked,            // this doesn't get stored; the user has just done an Ignore on an friendship invite
		RequestRecipient,
		Friend,
		PRequestInitiator,
		Ignored,            // this is stored; the user has explicit blocked this other user from comments/chat/etc
		IgnoredFriend,
		Suggested_DEPRECATED,       // was used by the original implementation of the facebook linking feature, but now unused.
	}
}