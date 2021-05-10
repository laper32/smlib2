/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          playermgr.sp
 *  Description:   Player Manager
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

#if defined _smlib2_playermgr_included
#endinput
#endif
#define _smlib2_playermgr_included

/**
 * @brief Returns true if the player is connected and alive, false if not.
 *
 * @param client            The client index.
 * @param bAlive            (Optional) Set to true to validate that the client is alive, false to ignore.
 *  
 * @return                  True or false.
 **/
inline bool IsPlayerExist(int client, bool bAlive = true)
{
    // If client isn't valid, then stop
    if (client <= 0 || client > MaxClients)
    {
        return false;
    }

    // If client isn't connected, then stop
    if (!IsClientConnected(client))
    {
        return false;
    }

    // If client isn't in game, then stop
    if (!IsClientInGame(client) || IsClientInKickQueue(client))
    {
        return false;
    }

    // If client is TV, then stop
    if (IsClientSourceTV(client))
    {
        return false;
    }

    // If client isn't alive, then stop
    if (bAlive && !IsPlayerAlive(client))
    {
        return false;
    }

    // If client exist
    return true;
}

/**
 * @brief Returns whether a player is in a spesific group or not.
 * 
 * @note This is only works in default SourceMod Admin.
 * If you have your own management system, DO NOT USE THIS FUNCTION, OR YOU WILL GET INTO TROUBLE!
 *
 * @param client            The client index.
 * @param sGroup            The SourceMod group name to check.
 *
 * @return                  True or false.
 **/
inline bool IsPlayerInGroup(int client, char[] sGroup)
{
    // Validate client
    if (!IsPlayerExist(client, false))
    {
        return false;
    }

    /*********************************
     *                               *
     *   FLAG GROUP AUTHENTICATION   *
     *                               *
     *********************************/

    // Finds a group by name
    GroupId nGroup = FindAdmGroup(sGroup);
    
    // Validate group
    if (nGroup == INVALID_GROUP_ID)
    {
        return false;
    }
     
    // Retrieves a client AdminId
    AdminId iD = GetUserAdmin(client);
    
    // Validate id
    if (iD == INVALID_ADMIN_ID)
    {
        return false;
    }

    // Initialize group char
    static char sGroupName[SMALL_LINE_LENGTH];

    // Gets immunity level
    int iImmunity = GetAdmGroupImmunityLevel(nGroup);
    
    // i = group index
    int iSize = GetAdminGroupCount(iD);
    for (int i = 0; i < iSize; i++)
    {
        // Gets group name
        nGroup = GetAdminGroup(iD, i, sGroupName, sizeof(sGroupName));

        // Validate groups
        if (!strcmp(sGroup, sGroupName, false) || iImmunity <= GetAdmGroupImmunityLevel(nGroup))
        {
            return true;
        }
    }
    
    // No groups or no match
    return false;
}

/**
 * @brief Get players in the game.
 *
 * @param aliveOnly             Sets true to count alive only.
 * @param teamOnly              Sets true to count team only.
 * @param teamNum               Team specified.
 *
 * @return                      Players what have been counted.
 */
inline int GetPlayers(bool aliveOnly, bool teamOnly, int teamNum)
{
    if (aliveOnly)
    {
        return (teamOnly) ? GetTeamAlives(teamNum) : GetTotalAlives();
    }
    else
    {
        return (teamOnly) ? GetTeamPlayers(teamNum) : GetTotalPlayers();
    }
}

/**
 * @brief Gets total players in the game.
 *
 * @return                      Total players in the game.
 */
inline int GetTotalPlayers()
{
    int iPlayer;

    for (int client = 1; client <= MaxClients; client++)
    {
        if (IsPlayerExist(client, false)) 
        {
            iPlayer++;
        }
    }
    return iPlayer;
}

/**
 * @brief Gets total team players in the game.
 *
 * @param team                  Team number.
 *
 * @return                      Total team players in the game.
 */
inline int GetTeamPlayers(int team)
{
    int iPlayer;

    for (int client = 1; client <= MaxClients; client++)
    {
        if (IsPlayerExist(client, false) && (GetClientTeam(client) == team)) 
        {
            iPlayer++;
        }
    }
    return iPlayer;
}

/**
 * @brief Gets total alive players in the game.
 *
 * @return                      Total alive players in the game.
 */
inline int GetTotalAlives()
{
    int iPlayer;

    for (int client = 1; client <= MaxClients; client++)
    {
        if (IsPlayerExist(client)) 
        {
            iPlayer++;
        }
    }
    return iPlayer;
}

/**
 * @brief Gets total alive team players in the game.
 *
 * @param team                  Team number.
 *
 * @return                      Total alive team players in the game.
 */
inline int GetTeamAlives(int team)
{
    int iPlayer;

    for (int client = 1; client <= MaxClients; client++)
    {
        if (IsPlayerExist(client) && (GetClientTeam(client) == team)) 
        {
            iPlayer++;
        }
    }
    return iPlayer;
}