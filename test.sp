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

    float matrix[16]; float wtf[3];
    Matrix3x4.Identity(matrix);
    Matrix3x4.Concatenate(matrix, matrix, matrix);
    Matrix3x4.TransformPoint(matrix, wtf, wtf);
    Matrix3x4.Rotate(matrix, 0.0, 0, 0, 0);
    Matrix3x4.Scale(matrix, 0.0, 0.0, 0.0);
    Matrix3x4.Translate(matrix, wtf);
    Matrix3x4.GetTranslate(matrix, wtf);
    Matrix3x4.RotateByMatrix(wtf, matrix, wtf);
    Matrix3x4.RotationOnly(matrix, matrix);
    Matrix3x4.RotateMatrix(matrix, 0.0, 0.0, 0.0, 0.0);
    Matrix3x4.InvertSimple(matrix, matrix);
    Matrix3x4.InvertRotation(matrix, matrix);
    
    Numeric.HexToDec("");
    Numeric.IsHexSymbol(0);

    // // ZP here
    //char ASMTRAMPOLINE[64]="\x58\x59\x5a\x50\xb8\x00\x00\x00\x00\xff\xe0";
    Memory.CreateMemoryForSDKCall(gd)
    Memory.GetModuleSize(nullptr);
    // Memory.memcpy(nullptr, ASMTRAMPOLINE, sizeof(ASMTRAMPOLINE)); // char[] and any[], wtf?
    // Memory.writeDWORD(ASMTRAMPOLINE, nullptr, 0); // char[] and any[] , wtf?

    char _str[16];
    StringEx.ToLower(_str);
    StringEx.CountOccurence(_str, ' ');
    StringEx.RandomOut(string(_str));
    StringEx.StrContainsEx(_str, _str);
    
    FileParser.PrecacheModel("");
    FileParser.PrecacheWeapon("");
    FileParser.PrecacheParticle("");
    FileParser.PrecacheTexture("", "");
    FileParser.PrecacheSound("");

    Server.GetIPAddress(string(_str), offset);
    
    Entity ent = new Entity(0);
    PrintToServer("%d", ent.Index);
    PrintToServer("%d", ent.Valid);
    PrintToServer("%d", ent.Networkable);
    ent.Remove();
    ent.SetParent(0);
    ent.AcceptInput("");
    ent.GetDataInt(0);
    ent.SetDataInt(0, 0);
    ent.GetDataFloat(0);
    ent.SetDataFloat(0, 0.0);
    ent.GetDataEnt(0);
    ent.SetDataEnt(0, 0);
    ent.GetDataVector(0, wtf);
    ent.SetDataVector(0, wtf);
    ent.GetDataString(0, string(_str));
    ent.SetDataString(0, string(_str));

    int _intarr[4];
    ent.GetDataIntArray(0, _intarr, 4);
    ent.SetDataIntArray(0, _intarr, 4);
    ent.GetDataMapInfo("");
    ent.GetSendPropOffset("");
    ent.HasProp(Prop_Data, "");
    ent.GetPropInt(Prop_Data, "");
    ent.SetPropInt(Prop_Data, "", 0);
    ent.GetPropFloat(Prop_Data, "");
    ent.SetPropFloat(Prop_Data, "", 0.0);
    ent.GetPropEnt(Prop_Data, "");
    ent.SetPropEnt(Prop_Data, "", 0);
    ent.GetPropVector(Prop_Data, "", wtf);
    ent.SetPropVector(Prop_Data, "", wtf);
    ent.GetPropString(Prop_Data, "", string(_str));
    ent.SetPropString(Prop_Data, "", _str);
    ent.GetPropArraySize(Prop_Data, "");
    PrintToServer("%x", ent.Addr);
    ent.GetClassname(string(_str));
    ent.Teleport(wtf, wtf, wtf);
    ent.GetVelocity(wtf);
    PrintToServer("%.2f", ent.Speed);
    ent.GetAbsOrigin(wtf);
    ent.GetAbsAngles(wtf);
    ent.GetMaxs(wtf);
    ent.GetMins(wtf);
    ent.m_iHealth = 0;
    PrintToServer("%d", ent.m_iHealth);
    ent.m_iMaxHealth = 0;
    PrintToServer("%d", ent.m_iMaxHealth);
    ent.m_hOwnerEntity = 0;
    PrintToServer("%d", ent.m_hOwnerEntity);
    ent.m_pParent = 0;
    PrintToServer("%d", ent.m_pParent);
    PrintToServer("%d", ent.m_hRagdoll);
    PrintToServer("%d", ent.m_pActivator);

    Base64.Encode("123", string(_str), 1);
    Base64.Decode("123", string(_str));
    MD5.Digest("", "", 0);

    // char str[16];
    // Base64.Encode("123", string(str), 1);
    // Base64.Decode("123", string(str));
    // Base64.Decode("123", string(str));
    // Base64.Decode("123", string(str));
    // MD5.Digest("", "", 0)
    // Convert.SettingToBool("yes");

    
    // Shake.Create(0, 0.0, 0.0, 0.0);

    // EntityEx.SetFlashLight(0, false)

    // PlayerEx.CreateDeathIcon(0, 0, "")
}