# PXSteam
<p>
The Steam API downgraded to be used in C, then updated to C++ and C#. All in one place.
</p>

<p>
The steam API is using C++, blocking direct interaction with C.<br>
The code is written in half C and half C++ Style.<br>
Interfaces and classes are used but enum classes are absent and have invalid states.<br>
Additionally all functions rely on a global state object residing in a local DLL.
All this makes it not logical to use C++.<br>If we still want C++, we need a wrapper anyway, as this code violates even C code rules (not even speaking from C++). If we want to wrap it to CLI (C# and VB.NET) we need additional work.
</p>

Link: https://partner.steamgames.com/doc/sdk
