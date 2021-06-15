/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          engine.sp
 *  Description:   Engine related
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

#if defined _smlib2_engine_included
    #endinput
#endif

#define _smlib2_engine_included

methodmap Engine {
    /**
     * @brief Returns an offset value from a given config.
     *
     * @param gameConf          The game config handle.
     * @param iOffset           An offset, or -1 on failure.
     * @param sKey              Key to retrieve from the offset section.
     */
    public static void InitGameConfOffset(GameData gameConf, int &iOffset, char[] sKey) {
    if ((iOffset = gameConf.GetOffset(sKey)) == -1) {
        SetFailState("Engine.InitGameConfOffset: Failed to get offset: \"%s\".", sKey);
        }
    }

    /**
     * @brief Returns an address value from a given config.
     *
     * @param gameConf          The game config handle.
     * @param pAddress          An address, or null on failure.
     * @param sKey              Key to retrieve from the address section.
     */
    public static void InitGameConfAddress(GameData gameConf, Address &pAddress, char[] sKey) {
        if ((pAddress = gameConf.GetAddress(sKey)) == Address_Null) {
            SetFailState("Engine.InitGameConfAddress: Failed to get address: \"%s\".", sKey);
        }
    }

    /**
     * @brief Returns the value of a key from a given config.
     *
     * @param gameConf          The game config handle.
     * @param sKey              Key to retrieve from the key section.
     * @param sIdentifier       The string to return identifier in.
     * @param iMaxLen           The lenght of string.
     */
    public static void InitGameConfKey(GameData gameConf, char[] sKey, char[] sIdentifier, int iMaxLen) {
        if (!gameConf.GetKeyValue(sKey, sIdentifier, iMaxLen)) {
            SetFailState("Engine.InitGameConfKey: Failed to get key: \"%s\".", sKey);
        }
    }
    
    /**
     * @brief Given an entity classname, finds a networkable send property offset.
     *
     * @param iOffset           An offset, or -1 on failure.
     * @param sClass            The entity classname.
     * @param sProp             The property name.
     */
    public static void InitSendPropOffset(int &iOffset, char[] sClass, char[] sProp) {
        if ((iOffset = FindSendPropInfo(sClass, sProp)) < 1) {
            SetFailState("Engine.InitSendPropOffset: Failed to find send prop: \"%s\"", sProp);
        }
    }

    /**
     * @brief Given an entity index, finds a networkable data property offset.
     *
     * @param iOffset           An offset, or -1 on failure.
     * @param entity            The entity index.
     * @param sProp             The property name.
     */
    public static void InitDataPropOffset(int &iOffset, int entity, char[] sProp) {
        if ((iOffset = FindDataMapInfo(entity, sProp)) < 1) {
            SetFailState("Engine.InitDataPropOffset: Failed to find data prop: \"%s\"", sProp);
        }
    }
    /**
     * @brief This is the primary exported function by a dll, referenced by name via dynamic binding
     *        that exposes an opqaue function pointer to the interface.
     *
     * @param gameConf          The game config handle.
     * @param sConfigFile       Config file what you used for retrieving gamedata.
     * @param sKey              Key to retrieve from the key section.
     * @param pAddress          (Optional) The optional interface address.
     * 
     * @return Address pointer
     */
    public static Address CreateEngineInterface(GameData gameConf, const char[] sConfigFile, char[] sKey, Address pAddress = Address_Null) {
        // Initialize intercace call
        Handle hInterface = null;
        if (hInterface == null)  {
            // Starts the preparation of an SDK call
            StartPrepSDKCall(SDKCall_Static);
            PrepSDKCall_SetFromConf(gameConf, SDKConf_Signature, "CreateInterface");

            // Adds a parameter to the calling convention. This should be called in normal ascending order
            PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer);
            PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain, VDECODE_FLAG_ALLOWNULL);
            PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain);

            // Validate call
            if ((hInterface = EndPrepSDKCall()) == null) {
                SetFailState("Engine.CreateEngineInterface: Failed to load SDK call \"CreateInterface\". Update signature in the config: \"%s\".", sConfigFile);
                return Address_Null;
            }
        }

        // Gets the value of a key from a config
        char sInterface[NORMAL_LINE_LENGTH];
        Engine.InitGameConfKey(gameConf, sKey, sInterface, sizeof(sInterface));

        // Gets the address of a given interface and key
        Address pInterface = SDKCall(hInterface, sInterface, pAddress);
        if (pInterface == Address_Null) {
            SetFailState("Engine.CreateEngineInterface: Failed to get pointer to interface %s(\"%s\")", sKey, sInterface);
            return Address_Null;
        }

        // Return on the success
        return pInterface;
    }
}