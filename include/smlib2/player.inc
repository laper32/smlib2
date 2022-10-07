/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          player.sp
 *  Description:   Player.
 *
 *  Copyright (c) 2022 laper32.
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

#if defined _smlib2_player_included
#endinput
#endif
#define _smlib2_player_included

methodmap Player < Entity {
    public Player(int client) {
        return view_as<Player>(client);
    }

    property int UserId {
        public get() {
            return GetClientUserId(this.Index);
        }
    }

    property bool InBound {
        public get() {
            return (this.Index > 0 && this.Index <= MaxClients);
        }
    }

    property bool Connected {
        public get() {
            return IsClientConnected(this.Index);
        }
    }

    property bool InGame {
        public get() {
            return IsClientInGame(this.Index);
        }
    }

    property bool InKickQueue {
        public get() {
            return IsClientInKickQueue(this.Index);
        }
    }

    property bool SourceTV {
        public get() {
            return IsClientSourceTV(this.Index);
        }
    }

    property bool Alive {
        public get() {
            return IsPlayerAlive(this.Index);
        }
    }

    property bool Fake {
        public get() {
            return IsFakeClient(this.Index);
        }
    }

    property int Serial {
        public get() {
            return GetClientSerial(this.Index);
        }
    }

    public int GetFromSerial(int serial) {
        return GetClientFromSerial(serial);
    }

    public int GetFromUserId(int userid) {
        return GetClientOfUserId(userid);
    }

    public bool IsExist(bool alive=true) {
        if (!this.InBound) {
            return false;
        }

        if (!this.Connected) {
            return false;
        }

        if (!this.InGame || this.InKickQueue) {
            return false;
        }

        if (this.SourceTV) {
            return false;
        }

        if (alive && !this.Alive) {
            return false;
        }

        return true;
    }

    public bool IsHuman(bool alive=true) {
        if (this.IsExist(alive)) {
            if (!this.Fake) {
                return true;
            }
        }
        return false;
    }

    public void Kick(const char[] buffer="", any ...) {
        char message[512];
        VFormat(message, sizeof(message), buffer, 2);
        KickClient(this.Index, message);
    }

    public void KickEx(const char[] buffer="", any ...) {
        char message[512];
        VFormat(message, sizeof(message), buffer, 2);
        KickClientEx(this.Index, message);
    }

    property int m_iTeamNum {
        public get() {
            return GetEntProp(this.Index, Prop_Data, "m_iTeamNum");
        }
        public set(int val) {
            // <= TEAM_SPECTATOR
            if (this.m_iTeamNum <= TEAM_SPECTATOR) {
                ChangeClientTeam(this.Index, val);
            } else {
                #if defined _cstrike_included
                    CS_SwitchTeam(this.Index, val);
                #elseif defined _tf2_stocks_included
                    TF2_ChangeClientTeam(this.Index, view_as<TFTeam>(val));
                #else
                    PrintToServer("No game-specific library found.");
                    PrintToServer("You must include game-specific library to let this setter works.");
                #endif
            }
        }
    }
}

methodmap PlayerEx < EntityEx {
    /**
    * @brief Returns true if the player is connected and alive, false if not.
    *
    * @param client            The client index.
    * @param bAlive            (Optional) Set to true to validate that the client is alive, false to ignore.
    *  
    * @return                  True or false.
    **/
    public static bool IsExist(int client, bool bAlive = true)
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
     * @brief Gets whether the player is human.
     *
     * @param client            The client index.
     * @param bAlive            (Optional) Set to true to validate that the client is alive, false to ignore.
     *
     * @return                  T/F.
     */
    public static bool IsHuman(int client, bool bAlive = true) {
        return (PlayerEx.IsExist(client, bAlive) && !IsFakeClient(client));
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
    public static int GetPlayers(bool aliveOnly, bool teamOnly, int teamNum)
    {
        if (aliveOnly)
        {
            return (teamOnly) ? PlayerEx.GetTeamAlives(teamNum) : PlayerEx.GetTotalAlives();
        }
        else
        {
            return (teamOnly) ? PlayerEx.GetTeamPlayers(teamNum) : PlayerEx.GetTotalPlayers();
        }
    }

    /**
     * @brief Gets total players in the game.
     *
     * @return                      Total players in the game.
     */
    public static int GetTotalPlayers()
    {
        int iPlayer;

        for (int client = 1; client <= MaxClients; client++)
        {
            if (PlayerEx.IsExist(client, false)) 
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
    public static int GetTeamPlayers(int team)
    {
        int iPlayer;

        for (int client = 1; client <= MaxClients; client++)
        {
            if (PlayerEx.IsExist(client, false) && (GetClientTeam(client) == team)) 
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
    public static int GetTotalAlives()
    {
        int iPlayer;

        for (int client = 1; client <= MaxClients; client++)
        {
            if (PlayerEx.IsExist(client)) 
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
    public static int GetTeamAlives(int team)
    {
        int iPlayer;

        for (int client = 1; client <= MaxClients; client++)
        {
            if (PlayerEx.IsExist(client) && (GetClientTeam(client) == team)) 
            {
                iPlayer++;
            }
        }
        return iPlayer;
    }

    /**
     * @brief Create a death icon.
     * 
     * @param userID            The user id who victim.
     * @param attackerID        The user id who killed.
     * @param sIcon             The icon name.
     * @param bHead             (Optional) States the additional headshot icon.
     * @param bPenetrated       (Optional) Number of objects shot penetrated before killing target.
     * @param bRevenge          (Optional) Killer get revenge on victim with this kill.
     * @param bDominated        (Optional) Did killer dominate victim with this kill.
     * @param assisterID        (Optional) The user id who assisted in the kill.
     */
    public static void CreateDeathIcon(
        int userID,                 int attackerID,         char[] sIcon,               bool bHead = false, 
        bool bPenetrated = false,   bool bRevenge = false,  bool bDominated = false,    int assisterID = 0)
    {
        // Creates and send custom death icon
        Event hEvent = CreateEvent("player_death");
        if (hEvent != null)
        {
            // Sets event properties
            hEvent.SetInt("userid", userID);
            hEvent.SetInt("attacker", attackerID);
            hEvent.SetInt("assister", assisterID);
            hEvent.SetString("weapon", sIcon);
            hEvent.SetBool("headshot", bHead);
            hEvent.SetBool("penetrated", bPenetrated);
            hEvent.SetBool("revenge", bRevenge);
            hEvent.SetBool("dominated", bDominated);

            // i = client index
            for (int i = 1; i <= MaxClients; i++)
            {
                // Send fake event
                if (PlayerEx.IsHuman(i, false)) hEvent.FireToClient(i);
            }
            
            // Close it
            hEvent.Cancel();
        }
    }
}