#include <cstrike>
#include <smlib2>

public void OnPluginStart()
{
    char str[16];
    Base64.Encode("123", string(str), 1);
    Base64.Decode("123", string(str));

    Convert.SettingToBool(str);

    GameData gd; int offset=0; Pointer ptr = nullptr;
    Engine.InitGameConfOffset(gd, offset, "");
    Engine.InitGameConfAddress(gd, ptr, "");
    Engine.InitGameConfKey(gd, "", "", 0);
    Engine.InitSendPropOffset(offset, "", "");
    Engine.InitDataPropOffset(offset, 0, "");
    Engine.CreateEngineInterface(gd, "", "", ptr);

    Entity e = new Entity(0); float vec[3]; int arr[4]; float scr[2];
    e.Index;
    e.Valid;
    e.Networkable;
    e.Remove();
    e.SetParent(0);
    e.AcceptInput("", -1, -1, 0);
    e.GetDataEnt(0);
    e.SetDataEnt(0, 0, false);
    e.GetDataFloat(0);
    e.SetDataFloat(0, 0.0, false);
    e.GetDataEnt(0);
    e.SetDataEnt(0, 0, false);
    e.GetDataVector(0, vec);
    e.SetDataVector(0, vec, false);
    e.GetDataString(0, str, 16);
    e.SetDataString(0, str, 16, false);
    e.GetDataIntArray(0, arr, 4, 4);
    e.SetDataIntArray(0, arr, 4, 4, false);
    e.GetDataMapInfo("input");
    e.GetSendPropOffset("", false);
    e.HasProp(Prop_Data, "");
    e.GetPropInt(Prop_Data, "");
    e.SetPropInt(Prop_Data, "", 0);
    e.GetPropFloat(Prop_Data, "");
    e.SetPropFloat(Prop_Data, "", 0.0);
    e.GetPropEnt(Prop_Data, "");
    e.SetPropEnt(Prop_Data, "", 0);
    e.GetPropVector(Prop_Data, "", vec);
    e.SetPropVector(Prop_Data, "", vec);
    e.GetPropString(Prop_Data, "", str, 4);
    e.SetPropString(Prop_Data, "", str);
    e.GetPropArraySize(Prop_Data, "");
    e.Addr;
    e.GetClassname(str, 4);
    e.Teleport(vec, vec, vec);
    e.GetVelocity(vec);
    e.SetVelocity(vec);
    e.Speed;
    e.GetAbsOrigin(vec);
    e.GetAbsAngles(vec);
    e.GetMaxs(vec);
    e.GetMins(vec);
    e.m_iHealth;
    e.m_iHealth = 0;
    e.m_iMaxHealth;
    e.m_iMaxHealth = 0;
    e.m_hOwnerEntity;
    e.m_hOwnerEntity = 0;
    e.m_pParent;
    e.m_pParent = 0;
    e.m_hRagdoll;
    e.m_pActivator;
    e.m_hMyWeapons;
    e.GetWeapon(0);
    e.m_flLaggedMovementValue;
    e.m_flLaggedMovementValue = 0.0;
    e.m_ArmorValue;
    e.m_ArmorValue = 0;
    e.m_iTeamNum;
    e.m_bHasNightVision;
    e.m_bHasNightVision = true;
    e.m_bNightVisionOn;
    e.m_bNightVisionOn = true;
    e.m_bHasDefuser;
    e.m_bHasDefuser = true;
    e.m_bHasHelmet;
    e.m_bHasHelmet = true;
    e.m_bHasHeavyArmor;
    e.m_bHasHeavyArmor = true;
    e.m_hActiveWeapon;
    e.m_iAddonBits;
    e.m_iAddonBits = 0;
    e.m_iObserverMode;
    e.m_hObserverTarget;
    e.m_LastHitGroup;
    e.m_iFrags;
    e.m_iFrags = 0;
    e.m_iDeaths;
    e.m_iDeaths = 0;
    e.m_flGravity;
    e.m_flGravity = 0.0;
    e.m_iAccount;
    e.SetArmsModel("");
    e.m_flNextAttack;
    e.m_flNextAttack = 0.0;
    e.m_iFOV;
    e.m_iFOV = 90;
    e.m_iDefaultFOV;
    e.m_iDefaultFOV = 90;
    e.m_nBody;
    e.m_nBody = 0;
    e.m_nSkin;
    e.m_nSkin = 0;
    e.m_fEffects;
    e.m_fEffects = 0;
    e.m_nModelIndex;
    e.m_nModelIndex = 0;
    e.m_CollisionGroup;
    e.m_CollisionGroup = 0;

    EntityEx.Ignite(0, 0.0);
    EntityEx.Extinguish(0);
    EntityEx.GetHealth(0, true);
    EntityEx.GetHealth(0, false);
    EntityEx.SetHealth(0, 0, true);
    EntityEx.SetHealth(0, 0, false);
    EntityEx.SetVelocity(0, vec, true, true);
    EntityEx.SetVelocity(0, vec, true, false);
    EntityEx.SetVelocity(0, vec, false, true);
    EntityEx.SetVelocity(0, vec, false, false);
    EntityEx.GetVelocity(0, vec);
    EntityEx.GetSpeed(0);
    EntityEx.GetAbsOrigin(0, vec);
    EntityEx.GetAbsAngles(0, vec);
    EntityEx.GetMaxs(0, vec);
    EntityEx.GetMins(0, vec);
    EntityEx.GetMyWeapons(0);
    EntityEx.GetWeapon(0, 0);
    EntityEx.GetLMV(0);
    EntityEx.SetLMV(0, 0.0);
    EntityEx.GetArmor(0);
    EntityEx.SetArmor(0, 0);
    EntityEx.GetTeam(0);
    EntityEx.SetTeam(0, 0);
    EntityEx.GetNightVision(0, true);
    EntityEx.GetNightVision(0, false);
    EntityEx.SetNightVision(0, true, true);
    EntityEx.SetNightVision(0, true, false);
    EntityEx.GetDefuser(0);
    EntityEx.SetDefuser(0, false);
    EntityEx.GetHelmet(0);
    EntityEx.SetHelmet(0, true);
    EntityEx.GetHeavySuit(0);
    EntityEx.SetHeavySuit(0, false);
    EntityEx.GetActiveWeapon(0);
    EntityEx.GetAddonBits(0);
    EntityEx.SetAddonBits(0, 0);
    EntityEx.GetObserverMode(0);
    EntityEx.GetObserverTarget(0);
    EntityEx.GetHitGroup(0);
    EntityEx.GetScore(0, true);
    EntityEx.GetScore(0, false);
    EntityEx.GetGravity(0);
    EntityEx.SetGravity(0, 0.0);
    EntityEx.GetMoney(0);
    EntityEx.SetMoney(0, 0);
    EntityEx.SetDetecting(0, false);
    EntityEx.SetHud(0, false, 0);
    EntityEx.SetArmsModel(0, "");
    EntityEx.SetAttack(0, 0.0);
    EntityEx.GetEffect(0);
    EntityEx.SetEffect(0, 0);
    EntityEx.SetFlashLight(0, false);
    EntityEx.SetFov(0);
    EntityEx.SetTextures(0);
    EntityEx.GetActivator(0);
    EntityEx.SetModelIndex(0, 0);
    EntityEx.GetOwner(0);
    EntityEx.SetOwner(0, 0);
    EntityEx.GetParent(0);
    EntityEx.SetParent(0, 0);
    EntityEx.GetRagdollIndex(0);
    EntityEx.GetCollisionGroup(0);
    EntityEx.SetCollisionGroup(0, 0);

    FileParser.PrecacheModel("");
    FileParser.PrecacheWeapon("");
    FileParser.PrecacheParticle("");

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
    hint.Display(0, "%s", "114 514");
    hint.DisplayAll("%s", "114 514");
    hint.tDisplay(0, "asdadad");
    hint.tDisplayAll("%d", 114514);
    hint.Destroy();

    CreateInstructorHint(0, 0.0, Icon_bulb, 0.0, 255, 255, 255, "%s", "sdashdjlkashdkl");
    CreateInstructorHintAll(0.0, Icon_bulb, 0.0, 0, 0, 0, "%s", "dkashdojyhasjkdaghskjds");

    Math.abs(0);
    Math.fabs(0.0);
    Math.min(0, 0);
    Math.max(0, 0);
    Math.clamp(0, 1, 2);
    Math.overflow(1, 2, 3);
    Math.sqrt(0.0);
    Math.GetPercentageFloat(0.0, 100.0);
    Math.GetPercentageInt(0, 100);
    Math.mean(vec);

    float matrix3x4[16];
    Matrix3x4.Identity(matrix3x4);
    Matrix3x4.RotateX(matrix3x4, 0.0);
    Matrix3x4.RotateY(matrix3x4, 0.0);
    Matrix3x4.RotateZ(matrix3x4, 0.0);
    Matrix3x4.Concatenate(matrix3x4, matrix3x4, matrix3x4);
    Matrix3x4.TransformPoint(matrix3x4, vec, vec);
    Matrix3x4.Rotate(matrix3x4, 0.0, 0, 0, 0);
    Matrix3x4.Scale(matrix3x4, 0.0, 0.0, 0.0);
    Matrix3x4.Translate(matrix3x4, vec);
    Matrix3x4.GetTranslate(matrix3x4, vec);
    Matrix3x4.RotateByMatrix(vec, matrix3x4, vec);
    Matrix3x4.RotationOnly(matrix3x4, matrix3x4);
    Matrix3x4.RotateMatrix(matrix3x4, 0.0, 0.0, 0.0, 0.0);
    Matrix3x4.InvertSimple(matrix3x4, matrix3x4);
    Matrix3x4.InvertRotation(matrix3x4, matrix3x4);

    MD5.Digest("", "", 0);

    char ASMTRAMPOLINE[64]="\x58\x59\x5a\x50\xb8\x00\x00\x00\x00\xff\xe0";
    Memory.CreateMemoryForSDKCall(gd);
    Memory.GetModuleSize(nullptr);
    Memory.memcpy(nullptr, ASMTRAMPOLINE, sizeof(ASMTRAMPOLINE));
    Memory.writeDWORD(ASMTRAMPOLINE, nullptr, 0);

    Message.Init();
    HudMsg.SetUMParams(scr, 0.0, arr, 0, 0.0, 0.0, 0.0);
    HudMsg.ToAll(0, "dsadsad%s", "Dsadasd");
    HudMsg.ToTeam(CS_TEAM_CT, 0, "djashdkjha%s", "dashdkjashd");
    HudMsg.ToOne(0, 0, "asdasd%s","dsakjdsad");
    HudMsg.ToOneEx(0, 0, 0.0, scr, arr, 0, 0.0, 0.0, 0.0, "dasjdlashdjash%s", "DSakdsakjdhkajsd");
    HudMsg.ToMultiple(arr, 4, 0, "dashdaksjdh%s", "dasdasd");

    Shake.Create(0, 0.0, 0.0, 0.0);
    Fade.Create(0, 0.0, 0.0, 0, arr);

    Numeric.HexToDec("0x16");
    Numeric.IsHexSymbol(1);
    ArrayList dynArr = new ArrayList();
    ParamParseString(dynArr, "dasda", 0, '1');
    StrExtract(ASMTRAMPOLINE, ASMTRAMPOLINE, 0, 0);
    StrContain(ASMTRAMPOLINE, ASMTRAMPOLINE, '1');
    ArrayShuffle(dynArr);
    Sort_ByLength(0, 0, dynArr, null);

    Particle.GetEffectIndex("asdads");
    Particle.PrecacheEffect("asdasd");
    Particle.GetEffectName(0, str, 4);
    Particle.GetEffectCount();
    Particle.Precache(0, str);

    Player p = Player(0);
    p.UserId;
    p.InBound;
    p.Connected;
    p.InGame;
    p.InKickQueue;
    p.SourceTV;
    p.Alive;
    p.Fake;
    p.Serial;
    p.GetFromSerial(0);
    p.GetFromUserId(0);
    p.IsExist(true);
    p.IsExist(false);
    p.IsHuman(true);
    p.IsHuman(false);
    p.Kick("sjadhaksjhdkja%s", "DSsahdkajshdas");
    p.KickEx("daskjdlkasjh%s", "Dsajhdkjashd");
    p.m_iTeamNum = 0;

    PlayerEx.IsExist(0, true);
    PlayerEx.IsExist(0, false);
    PlayerEx.IsHuman(0, true);
    PlayerEx.IsHuman(0, false);
    PlayerEx.GetPlayers(true, true, 0);
    PlayerEx.GetPlayers(true, false, 0);
    PlayerEx.GetPlayers(false, true, 0);
    PlayerEx.GetPlayers(false, false, 0);
    PlayerEx.GetTotalPlayers();
    PlayerEx.GetTeamPlayers(0);
    PlayerEx.GetTotalAlives();
    PlayerEx.GetTeamAlives(0);
    PlayerEx.CreateDeathIcon(0, 0, "d", false, false, false, false, 0);

    Server.GetIPAddress("127.0.0.1", 16, 27015);

    SoundEx.EmitSingle(0, "dashjdjahsd");
    SoundEx.EmitMultiple(arr, 4, "dasd");
    SoundEx.EmitAll("dahsjd");

    StringEx.ToLower("ADSADAS");
    StringEx.CountOccurence("dasdasd", 'a');
    StringEx.RandomOut(str, 16);
    StringEx.StrContainsEx(str, str);

    UTIL.RemoveEntity(0, 0.0);
    UTIL.CreateTrain("", vec, vec, "", "");
    UTIL.CreatePath("", vec, vec, "");
    UTIL.CreateMonster("", vec, vec, "");
    UTIL.CreatePhysics("", vec, vec, "");
    UTIL.CreateDynamic("", vec, vec, "");
    UTIL.CreateProjectile(vec, vec);
    UTIL.CreateSmoke(-1, vec, vec, "", "", "", "", "", "", "", "", "", "", "", "", 0.0, 0.0);
    UTIL.CreateParticle(-1, NULL_VECTOR, NULL_VECTOR, "", "", 0.0);
    UTIL.CreateExplosion(vec, 0, "", 0.0, 0.0, "", -1, -1, "");
    UTIL.CreateDamage(-1, vec, 0, 0.0, 0.0, DMG_GENERIC, -1, "");
    UTIL.CreateSprite(-1, vec, vec, "", "", "", "", 0.0);
    UTIL.CreateSpriteController(-1, "", "");
    UTIL.CreateTesla(-1, vec, vec, "", "", "", "", "", "", "", "", "", "", "", "", "", 0.0);
    UTIL.CreateShooter(0, "", _, _, _, "", _, _, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    UTIL.CreateBeam(vec, vec, "", "", "", "", "", "", "", "", "", "", "", "", 0, "", "", "", "", 0.0, 0.0, "");
    UTIL.CreateLight(_, _, _, _, _, _, _, _, _, "", 0.0, 0.0, _);
    UTIL.SpawnSpeaker(vec, vec, 0, _);
    UTIL.CreateGlowing(0, false, _, _, _, _, _);
    UTIL.GetRenderColor(0, Clr_R);
    UTIL.SetRenderColor(0, Clr_R, 0);
    UTIL.CreateTracer(0, "", "", vec, 0.0);
    UTIL.CreatePhysForce(0, vec, vec, 0.0, 0.0, 0.0);
    UTIL.PrecacheModel("");
    UTIL.PrecacheDecal("");
    UTIL.PrecacheSound("");
    UTIL.GetVelocityByAim(vec, vec, vec, vec, _, _);

    UTIL.IsOnSamePlane(0, 0, vec, PlayersFilter);
    UTIL.GetTraceEndPoint(0, vec);
    UTIL.TraceRay(0, 0, vec, vec, PlayersFilter);
    UTIL.GetDistanceBetween(0, 0);

}
