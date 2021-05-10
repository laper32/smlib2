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
    encode(NULL_STRING, string(anystr), 0)
    decode(NULL_STRING, string(anystr))
    mime2url(NULL_STRING, string(anystr))
    url2mime(NULL_STRING, string(anystr))

    // cvar
    ConVar whatever;
    CvarLockOnCvarHook(whatever, "old", "new")
    CvarUnlockOnCvarHook(whatever, "old", "new")
    CvarLockOnCvarHook2(whatever, "old", "new")
    CvarLockOnCvarHook3(whatever, "old", "new")
    CvarOnCheatSet(whatever, 0)

    // convert
    ConvertSettingToBool("yes");
    ConvertSettingToBool("no");

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
    hint.Init();
    hint.Display(0, NULL_STRING);
    hint.DisplayAll(NULL_STRING);
    hint.tDisplayAll(NULL_STRING);
    hint.Destroy();
    CreateInstructorHint(0, 0.0, Icon_bulb, 0.0, 255, 255, 255, "");
    CreateInstructorHintAll(0.0, Icon_bulb, 0.0, 255, 255, 255, "");

    // math
    abs(0)
    fabs(0.0)
    min(0, 0.0)
    max(0, 0.0)
    clamp(0, 0.0, 0.0)
    overflow(0, 0.0, 0.0)
    sqrt(0.0)
    GerPercentageInt(1, 1)
    GetPercentageFloat(1.0, 1.0)
    mean({1, 2, 3})

    // matrix
    float mat[16];
    Matrix3x4Identity(mat);

    // md5
    md5sum(NULL_STRING, string(anystr))

    // mem
    CreateMemoryForSDKCall(gd)
    GetModuleSize(addr)
    memcpy(addr, string(anystr))
    writeDWORD("", addr, 0)

    // paramparser
    ArrayList arr;
    Handle hndl;
    ParamParseString(arr, "", 0, ' ')
    StrExtract("", "", 0, 0)
    StrContain("", "", ' ')
    CountCharInString("", ' ')
    StringToLower("")
    ArrayShuffle(arr)
    Sort_ByLength(0, 0, arr, hndl)

    // playermgr
    IsPlayerExist(0, true)
    IsPlayerInGroup(0, "")
    GetPlayers(true, true, CS_TEAM_CT)
    GetPlayers(true, false, CS_TEAM_CT)
    GetPlayers(false, true, CS_TEAM_CT)
    GetPlayers(false, false, CS_TEAM_CT)
    GetTotalPlayers()
    GetTeamPlayers(CS_TEAM_CT)
    GetTotalAlives()
    GetTeamAlives(CS_TEAM_CT)

    // sound
    int[] val = new int[16];
    EmitSoundEx(val, 0, "any.wav");
    EmitSoundOne(0, "any.wav");
    EmitSoundAll("any.wav");

    // text
    InitUserMessage()
    SetChatPrefix(NULL_STRING)
    SetChatSpaces(NULL_STRING)
    SetChatConSnd(true)
    text_SkipNextChatCS()
    text_SkipNextPrefix()

    Chat(0, NULL_STRING)
    ChatEx(val, 1, NULL_STRING)
    ChatTeam(0, true, NULL_STRING)
    ChatAlive(true, true, NULL_STRING)
    ChatAll(NULL_STRING)
    tChat(0, NULL_STRING)
    tChatAlive(true, true, NULL_STRING)
    tChatTeam(0, true, NULL_STRING)
    tChatAll(NULL_STRING)
    ProcessColorString("", 0)
    RemoveAllColors("", 0)

    Hint(0, NULL_STRING)
    HintAll(NULL_STRING)
    HintEx(val, 0, NULL_STRING)

    SetTextDest(0)

    Text(0, NULL_STRING)
    TextAll(NULL_STRING)
    TextEx(val, 0, NULL_STRING)

    float _2dpos[2] = {0.0, 0.0}
    SetHudTextParamsUM(_2dpos, 0.0, {255, 255, 255, 255}, 0, 0.0, 0.0, 0.0)
    SendHudTextMessage(0, 0, NULL_STRING)
    SendHudTextMessage2(0, 0, NULL_STRING)
    SendHudTextMessageEx(0, 0, 0.0, _2dpos, {0, 0, 0, 0}, 0, 0.0, 0.0, 0.0, NULL_STRING)
    SendHudTextMessageClients(0, val, 0, NULL_STRING)
    SendHudTextMessageAll(0, NULL_STRING)
    SendHudTextMessageTeam(0, 0, NULL_STRING)

    RandomString(string(anystr));

    // tools
    float vel[3], ang[3], pos[3]
    int client = entity
    int iter = 1
    ToolsSetVelocity(entity, vel, true, true)
    ToolsGetVelocity(entity, vel)
    ToolsGetSpeed(entity)
    ToolsGetAbsOrigin(entity, pos)
    ToolsGetAbsAngles(entity, ang)
    ToolsGetMaxSizeVector(entity, pos)
    ToolsGetCenterPosition(entity, pos)
    ToolsGetEyePosition(entity, pos)
    ToolsGetMyWeapons(entity)
    ToolsGetWeapon(entity, 0)
    ToolsGetHealth(entity, true)
    ToolsSetHealth(entity, 0, true)
    ToolsGetLMV(entity)
    ToolsSetLMV(entity, 0.0)
    ToolsGetArmor(entity)
    ToolsSetArmor(entity, 0)
    ToolsGetTeam(entity)
    ToolsSetTeam(entity, 0)
    ToolsGetNightVision(entity, true)
    ToolsSetNightVision(entity, true, true)
    ToolsGetDefuser(entity)
    ToolsSetDefuser(entity, true)
    ToolsGetHelmet(entity)
    ToolsSetHelmet(entity, true)
    ToolsGetHeavySuit(entity)
    ToolsSetHeavySuit(entity, true)
    ToolsGetActiveWeapon(entity)
    // ToolsSetActiveWeapon(entity, 0)
    ToolsGetAddonBits(entity)
    ToolsSetAddonBits(entity, 1<<0)
    ToolsGetObserverMode(entity)
    ToolsGetObserverTarget(entity)
    ToolsGetHitGroup(entity)
    ToolsGetScore(entity, true)
    ToolsSetScore(entity, true, 0)
    ToolsSetGravity(entity, 0.0)
    ToolsGetMoney(entity)
    ToolsSetMoney(entity, 0)
    // ToolsSetSpot(entity, true)
    ToolsSetDetecting(entity, true)
    ToolsSetHud(entity, true, 0)
    ToolsSetArm(entity, "models/senpai_arms.mdl")
    ToolsSetAttack(entity, 0.0)
    ToolsSetFlashLight(entity, true)
    ToolsSetFov(entity, 90)
    ToolsSetTextures(entity, 1, 1)
    ToolsGetEffect(entity)
    ToolsSetEffect(entity, 0)
    ToolsGetActivator(entity)
    ToolsSetModelIndex(entity, 1)
    ToolsGetOwner(entity)
    ToolsSetOwner(entity, client)
    ToolsGetParent(entity)
    ToolsSetParent(entity, client)
    ToolsGetRagdollIndex(client)
    ToolsGetCollisionGroup(client)
    ToolsSetCollisionGroup(client, 0)
    ToolsIsModelBoxColliding(client, client)
    ToolsFindPlayerInSphere(iter, pos, 0.0)

    float flBoundaries[BoxBound][3]
    ToolsIsBoxIntersectingSphere(flBoundaries, pos, 0.0)
    ToolsGetBoxMaxBoundary(0, flBoundaries, false)
    ToolsBuildModelBox(client, flBoundaries, 0.0)
    ToolsJumpToPoint(pos, ang, 0.0, NULL_VECTOR)
    ToolsIsSectorDiskIntersect(NULL_VECTOR, NULL_VECTOR, 0.0, 0.0, NULL_VECTOR, 0.0);
    ToolsCalculateLinePointShortestSquaredDistance(NULL_VECTOR, NULL_VECTOR, NULL_VECTOR);

    // utils
    UTIL_CreateTrain("", NULL_VECTOR, NULL_VECTOR, "", "", "", 0)
    UTIL_CreatePath("", NULL_VECTOR, NULL_VECTOR, "", 0)
    UTIL_CreateMonster("", NULL_VECTOR, NULL_VECTOR, "", 0)
    UTIL_CreatePhysics("", NULL_VECTOR, NULL_VECTOR, "", 0)
    UTIL_CreateDynamic("", NULL_VECTOR, NULL_VECTOR, "", "", true, false, false, DYN_COLLISIONDISABLED)
    UTIL_CreateProjectile(NULL_VECTOR, NULL_VECTOR, "")
    UTIL_CreateSmoke(-1, NULL_VECTOR, NULL_VECTOR, "", "100", "70", "80", "200", "2", "30", "400", "20", "255 255 255", "0", "", 0.0, 0.0)
    UTIL_CreateParticle(-1, NULL_VECTOR, NULL_VECTOR, "", "", 0.0)
    UTIL_CreateExplosion(NULL_VECTOR/*, NULL_VECTOR*/, 0, "materials/sprites/xfireball3.vmt", 0.0, 0.0, "", -1, -1, "")
    UTIL_CreateDamage(-1, NULL_VECTOR, 0, 0.0, 0.0, DMG_GENERIC, -1, "")
    UTIL_CreateSprite(-1, NULL_VECTOR, NULL_VECTOR, "", "", "", "", 0.0)
    UTIL_CreateSpriteController(-1, "", "")
    UTIL_CreateTesla(-1, NULL_VECTOR, NULL_VECTOR, "", "500.0", "DoSpark", "42", "62", "materials/sprites/physbeam.vmt", "255 255 255", "10.0", "11.0", "0.3", "0.3", "0.1", "0.2", 0.0)
    UTIL_CreateShooter(-1, "", "5", "-1", 0, "", NULL_VECTOR, NULL_VECTOR, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    UTIL_CreateBeam(NULL_VECTOR, NULL_VECTOR, "0", "0", "4.0", "0", "3", "0", "Bigshot", "35", "1.0", "materials/sprites/purplelaser1.vmt", "0", "1", 0, "0", "256", "100", "", 0.0, 0.0, "")
    UTIL_CreateLight(-1, NULL_VECTOR, "", "0", "80", "1", "90", "1", 0, "", 0.0, 0.0, 0.0)
    UTIL_SpawnSpeaker(NULL_VECTOR, NULL_VECTOR, 0, 0.1)
    UTIL_CreateGlowing(0, true, 0, 0, 0, 0, 0)
    UTIL_SetRenderColor(0, Clr_R, 0)
    UTIL_GetRenderColor(0, Clr_R)
    UTIL_CreateTracer(-1, "", "", NULL_VECTOR, 0.0)
    UTIL_CreateShakeScreen(0, 0.0, 0.0, 0.0)
    UTIL_CreateFadeScreen(0, 0.0, 0.0, 0, {0, 0, 0, 0})
    UTIL_CreatePhysForce(0, NULL_VECTOR, NULL_VECTOR, 0.0, 0.0, 0.0)
    UTIL_CreateClientHint(0, "")
    UTIL_CreateClientHud(hndl, 0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, "")
    UTIL_PrecacheModel("")
    UTIL_IgniteEntity(0, 0.0)
    UTIL_ExtinguishEntity(0)
    UTIL_RemoveEntity(0, 0.0)
    UTIL_PrecacheDecal("")
    UTIL_PrecacheSound("")
    UTIL_FindHullIntersection(hndl, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, PlayersFilter, 0)
    UTIL_GetVelocityByAim(NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 1.0, false)
    UTIL_IsOnSamePlane(0, 0, NULL_VECTOR, PlayersFilter)
    UTIL_GetTraceEndPoint(0, NULL_VECTOR)
    UTIL_TraceRay(0, 0, NULL_VECTOR, NULL_VECTOR, PlayersFilter)
    UTIL_GetDistanceBetween(0, 0)
    GetEffectIndex("")
    GetParticleEffectIndex("")
    PrecacheParticleFile(0, "")
    PrecacheParticleEffect("")
    GetEffectName(0, "", 0)
    GetParticleEffectName(0, "", 0)
    GetEffectNameCount()
    GetParticleEffectCount()
    UTIL_IsMapZE()
    UTIL_CreateDeathIcon(0, 0, "", false, false, false, false, 0)
    PlayersFilter(0, 0)
}