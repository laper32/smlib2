/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          particle.sp
 *  Description:   Particle.
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

#if defined _smlib2_particle_included
    #endinput
#endif

#define _smlib2_particle_included

methodmap Effect {
    /**
     * @brief Searches for the index of a given string in a dispatch table.
     *
     * @param sEffect           The effect name.
     *
     * @return                  The string index.
     */
    public static int GetIndex(char[] sEffect) {

        // Initialize the table index
        static int table = INVALID_STRING_TABLE;

        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("EffectDispatch");
        }

        // Searches for the index of a given string in a string table
        int item = FindStringIndex(table, sEffect);

        // Validate item
        if (item != INVALID_STRING_INDEX) {
            return item;
        }

        // Return on the unsuccess
        return 0;
    }

    /**
     * @brief Gets a string count in a dispatch table.
     *
     * @return                  The table size.    
     */
    public static int GetNameCount(/*void*/) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("EffectDispatch");
        }

        // Returns the count of strings that exist in a given table
        return GetStringTableNumStrings(table);
    }

    /**
     * @brief Gets a string of a given index in a dispatch table.
     *
     * @param iIndex            The string index.
     * @param sEffect           The string to return effect in.
     * @param iMaxLen           The lenght of string.
     */
    public static void GetEffectName(int iIndex, char[] sEffect, int iMaxLen) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("EffectDispatch");
        }

        // Gets the string at a given index
        ReadStringTable(table, iIndex, sEffect, iMaxLen);
    }

}

methodmap Particle < Effect {
    /**
     * @brief Searches for the index of a given string in an effect table.
     *
     * @param sEffect           The effect name.
     *
     * @return                  The string index.
     */
    public static int GetEffectIndex(char[] sEffect) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;

        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("ParticleEffectNames");
        }

        // Searches for the index of a given string in a string table
        int item = FindStringIndex(table, sEffect);

        // Validate item
        if (item != INVALID_STRING_INDEX) {
            return item;
        }

        // Return on the unsuccess
        return 0;
    }

    /**
     * @brief Precache the particle in the effect table.
     *
     * @param sEffect           The effect name.
     */
    public static void PrecacheEffect(char[] sEffect) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("ParticleEffectNames");
        }
        
        // Precache particle
        bool bSave = LockStringTables(false);
        AddToStringTable(table, sEffect);
        LockStringTables(bSave);
    }

    /**
     * @brief Gets a string of a given index in an effect table.
     *
     * @param iIndex            The string index.
     * @param sEffect           The string to return effect in.
     * @param iMaxLen           The lenght of string.
     */
    public static void GetParticleEffectName(int iIndex, char[] sEffect, int iMaxLen) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("ParticleEffectNames");
        }
        
        // Gets the string at a given index
        ReadStringTable(table, iIndex, sEffect, iMaxLen);
    }

    /**
     * @brief Gets a string count in an effect table.
     *
     * @return                  The table size.    
     */
    public static int GetEffectCount() {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("ParticleEffectNames");
        }
        
        // Returns the count of strings that exist in a given table
        return GetStringTableNumStrings(table);
    }

    /**
     * Precache the particle in the effect table. (for client)
     *
     * Note: This is considered as a more general method, for all Source Engine games.
     *
     * @param client            (Optional) The client index.
     * @param sEffect           The effect name.
     */
    public static void Precache(int client = 0, char[] sEffect) {
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;
        
        // Validate table
        if (table == INVALID_STRING_TABLE) {
            // Searches for a string table
            table = FindStringTable("ExtraParticleFilesTable");
        }

        // Validate server
        if (!client) {
            // Precache particle
            bool bSave = LockStringTables(false);
            AddToStringTable(table, sEffect);
            LockStringTables(bSave);
        } else {
            // i = string index
            int iCount = GetStringTableNumStrings(table);
            for (int i = 0; i < iCount; i++) {
                char iD[SMALL_LINE_LENGTH];
                IntToString(client, iD, sizeof(iD));
                SetStringTableData(table, i, iD, sizeof(iD));
            }
        }
    }
}