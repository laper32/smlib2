/**
 * ============================================================================  
 *  
 *  SourceMod Library 2
 *
 *  Copyright (c) 2021 laper32.
 *  
 *  Regards to Zombie-Plague, sourcemod-util, smlib, and any other library
 *  what have not covered here. These libs what have mentioned above have
 *  provided many useful functions for me to develop this project.
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


#if defined _smlib2_included
#endinput
#endif
#define _smlib2_included

#define inline stock
#define extern native

// To let most of these functions works, you must include following parts:
// - sourcemod
// - sdktools
// - sdkhooks

// Additionally, I recommend you include:
// - dhooks

// These are game-specific. You should determine whether you actually needed:
// - PTaH
// - cstrike
// - tf2
// - ...(Any other game-specifics)

// I recommend you include these libraries above before you include <smlib2> to let it fully works, as 
// I have said before.

#include <smlib2/const>

#include <smlib2/cvar>
#include <smlib2/convert>
// #include <smlib2/engine>
// #include <smlib2/math>
// #include <smlib2/matrix>
// #include <smlib2/numeric>
// #include <smlib2/memory>
// #include <smlib2/string>
// #include <smlib2/paramparser>
// #include <smlib2/fileparser>
// #include <smlib2/server>

// #include <smlib2/entity>
// #include <smlib2/player>
// #include <smlib2/message>
// #include <smlib2/tools>
// #include <smlib2/hint>
// #include <smlib2/sound>
// #include <smlib2/utility>

// #if defined USE_DLL
//     #include <smlib2/hashlib>
// #else
//     #include <smlib2/md5>
//     #include <smlib2/base64>
// #endif

// #include <smlib2/version>

// #if defined USE_DLL
//     public Extension __ext_smlib2 =
//     {
//         name = "smlib2",
//         file = "smlib2.ext",
//     #if defined AUTOLOAD_EXTENSIONS
//         autoload = 1,
//     #else
//         autoload = 0,
//     #endif
//     #if defined REQUIRE_EXTENSIONS
//         required = 1,
//     #else
//         required = 0,
//     #endif
//     };
// #endif