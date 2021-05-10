/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          convert.sp
 *  Description:   Console variables
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


#if defined _cvar_included
    #endinput
#endif

#define _cvar_included

/**
 * Cvar hook callback.
 * @brief Prevents changes of default cvars.
 * 
 * @param hConVar           The cvar handle.
 * @param oldValue          The value before the attempted change.
 * @param newValue          The new value.
 **/
public void CvarsLockOnCvarHook(ConVar hConVar, char[] oldValue, char[] newValue)
{
    // Revert to locked value
    hConVar.IntValue = 0;
}

/**
 * Cvar hook callback.
 * @brief Prevents changes of default cvars.
 * 
 * @param hConVar           The cvar handle.
 * @param oldValue          The value before the attempted change.
 * @param newValue          The new value.
 **/
public void CvarsUnlockOnCvarHook(ConVar hConVar, char[] oldValue, char[] newValue)
{
    // Revert to locked value
    hConVar.IntValue = 1;
}

/**
 * Cvar hook callback.
 * @brief Prevents changes of cheat cvars.
 * 
 * @param hConVar           The cvar handle.
 * @param oldValue          The value before the attempted change.
 * @param newValue          The new value.
 **/
public void CvarsLockOnCvarHook2(ConVar hConVar, char[] oldValue, char[] newValue)
{
    // Revert to locked value
    CvarsOnCheatSet(hConVar, 0);
}

/**
 * Cvar hook callback.
 * @brief Prevents changes of default cvars.
 * 
 * @param hConVar           The cvar handle.
 * @param oldValue          The value before the attempted change.
 * @param newValue          The new value.
 **/
public void CvarsLockOnCvarHook3(ConVar hConVar, char[] oldValue, char[] newValue)
{
    // Revert to locked value
    hConVar.SetString("");
}

/*
 * Stocks cvars API.
 */

/**
 * @brief Sets the integer value of a cvar variable. (sv_cheat 1)
 *
 * @param hConVar           Handle to the convar.
 * @param iValue            New integer value.
 **/
inline void CvarsOnCheatSet(ConVar hConVar, int iValue) 
{
    // Revert to locked value
    hConVar.Flags = (hConVar.Flags & ~FCVAR_CHEAT);
    hConVar.IntValue = iValue;
    //hConVar.Flags = hConVar.Flags | FCVAR_CHEAT;  -> Sent errors to console!
}