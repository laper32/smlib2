#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <cstrike>

// #include <PTaH>
// #include <dhooks>

#include <smlib2>

public void OnPluginStart()
{
    ConVar cvar;
    Cvar.LockOnCvarHook(cvar, "1", "1");
    Cvar.UnlockOnCvarHook(cvar, "1", "1");
    Cvar.LockOnCvarHook2(cvar, "1", "1");
    Cvar.LockOnCvarHook3(cvar, "1", "1");
    Cvar.OnCheatSet(cvar, 1);

    Convert.SettingToBool("foo");

    GameData gd; int offset=0; Pointer ptr = nullptr;
    Engine.InitGameConfOffset(gd, offset, "");
    Engine.InitGameConfAddress(gd, ptr, "")
    Engine.InitGameConfKey(gd, "", "", 0)
    Engine.InitSendPropOffset(offset, "", "")
    Engine.InitDataPropOffset(offset, 0, "")
    Engine.CreateEngineInterface(gd, "", "", ptr)

    // ZP here
    char ASMTRAMPOLINE[64]="\x58\x59\x5a\x50\xb8\x00\x00\x00\x00\xff\xe0";
    Memory.CreateMemoryForSDKCall(gd)
    Memory.GetModuleSize(nullptr);
    Memory.memcpy(nullptr, ASMTRAMPOLINE, sizeof(ASMTRAMPOLINE));
    Memory.writeDWORD(ASMTRAMPOLINE, nullptr, 0);

    Math.abs(1);
    Math.fabs(1.0);
    Math.min(1, 1);
    Math.max(1, 1);
    Math.clamp(2, 1, 1);
    Math.overflow(2, 1, 1);
    Math.sqrt(10);
    Math.GetPercentageInt(1, 10);
    Math.GetPercentageFloat(1.0, 10.0);

    int sth[2] = {1, 1};
    Math.mean(sth);

    // char str[16];
    // Base64.Encode("123", string(str), 1);
    // Base64.Decode("123", string(str));
    // Base64.Decode("123", string(str));
    // Base64.Decode("123", string(str));
    // MD5.Digest("", "", 0)
    // Convert.SettingToBool("yes");

    // ConVar cvar;
    // Cvar.LockOnCvarHook(cvar, "1", "1");
    // Cvar.UnlockOnCvarHook(cvar, "1", "1");
    // Cvar.LockOnCvarHook2(cvar, "1", "1");
    // Cvar.LockOnCvarHook3(cvar, "1", "1");
    // Cvar.OnCheatSet(cvar, 1);

    // GameData gd; int offset=0; Pointer ptr = nullptr;
    // Engine.InitGameConfOffset(gd, offset, "");
    // Engine.InitGameConfAddress(gd, ptr, "")
    // Engine.InitGameConfKey(gd, "", "", 0)
    // Engine.InitSendPropOffset(offset, "", "")
    // Engine.InitDataPropOffset(offset, 0, "")
    // Engine.CreateEngineInterface(gd, "", "", ptr)

    // float mat[16];
    // Matrix3x4.Identity(mat);
    
    // Shake.Create(0, 0.0, 0.0, 0.0);

    // EntityEx.SetFlashLight(0, false)

    // PlayerEx.CreateDeathIcon(0, 0, "")

    // ArrayList _arr;
    // ParamParseString(_arr, "", 0, ' ')
}