/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          const.sp
 *  Description:   Constant definitions.
 *
 *  Copyright (c) 2021 laper32.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ============================================================================
 */

#if defined _smlib2_const_included
    #endinput
#endif

#define _smlib2_const_included

// Useful constant macros
#define SMALL_LINE_LENGTH       32
#define NORMAL_LINE_LENGTH      64
#define BIG_LINE_LENGTH         128
#define CHAT_LINE_LENGTH        192
#define PLATFORM_LINE_LENGTH    256
#define HUGE_LINE_LENGTH        512
#define CONSOLE_LINE_LENGTH     1024
#define FILE_LINE_LENGTH        2048

#define DEFAULT_HULL_WIDTH      32.0

#define TEAM_NONE               0
#define TEAM_SPECTATOR          1    /**< Spectators        */
#define TEAM_T                  2    /**< Terrorist         */
#define TEAM_CT                 3    /**< Counter-Terrorist */

#define TEAM_ZOMBIE             2    /**< Zombies           */
#define TEAM_HUMAN              3    /**< Humans            */

#define SPECMODE_NONE           0
#define SPECMODE_FIRSTPERSON    4
#define SPECMODE_3RDPERSON      5
#define SPECMODE_FREELOOK       6

#define MAX_FLOAT               2147483647.0
#define MAX_INT                 2147483647
#define hasLength(%0)           (%0[0] != NULL_STRING[0]) 
#define string(%0)				%0, sizeof(%0)

#define TEXT_COLOR_DEFAILT              "\x01"
#define TEXT_COLOR_NORMAL               "\x01"
#define TEXT_COLOR_WHITE                "\x01"

#define TEXT_COLOR_DARKRED              "\x02"
#define TEXT_COLOR_PINK                 "\x03"
#define TEXT_COLOR_GREEN                "\x04"

#define TEXT_COLOR_LIME                 "\x05"
#define TEXT_COLOR_YELLOW               "\x05"

#define TEXT_COLOR_LIGHTGREEN           "\x06"

#define TEXT_COLOR_LIGHTRED             "\x07"
#define TEXT_COLOR_RED                  "\x07"

#define TEXT_COLOR_GREY                 "\x08"
#define TEXT_COLOR_GRAY                 "\x08"

#define TEXT_COLOR_OLIVE                "\x09"
#define TEXT_COLOR_ORANGE               "\x10"
#define TEXT_COLOR_SILVER               "\x0A"
#define TEXT_COLOR_LIGHTBLUE            "\x0B"
#define TEXT_COLOR_BLUE                 "\x0C"
#define TEXT_COLOR_PURPLE               "\x0E"
#define TEXT_COLOR_DARKORANGE           "\x0F"
// === END ===

/**
 * @section Damage type values.
 **/
#define DAMAGE_NO               0
#define DAMAGE_EVENTS_ONLY      1    //! Call damage functions, but don't modify health
#define DAMAGE_YES              2
#define DAMAGE_AIM              3
/**
 * @endsection
 **/

/**
 * @section Water levels.
 **/
#define WLEVEL_CSGO_DRY         0
#define WLEVEL_CSGO_FEET        1
#define WLEVEL_CSGO_HALF        2
#define WLEVEL_CSGO_FULL        3
/**
 * @endsection
 **/

/**
 * @section Explosion flags.
 **/
#define EXP_NODAMAGE                (1<<0)
#define EXP_REPEATABLE              (1<<1)
#define EXP_NOFIREBALL              (1<<2)
#define EXP_NOSMOKE                 (1<<3)
#define EXP_NODECAL                 (1<<4)
#define EXP_NOSPARKS                (1<<5)
#define EXP_NOSOUND                 (1<<6)
#define EXP_RANDOMORIENTATION       (1<<7)
#define EXP_NOFIREBALLSMOKE         (1<<8)
#define EXP_NOPARTICLES             (1<<9)
#define EXP_NODLIGHTS               (1<<10)
#define EXP_NOCLAMPMIN              (1<<11)
#define EXP_NOCLAMPMAX              (1<<12)
#define EXP_NOUNDERWATER            (1<<13)
#define EXP_GENERICDAMAGE           (1<<14)
/**
 * @endsection
 **/

/**
 * @section Train flags.
 **/ 
#define TRAIN_NOPITCH               (1<<0)
#define TRAIN_NOCONTROL             (1<<1)
#define TRAIN_PASSABLE              (1<<2)
#define TRAIN_FIXED                 (1<<3)
#define TRAIN_HL1TRAIN              (1<<7)
#define TRAIN_USESPEEDFORSOUND      (1<<8)
#define TRAIN_UNBLOCKABLE           (1<<9)
#define TRAIN_ALLOWROLL             (1<<10) 
/**
 * @endsection
 **/

/**
 * @section Path flags.
 **/
#define PATH_DISABLED               (1<<0)
#define PATH_FIREONE                (1<<1)
#define PATH_BRANCHRESERVE          (1<<2)
#define PATH_DISABLETRAIN           (1<<3)
#define PATH_TELEPORTTOTHIS         (1<<4)
/** 
 * @endsection  
 **/ 

/** 
 * @section NPC flags.  
 **/    
#define NPC_WAITTILLSEEN            (1<<0)
#define NPC_GAG                     (1<<1)
#define NPC_FALLTOGROUND            (1<<2)
#define NPC_DROPHEALTHKIT           (1<<3)
#define NPC_EFFICIENT               (1<<4)
#define NPC_WAITFORSCRIPT           (1<<7)
#define NPC_LONGVISIBILITY          (1<<8)
#define NPC_FADECORPSE              (1<<9)
#define NPC_OUTSIDEPVS              (1<<10)
#define NPC_TEMPLATE                (1<<11)
#define NPC_ALTCOLLISION            (1<<12)
#define NPC_DONTDROPWEAPONS         (1<<13)
#define NPC_IGNOREPLAYERPUSH        (1<<14)
/**
 * @endsection
 **/

/**
 * @section Physics flags.
 **/
#define PHYS_STARTASLEEP            (1<<0)
#define PHYS_NOPHYSDAMAGE           (1<<1)
#define PHYS_DEBRIS                 (1<<2)
#define PHYS_MOTIONDISABLED         (1<<3)
#define PHYS_MOTIONONCANNON         (1<<6)
#define PHYS_NOTAFFECTBYROTOR       (1<<7)
#define PHYS_GENERATEUSE            (1<<8)
#define PHYS_PREVENTPICKUP          (1<<9)
#define PHYS_PREVENTBUMP            (1<<10)
#define PHYS_DEBRISTRIGGER          (1<<12)
#define PHYS_FORCESERVERSIDE        (1<<13)
#define PHYS_PHYSGUNALWAYS          (1<<20)    
/**
 * @endsection
 **/

/**
 * @section Dynamic flags.
 **/
#define DYN_HITBOXCOLLISION         (1<<6)
#define DYN_COLLISIONDISABLED       (1<<7)
/**
 * @endsection
 **/

/**
 * @section Beam flags.
 **/
#define BEAM_STARTON                (1<<0)
#define BEAM_TOGGLE                 (1<<1)
#define BEAM_RANDOMSTRIKE           (1<<2)
#define BEAM_RING                   (1<<3)
#define BEAM_STARTSPARKS            (1<<4)
#define BEAM_ENDSPARKS              (1<<5)
#define BEAM_DECALEND               (1<<6)
#define BEAM_SHADESTART             (1<<7)
#define BEAM_SHADEEND               (1<<8)
#define BEAM_TAPEROUT               (1<<9)
/**
 * @endsection
 **/

/**
 * @section Light flags.
 **/
#define LIGHT_NOWORLD               (1<<0)
#define LIGHT_NOMODELS              (1<<1)
#define LIGHT_ADDALPHA              (1<<2)
#define LIGHT_SUBALPHA              (1<<3)
/**
 * @endsection
 **/

/**
 * @section Addon bits.
 **/
#define CSAddon_NONE                0
#define CSAddon_Flashbang1          (1<<0)
#define CSAddon_Flashbang2          (1<<1)
#define CSAddon_HEGrenade           (1<<2)
#define CSAddon_SmokeGrenade        (1<<3)
#define CSAddon_C4                  (1<<4)
#define CSAddon_DefuseKit           (1<<5)
#define CSAddon_PrimaryWeapon       (1<<6)
#define CSAddon_SecondaryWeapon     (1<<7)
#define CSAddon_Holster             (1<<8) 
#define CSAddon_Decoy               (1<<9)
#define CSAddon_Knife               (1<<10)
#define CSAddon_FaceMask            (1<<11)
#define CSAddon_TaGrenade           (1<<12)
#define CSAddon_Shield              (1<<13)
/**
 * @endsection
 **/

/**
 * @section Hud elements flags.
 **/
#define HIDEHUD_WEAPONSELECTION     (1<<0)   /// Hide ammo count & weapon selection
#define HIDEHUD_FLASHLIGHT          (1<<1)
#define HIDEHUD_ALL                 (1<<2)
#define HIDEHUD_HEALTH              (1<<3)   /// Hide health & armor / suit battery
#define HIDEHUD_PLAYERDEAD          (1<<4)   /// Hide when local player's dead
#define HIDEHUD_NEEDSUIT            (1<<5)   /// Hide when the local player doesn't have the HEV suit
#define HIDEHUD_MISCSTATUS          (1<<6)   /// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
#define HIDEHUD_CHAT                (1<<7)   /// Hide all communication elements (saytext, voice icon, etc)
#define HIDEHUD_CROSSHAIR           (1<<8)   /// Hide crosshairs
#define HIDEHUD_VEHICLE_CROSSHAIR   (1<<9)   /// Hide vehicle crosshair
#define HIDEHUD_INVEHICLE           (1<<10)
#define HIDEHUD_BONUS_PROGRESS      (1<<11)  /// Hide bonus progress display (for bonus map challenges)
#define HIDEHUD_RADAR               (1<<12)
/**
 * @endsection
 **/

/**
 * @section Entity effects flags.
 **/
#define EF_BONEMERGE                (1<<0)     /// Performs bone merge on client side
#define EF_BRIGHTLIGHT              (1<<1)     /// DLIGHT centered at entity origin
#define EF_DIMLIGHT                 (1<<2)     /// Player flashlight
#define EF_NOINTERP                 (1<<3)     /// Don't interpolate the next frame
#define EF_NOSHADOW                 (1<<4)     /// Disables shadow
#define EF_NODRAW                   (1<<5)     /// Prevents the entity from drawing and networking
#define EF_NORECEIVESHADOW          (1<<6)     /// Don't receive shadows
#define EF_BONEMERGE_FASTCULL       (1<<7)     /// For use with EF_BONEMERGE. If this is set, then it places this ents origin at its parent and uses the parent's bbox + the max extents of the aiment. Otherwise, it sets up the parent's bones every frame to figure out where to place the aiment, which is inefficient because it'll setup the parent's bones even if the parent is not in the PVS.
#define EF_ITEM_BLINK               (1<<8)     /// Makes the entity blink
#define EF_PARENT_ANIMATES          (1<<9)     /// Always assume that the parent entity is animating
#define EF_FOLLOWBONE               (1<<10)    
/**
 * @endsection
 **/

/**
 * @section Fade flags.
 **/
#define FFADE_IN                    0x0001      /// Just here so we don't pass 0 into the function
#define FFADE_OUT                   0x0002      /// Fade out (not in)
#define FFADE_MODULATE              0x0004      /// Modulate (don't blend)
#define FFADE_STAYOUT               0x0008      /// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE                 0x0010      /// Purges all other fades, replacing them with this one
/**
 * @endsection
 **/

/**
 * @section Solid types.
 **/
#define SOLID_NONE                  0  /// no solid model 
#define SOLID_BSP                   1  /// BSP tree 
#define SOLID_BBOX                  2  /// an AABB 
#define SOLID_OBB                   3  /// an OBB 
#define SOLID_OBB_YAW               4  /// an OBB, constrained so that it can only yaw 
#define SOLID_CUSTOM                5  /// always call into the entity for tests 
#define SOLID_VPHYSICS              6  /// solid vphysics object, get vcollide from the model and collide with that 
#define SOLID_LAST                  7  /// custom solid last
/**
 * @endsection
 **/

/**
 * @section Collision groups.
 **/
#define COLLISION_GROUP_NONE                0   /// Default; collides with static and dynamic objects. 
#define COLLISION_GROUP_DEBRIS              1   /// Collides with nothing but world and static stuff. 
#define COLLISION_GROUP_DEBRIS_TRIGGER      2   /// Same as debris, but hits triggers. 
#define COLLISION_GROUP_INTERACTIVE_DEBRIS  3   /// Collides with everything except other interactive debris or debris. 
#define COLLISION_GROUP_INTERACTIVE         4   /// Collides with everything except interactive debris or debris. 
#define COLLISION_GROUP_PLAYER              5   /// This is the default behavior expected for most prop_physics. 
#define COLLISION_GROUP_BREAKABLE_GLASS     6   /// Special group for glass debris. 
#define COLLISION_GROUP_VEHICLE             7   /// Collision group for driveable vehicles. 
#define COLLISION_GROUP_PLAYER_MOVEMENT     8   /// For HL2, same as Collision_Group_Player. 
#define COLLISION_GROUP_NPC                 9   /// Generic NPC group. 
#define COLLISION_GROUP_IN_VEHICLE          10  /// For any entity inside a vehicle. 
#define COLLISION_GROUP_WEAPON              11  /// For any weapons that need collision detection. 
#define COLLISION_GROUP_VEHICLE_CLIP        12  /// Vehicle clip brush to restrict vehicle movement. 
#define COLLISION_GROUP_PROJECTILE          13  /// Projectiles. 
#define COLLISION_GROUP_DOOR_BLOCKER        14  /// Blocks entities not permitted to get near moving doors. 
#define COLLISION_GROUP_PASSABLE_DOOR       15  /// Doors that the player shouldn't collide with. 
#define COLLISION_GROUP_DISSOLVING          16  /// Things that are dissolving are in this group. 
#define COLLISION_GROUP_PUSHAWAY            17  /// Nonsolid on client and server, pushaway in player code. 
#define COLLISION_GROUP_NPC_ACTOR           18  /// Used so NPCs in scripts ignore the player.
/**
 * @endsection
 **/

/**
 * @section Solid flags.
 **/
#define FSOLID_CUSTOMRAYTEST                0x0001     /// Ignore solid type + always call into the entity for ray tests
#define FSOLID_CUSTOMBOXTEST                0x0002     /// Ignore solid type + always call into the entity for swept box tests
#define FSOLID_NOT_SOLID                    0x0004     /// Are we currently not solid?
#define FSOLID_TRIGGER                      0x0008     /// This is something may be collideable but fires touch functions
#define FSOLID_NOT_STANDABLE                0x0010     /// You can't stand on this
#define FSOLID_VOLUME_CONTENTS              0x0020     /// Contains volumetric contents (like water)
#define FSOLID_FORCE_WORLD_ALIGNED          0x0040     /// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
#define FSOLID_USE_TRIGGER_BOUNDS           0x0080     /// Uses a special trigger bounds separate from the normal OBB
#define FSOLID_ROOT_PARENT_ALIGNED          0x0100     /// Collisions are defined in root parent's local coordinate space
#define FSOLID_TRIGGER_TOUCH_DEBRIS         0x0200     /// This trigger will touch debris objects
/**
 * @endsection
 **/
 
/**
 * @section Material types.
 **/ 
#define MAT_NONE       "-1"
#define MAT_GLASS       "0"
#define MAT_WOOD        "1"
#define MAT_METAL       "2"
#define MAT_FLESH       "3"    
#define MAT_CONCRETE    "4"    
/**
 * @endsection
 **/

/** 
 * @section Number of valid def indexes.
 *
 * @link https://tf2b.com/itemlist.php?gid=730
 **/
enum ItemDef
{
    ItemDef_Invalid = 0,          /** Used as return value when a def doens't exist. */

    ItemDef_Deagle = 1,
    ItemDef_Elite,
    ItemDef_FiveSeven,
    ItemDef_Glock,
    ItemDef_AK47 = 7,
    ItemDef_AUG,
    ItemDef_AWP,
    ItemDef_Famas,
    ItemDef_G3SG1,
    ItemDef_GalilAR = 13,
    ItemDef_M249,
    ItemDef_M4A4 = 16,
    ItemDef_MAC10,
    ItemDef_P90 = 19,
    ItemDef_MP5 = 23,
    ItemDef_UMP45,
    ItemDef_XM1014,
    ItemDef_Bizon,
    ItemDef_MAG7,
    ItemDef_Negev,
    ItemDef_SawedOff,
    ItemDef_TEC9,
    ItemDef_Taser,
    ItemDef_HKP2000,
    ItemDef_MP7,
    ItemDef_MP9,
    ItemDef_Nova,
    ItemDef_P250,
    ItemDef_Shield,
    ItemDef_SCAR20,
    ItemDef_SG553,
    ItemDef_SSG08,
    ItemDef_Knife,
    ItemDef_KnifeGG,
    ItemDef_FlashBang,
    ItemDef_HEGrenade,
    ItemDef_SmokeGrenade,
    ItemDef_Molotov,
    ItemDef_Decoy,
    ItemDef_IncGrenade,
    ItemDef_C4,
    ItemDef_Kevlar,
    ItemDef_KevlarHelmet,
    ItemDef_HeavySuit,
    ItemDef_NGVs = 54,
    ItemDef_Defuser,
    ItemDef_Cutters,
    ItemDef_Healthshot,
    ItemDef_KnifeT = 59,
    ItemDef_M4A1,
    ItemDef_USP,
    ItemDef_CZ75A = 63,
    ItemDef_Revolver,
    ItemDef_TAGrenade = 68,
    ItemDef_Fists,
    ItemDef_BreachCharge,
    ItemDef_Tablet = 72,
    ItemDef_Melee = 74,
    ItemDef_Axe,
    ItemDef_Hammer,
    ItemDef_Wrench = 78,
    ItemDef_KnifeGhost = 80,
    ItemDef_FireBomb,
    ItemDef_DiversionDevice,
    ItemDef_FragGrenade,
    ItemDef_SnowBall,
    ItemDef_BumpMine,
    ItemDef_Bayonet = 500,
    ItemDef_Classic = 503,
    ItemDef_FlipKnife = 505,
    ItemDef_GutKnife = 506,
    ItemDef_Karambit = 507,
    ItemDef_M9_Bayonet = 508,
    ItemDef_HuntsmanKnife = 509,
    ItemDef_FalchionKnife = 512,
    ItemDef_BowieKnife = 514,
    ItemDef_ButterflyKnife = 515,
    ItemDef_ShadowDaggers = 516,
    ItemDef_UrsusKnife = 519,
    ItemDef_NavajaKnife = 520,
    ItemDef_StilettoKnife = 522,
    ItemDef_TalonKnife = 523 
};
#define IsGrenade(%0)       (%0 == ItemDef_TAGrenade                                || \
                             %0 == ItemDef_HEGrenade                                || \
                             %0 == ItemDef_SmokeGrenade                             || \
                             %0 == ItemDef_FlashBang                                || \
                             %0 == ItemDef_BreachCharge                             || \
                             (%0 >= ItemDef_Molotov && %0 <= ItemDef_IncGrenade)    || \
                             (%0 >= ItemDef_FireBomb && %0 <= ItemDef_BumpMine))

#define IsProjectile(%0)    (%0 == ItemDef_TAGrenade                                || \
                             %0 == ItemDef_HEGrenade                                || \
                             %0 == ItemDef_SmokeGrenade                             || \
                             %0 == ItemDef_FlashBang                                || \
                             (%0 >= ItemDef_Molotov && %0 <= ItemDef_IncGrenade)    || \
                             (%0 >= ItemDef_FireBomb && %0 <= ItemDef_FragGrenade))

#define IsFireble(%0)       (%0 == ItemDef_Molotov                                  || \
                             %0 == ItemDef_IncGrenade                               || \
                             %0 == ItemDef_FireBomb)

#define IsKnife(%0)         (%0 == ItemDef_Knife                                    || \
                             %0 == ItemDef_KnifeGG                                  || \
                             %0 == ItemDef_KnifeT                                   || \
                             (%0 >= ItemDef_Melee && %0 <= ItemDef_Wrench)          || \
                             %0 == ItemDef_KnifeGhost                               || \
                             (%0 >= ItemDef_Bayonet))
                             
#define IsMelee(%0)         (IsKnife(%0) || %0 == ItemDef_Fists)

#define IsItem(%0)          (%0 == ItemDef_Kevlar || \
                             %0 == ItemDef_KevlarHelmet || \
                             %0 == ItemDef_NGVs || \
                             %0 == ItemDef_Defuser || \
                             %0 == ItemDef_HeavySuit || \
                             %0 == ItemDef_Cutters)

#define IsPistol(%0)        (%0 == ItemDef_Glock                                    || \
                             %0 == ItemDef_Elite                                    || \
                             %0 == ItemDef_FiveSeven                                || \
                             %0 == ItemDef_USP                                      || \
                             %0 == ItemDef_Deagle                                   || \
                             %0 == ItemDef_TEC9                                     || \
                             %0 == ItemDef_P250                                     || \
                             %0 == ItemDef_CZ75A                                    || \
                             %0 == ItemDef_HKP2000                                  || \
                             %0 == ItemDef_Revolver)

#define IsSMG(%0)           (%0 == ItemDef_MP5                                      || \
                             %0 == ItemDef_MAC10                                    || \
                             %0 == ItemDef_UMP45                                    || \
                             %0 == ItemDef_MP9                                      || \
                             %0 == ItemDef_Bizon                                    || \
                             %0 == ItemDef_MP7                                      || \
                             %0 == ItemDef_P90)

#define IsSR(%0)            (%0 == ItemDef_AWP                                      || \
                             %0 == ItemDef_SSG08                                    || \
                             %0 == ItemDef_SCAR20                                   || \
                             %0 == ItemDef_G3SG1)

#define IsSG(%0)            (%0 == ItemDef_Nova                                     || \
                             %0 == ItemDef_SawedOff                                 || \
                             %0 == ItemDef_MAG7                                     || \
                             %0 == ItemDef_XM1014)

#define IsMG(%0)            (%0 == ItemDef_Negev                                    || \
                             %0 == ItemDef_M249)

#define IsAR(%0)            (%0 == ItemDef_AK47                                     || \
                             %0 == ItemDef_M4A1                                     || \
                             %0 == ItemDef_M4A4                                     || \
                             %0 == ItemDef_GalilAR                                  || \
                             %0 == ItemDef_Famas                                    || \
                             %0 == ItemDef_SG553                                    || \
                             %0 == ItemDef_AUG)
/**
 * @endsection
 **/

/**
 * @section Number of valid render types.
 **/
enum RenderingColorType     
{
    Clr_R,
    Clr_G,
    Clr_B,
    Clr_A
};
/**
 * @endsection
 **/ 

/**
 * @section List of components that make up the model rectangular boundaries.
 * 
 * F = Front
 * B = Back
 * L = Left
 * R = Right
 * U = Upper
 * D = Down
 **/
enum /*BoxBound*/
{
    BoxBound_FUR,       /** Front upper right */
    BoxBound_FUL,       /** etc.. */
    BoxBound_FDR,
    BoxBound_FDL,
    BoxBound_BUR,
    BoxBound_BUL,
    BoxBound_BDR,
    BoxBound_BDL,
    
    BoxBound
};
/**
 * @endsection
 **/

enum OS {
    OS_Unknown,

    OS_Windows,
    OS_Linux,
    OS_Mac
}
