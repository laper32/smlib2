#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <cstrike>

#include <PTaH>
#include <dhooks>

#include <smlib2>

public void OnPluginStart()
{
    // base64
    char anystr[64];
    encode("", string(anystr), 0)
    decode("", string(anystr))
    mime2url("", string(anystr))
    url2mime("", string(anystr))

    // engine
    GameData gd 
    int offset = 0
    Address addr = Address_Null
    int entity = 0
    InitGameConfOffset(gd, offset, "")
    InitGameConfAddress(gd, addr, "")
    InitGameConfKey(gd, "", string(anystr))
    InitSendPropOffset(offset, "", "")
    InitDataPropOffset(offset, entity, "")
    CreateEngineInterface(gd, "", addr) 

    // fileparser
    fileparser_PrecacheModel("")
    fileparser_PrecacheParticle("")
    fileparser_PrecacheSoundsTable("")

    // hint
    InstructorHud hint = new InstructorHud();
    hint.target = 0;
    hint.flags = 0;
    hint.activator_userid = 0;
    hint.positioning = false;
    hint.invisible = false;
    hint.forcecaption = false;
    hint.icon_onscreen = Icon_bulb;
    hint.icon_offscreen = Icon_bulb;
    hint.show_offscreen = false;
    hint.range = 0.0;
    hint.timeout = 0.0;
    hint.offset = 0.0;
    hint.pulseoption = 0;
    hint.alphaoption = 0;
    hint.shakeoption = 0;
    hint.color(0, 0, 0);
    hint.EasyInit();
    hint.Display(0, "");
    hint.DisplayAll("");
    hint.tDisplayAll("");
    hint.Destroy();
    CreateInstructorHint(0, 0.0, Icon_bulb, 255, 255, 255, "");
    CreateInstructorHintAll(0.0, Icon_bulb, 255, 255, 255, "");

    // math
    abs(0)
    fabs(0.0)
    min(0, 0.0)
    max(0, 0.0)
    clamp(0, 0.0, 0.0)
    overflow(0, 0x0, 0.0)
    sqrt(0.0)
    GerPercentageInt(1, 1)
    GetPercentageFloat(1.0, 1.0)
    mean({1, 2, 3})

    // md5
    md5sum("", string(anystr))

    // mem
    CreateMemoryForSDKCall(gd)
    GetModuleSize(addr)
    memcpy(addr, string(anystr))
    writeDWORD("", addr, 0)

    // paramparser
    ParamParseString(ArrayList &arrayBuffer, char[] sParamString, int iMaxLen, char cSeparator)
    StrExtract(char[] sBuffer, char[] sSource, int startPos, int endPos)
    StrContain(char[] sBuffer, char[] sSource, char cSeparator)
    CountCharInString(char[] sBuffer, char cSymbol)
    StringToLower(char[] sBuffer)
    ArrayShuffle(ArrayList hArrayList)
    Sort_ByLength(int iIndex1, int iIndex2, ArrayList hArrayList, Handle hCustom)

    // playermgr
    IsPlayerExist(0, true)
    IsPlayerInGroup(0, "")
    GetPlayingCount()
    GetAliveCount()

    // sound
    int val = new int[16];
    EmitSoundEx(val, 0, "any.wav");
    EmitSoundOne(0, "any.wav");
    EmitSoundAll("any.wav");

    // text
    InitUserMessage()
    SetChatPrefix("")
    SetChatSpaces("")
    SetChatConSnd(true)
    text_SkipNextChatCS()
    text_SkipNextPrefix()

    Chat(0, "")
    ChatEx(val, 1, "")
    ChatTeam(0, true, "")
    ChatAlive(true, true, "")
    ChatAll("")
    tChat(0, "")
    tChatAlive(true, true, "")
    tChatTeam(0, true, "")
    tChatAll("")
    ProcessColorString("", 0)
    RemoveAllColors("", 0)

    Hint(0, "")
    HintAll("")
    HintEx(val, 0, "")

    SetTextDest(0)

    Text(0, "")
    TextAll("")
    TextEx(val, 0, "")

    SetHudTextParamsUM({0.0, 0.0}, 0.0, {0, 0, 0, 0}, 0, 0.0, 0.0, 0.0)
    SendHudTextMessage(0, 0, "")
    SendHudTextMessage2(0, 0,"")
    SendHudTextMessageEx(0, 0, 0.0, const {0, 0}, {0, 0, 0, 0}, 0, 0.0, 0.0, 0.0, "")
    SendHudTextMessageClients(0, val, 0,"")
    SendHudTextMessageAll(0, "")
    SendHudTextMessageTeam(0, 0, "")

    RandomString(string(anystr));

    // tools

    // utils
}