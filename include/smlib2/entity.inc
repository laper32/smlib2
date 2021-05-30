/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          entity.sp
 *  Description:   Entity related.
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

#if defined _smlib2_entity_included
    #endinput
#endif

#define _smlib2_entity_included


/**
 * A wrapper for object oriented programming of an entity.
 *
 * @note You can treat it as CBaseEntity*
 */
methodmap Entity __nullable__ {
    /**
     * Constructor of the entity object.
     *
     * @param entity            Entity index.
     *
     * @return                  Entity object.
     */
    public Entity(int entity) {
        return view_as<Entity>(entity);
    }

    /**
     * The index of the entity
     */
    property int Index {
        /**
         * Gets the index of the entity.
         *
         * @return              Entity index.
         */
        public get() {
            return view_as<int>(this);
        }
    }

    /**
     * Validation of the entity.
     */
    property bool Valid {
        /**
         * Gets whether the entity is valid.
         *
         * @return              True for the entity is valid, false otherwise.
         */
        public get() {
            return IsValidEntity(this.Index);
        }
    }

    /**
     * Whether or not an entity has a valid networkable edict.
     */
    property bool Networkable {
        /**
         * Gets whether the entity is networkable.
         *
         * @return              True if networkable, false if invalid or not networkable.
         */
        public get() {
            return IsEntNetworkable(this.Index);
        }
    }

    /**
     * 
     */
    public void Remove() {
        RemoveEntity(this.Index);
    }

    public bool SetParent(int parent) {
        SetVariantString("!activator");
        return AcceptEntityInput(this.Index, "SetParent", parent, this.Index, 0);
    }

    // You have been warning that: This is only used for the entity only.
    // If you have other purpose, use AcceptEntityInput() directly
    public bool AcceptInput(const char[] input, int activator=-1, int caller=-1, int outputid=0)
    {
        #if defined _sdktools_included
            return AcceptEntityInput(this.Index, input, activator, caller, outputid);
        #else
            PrintToServer("<sdktools> not included. this function will not work.");
            PrintToServer("Include <sdktools> to let this function works.")
            return 0;
        #endif
    }

    public int GetDataInt(int offset, int size=4) {
        return GetEntData(this.Index, offset, size);
    }

    public void SetDataInt(int offset, any value, int size=4, bool changeState=false) {
        SetEntData(this.Index, offset, value, size, changeState);
    }

    public float GetDataFloat(int offset) {
        return GetEntDataFloat(this.Index, offset);
    }

    public void SetDataFloat(int offset, float value, bool changeState=false) {
        SetEntDataFloat(this.Index, offset, value, changeState);
    }

    public int GetDataEnt(int offset) {
        return GetEntDataEnt2(this.Index, offset);
    }

    public void SetDataEnt(int offset, int other, bool changeState=false) {
        SetEntDataEnt2(this.Index, offset, other, changeState);
    }

    public void GetDataVector(int offset, float vec[3]) {
        GetEntDataVector(this.Index, offset, vec);
    }

    public void SetDataVector(int offset, const float vec[3], bool changeState=false) {
        SetEntDataVector(this.Index, offset, vec, changeState);
    }

    public int GetDataString(int offset, char[] buffer, int maxlen) {
        return GetEntDataString(this.Index, offset, buffer, maxlen);
    }

    public int SetDataString(int offset, const char[] buffer, int maxlen, bool changeState=false) {
        return SetEntDataString(this.Index, offset, buffer, maxlen, changeState);
    }

    public void GetDataIntArray(int offset, int[] array, int arraySize, int dataSize=4) {
        for (int i = 0; i < arraySize; i++) {
            array[i] = this.GetDataInt(offset + i*dataSize, dataSize);
        }
    }

    public void SetDataIntArray(int offset, const int[] array, int arraySize, int dataSize=4, bool changeState=false) {
        for (int i = 0; i < arraySize; i++) {
            this.SetDataInt(offset+i*dataSize, array[i], dataSize, changeState);
        }
    }

    public int GetDataMapInfo(const char[] prop, PropFieldType &type=view_as<PropFieldType>(0), int &num_bits=0, int &local_offset=0) {
        return FindDataMapInfo(this.Index, prop, type, num_bits, local_offset);
    }

    public int GetSendPropOffset(const char[] prop, bool actual=false) {
        return GetEntSendPropOffs(this.Index, prop, actual);
    }

    public bool hasProp(PropType type, const char[] prop) {
        return HasEntProp(this.Index, type, prop);
    }

    // I know, we have bool
    // But dont forget that bool=stdbool.h=
    // #define true     1
    // #define false    0
    // We treating them as int.
    public int GetPropInt(PropType type, const char[] prop, int size=4, int element=0) {
        return GetEntProp(this.Index, type, prop, size, element);
    }

    public void SetPropInt(PropType type, const char[] prop, any val, int size=4, int element=0) {
        SetEntProp(this.Index, type, prop, val, size, element);
    }

    public float GetPropFloat(PropType type, const char[] prop, int element=0) {
        return GetEntPropFloat(this.Index, type, prop, element);
    }

    public void SetPropFloat(PropType type, const char[] prop, float val, int element=0) {
        SetEntPropFloat(this.Index, type, prop, val, element);
    }

    public int GetPropEnt(PropType type, const char[] prop, int element=0) {
        return GetEntPropEnt(this.Index, type, prop, element);
    }

    public void SetPropEnt(PropType type, const char[] prop, int other, int element=0) {
        SetEntPropEnt(this.Index, type, prop, other, element);
    }

    public void GetPropVector(PropType type, const char[] prop, float vec[3], int element=0) {
        GetEntPropVector(this.Index, type, prop, vec, element);
    }

    public void SetPropVector(PropType type, const char[] prop, float vec[3], int element=0) {
        SetEntPropVector(this.Index, type, prop, vec, element);
    }

    public int GetPropString(PropType type, const char[] prop, char[] buffer, int maxlen, int element=0) {
        return GetEntPropString(this.Index, type, prop, buffer, maxlen, element);
    }

    public int SetPropString(PropType type, const char[] prop, const char[] buffer, int element=0) {
        return SetEntPropString(this.Index, type, prop, buffer, element);
    }

    public int GetPropArraySize(PropType type, const char[] prop) {
        return GetEntPropArraySize(this.Index, type, prop);
    }

    property Address Addr {
        public get() {
            return GetEntityAddress(this.Index);
        }
    }

    public bool GetClassname(char[] clsname, int maxlen) {
        return !!this.GetPropString(Prop_Data, "m_iClassname", clsname, maxlen);
    }

    public void Teleport(const float origin[3], const float angles[3], const float velocity[3]) {
        #if defined _sdktools_included
            TeleportEntity(this.Index, origin, angles, velocity);
        #else
            PrintToServer("<sdktools> not found, this function doesn't work.");
            PrintToServer("include <sdktools> for letting this function works.");
        #endif
    }

    public void GetVelocity(float vel[3]) {
        this.GetPropVector(Prop_Data, "m_vecVelocity", vel);
    }

    public void SetVelocity(float vel[3], bool apply=true, bool stack=true) {
        if (!apply) {
            this.GetVelocity(vel);
            return;
        }

        if (stack) {
            float speed[3];
            this.GetVelocity(speed);

            AddVectors(speed, vel, vel);
        }

        this.Teleport(NULL_VECTOR, NULL_VECTOR, vel);
    }

    // magnitude of the velocity
    property float Speed {
        public get() {
            float vel[3];
            this.GetVelocity(vel);

            return GetVectorLength(vel);
        }
    }

    public void GetAbsOrigin(float pos[3]) {
        this.GetPropVector(Prop_Data, "m_vecAbsOrigin", pos);
    }

    public void GetAbsAngles(float ang[3]) {
        this.GetPropVector(Prop_Data, "m_angAbsRotation", ang);
    }

    public void GetMaxs(float maxs[3]) {
        this.GetPropVector(Prop_Data, "m_vecMaxs", maxs);
    }

    public void GetMins(float mins[3]) {
        this.GetPropVector(Prop_Data, "m_vecMins", mins);
    }

    property int m_iHealth {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iHealth");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iHealth", val);
        }
    }

    property int m_iMaxHealth {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iMaxHealth");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iMaxHealth", val);
        }
    }

    property int m_hOwnerEntity {
        public get() {
            return this.GetPropEnt(Prop_Data, "m_hOwnerEntity");
        }
        public set(int owner) {
            this.SetPropEnt(Prop_Data, "m_hOwnerEntity", owner);
        }
    }

    property int m_pParent {
        public get() {
            return this.GetPropEnt(Prop_Data, "m_pParent");
        }
        public set(int parent) {
            this.SetPropEnt(Prop_Data, "m_pParent", parent);
        }
    }

    property int m_hRagdoll {
        public get() {
            return this.GetPropEnt(Prop_Data, "m_hRagdoll");
        }
    }

    property int m_pActivator {
        public get() {
            return this.GetPropEnt(Prop_Data, "m_pActivator");
        }
    }

    property int m_hMyWeapons {
        public get() {
            return this.GetPropArraySize(Prop_Data, "m_hMyWeapons");
        }
    }

    public int GetWeapon(int pos) {
        return this.GetPropEnt(Prop_Data, "m_hMyWeapons", pos);
    }

    property float m_flLaggedMovementValue {
        public get() {
            return this.GetPropFloat(Prop_Data, "m_flLaggedMovementValue");
        }
        public set(float val) {
            this.SetPropFloat(Prop_Data, "m_flLaggedMovementValue", val);
        }
    }

    property int m_ArmorValue {
        public get() {
            return this.GetPropInt(Prop_Data, "m_ArmorValue");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_ArmorValue", val);
        }
    }

    property int m_iTeamNum {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iTeamNum");
        }
    }
    
    property bool m_bHasNightVision {
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasNightVision"));
        }
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasNightVision", val);
        }
    }

    property bool m_bNightVisionOn {
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bNightVisionOn"));
        }
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bNightVisionOn", val);
        }
    }

    property bool m_bHasDefuser {
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasDefuser"));
        }
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasDefuser", val);
        }
    }

    property bool m_bHasHelmet {
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasHelmet"));
        }
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasHelmet", val);
        }
    }
    
    property bool m_bHasHeavyArmor {
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasHeavyArmor"));
        }
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasHeavyArmor", val);
        }
    }
    
    property int m_hActiveWeapon {
        public get() {
            return this.GetPropInt(Prop_Send, "m_hActiveWeapon");
        }
    }

    property int m_iAddonBits {
        public get() {
            return this.GetPropInt(Prop_Send, "m_iAddonBits");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iAddonBits", val);
        }
    }

    property int m_iObserverMode {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iObserverMode");
        }
    }

    property int m_hObserverTarget {
        public get() {
            return this.GetPropInt(Prop_Data, "m_hObserverTarget");
        }
    }
    
    property int m_LastHitGroup {
        public get() {
            return this.GetPropInt(Prop_Send, "m_LastHitGroup");
        }
    }

    property int m_iFrags {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iFrags");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iFrags", val);
        }
    }

    property int m_iDeaths {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iDeaths");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iDeaths", val);
        }
    }

    property float m_flGravity {
        public get() {
            this.GetPropFloat(Prop_Data, "m_flGravity");
        }
        public set(float val) {
            this.SetPropFloat(Prop_Data, "m_flGravity", val);
        }
    }

    property int m_iAccount {
        public get() {
            return this.GetPropInt(Prop_Data, "m_iAccount");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iAccount", val);
        }
    }

    public void SetArmsModel(const char[] path) {
        this.SetPropString(Prop_Send, "m_szArmsModel", path);
    }

    property float m_flNextAttack {
        public get() {
            return this.GetPropFloat(Prop_Send, "m_flNextAttack");
        }
        public set(float val) {
            this.SetPropFloat(Prop_Send, "m_flNextAttack", val);
        }
    }
    
    property int m_iFOV {
        public get() {
            return this.GetPropInt(Prop_Send, "m_iFOV");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iFOV", val);
        }
    }

    property int m_iDefaultFOV {
        public get() {
            return this.GetPropInt(Prop_Send, "m_iDefaultFOV");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iDefaultFOV", val);
        }
    }
    
    property int m_nBody {
        public get() {
            return this.GetPropInt(Prop_Send, "m_nBody");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nBody", val);
        }
    }

    property int m_nSkin {
        public get() {
            return this.GetPropInt(Prop_Send, "m_nSkin");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nSkin", val);
        }
    }

    property int m_fEffects {
        public get() {
            return this.GetPropInt(Prop_Send, "m_fEffects");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_fEffects", val);
        }
    }

    property int m_nModelIndex {
        public get() {
            return this.GetPropInt(Prop_Send, "m_nModelIndex");
        }
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nModelIndex", val);
        }
    }

    property int m_CollisionGroup {
        public get() {
            return this.GetPropInt(Prop_Data, "m_CollisionGroup");
        }
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_CollisionGroup", val);
        }
    }
}