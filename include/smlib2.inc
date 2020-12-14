#if defined _smlib2_included
#endinput
#endif
#define _smlib2_included

#define inline stock
#define extern native

#if !defined _sourcemod_included
#include <sourcemod>
#endif

#if !defined _sdktools_included
#include <sdktools>
#endif

#if !defined _sdkhooks_included
#include <sdkhooks>
#endif

#if !defined _cstrike_included
#include <cstrike>
#endif

#if !defined _ptah_included
#include <ptah>
#endif

#if !defined _dhooks_included
#include <dhooks>
#endif

#include <smlib2/const.inc>
#include <smlib2/engine.inc>
#include <smlib2/math.inc>
#include <smlib2/mem.inc>
#include <smlib2/paramparser.inc>
#include <smlib2/fileparser.inc>
#include <smlib2/tools.inc>
#include <smlib2/utils.inc>
#include <smlib2/text.inc>
#include <smlib2/playermgr.inc>
#include <smlib2/hint.inc>
#include <smlib2/md5.inc>
#include <smlib2/base64.inc>

// Here is used for _ArmsFix_ Extension
// Do not edit it unless you _EXACTLY_ know what you are doing!
public Extension _ext_armsFix = 
{
	name = "ArmsFix",
	file = "ArmsFix.ext.2.csgo",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0
#endif
};