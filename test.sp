#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <cstrike>

#include <PTaH>
#include <dhooks>

#include <smlib2>

public void OnPluginStart()
{
    char str[16];
    Base64.Encode("123", string(str), 1);
    Base64.Decode("123", string(str));
    Base64.Decode("123", string(str));
    Base64.Decode("123", string(str));

    Convert.SettingToBool("yes");

    ConVar cvar;
    Cvar.LockOnCvarHook(cvar, "1", "1");
    Cvar.UnlockOnCvarHook(cvar, "1", "1");
    Cvar.LockOnCvarHook2(cvar, "1", "1");
    Cvar.LockOnCvarHook3(cvar, "1", "1");
    Cvar.OnCheatSet(cvar, 1);
}