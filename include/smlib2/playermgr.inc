/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          playermgr.sp
 *  Type:          Player
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

#if defined _playermgr_included
#endinput
#endif
#define _playermgr_included

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

inline int GetPlayingCount()
{
    // Initialize index
    int iPlaying;

    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Validate client
        if (IsPlayerExist(i, false))
        {
            // Increment amount
            iPlaying++;
        }
    }
    
    // Return amount
    return iPlaying;
}

/**
 * @brief Gets amount of total alive players.
 *
 * @return                  The amount of total alive players.
 **/
inline int GetAliveCount()
{
    // Initialize index
    int iAlive;

    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Validate client
        if (IsPlayerExist(i))
        {
            // Increment amount
            iAlive++;
        }
    }
    
    // Return amount
    return iAlive;
}