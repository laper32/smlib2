/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          entity.sp
 *  Description:   Entity related.
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

#if defined _smlib2_entity_included
    #endinput
#endif

#define _smlib2_entity_included

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
    * Marks an entity for deletion.
    *
    * @error                    Invalid entity index.
    */
    public void Remove() {
        RemoveEntity(this.Index);
    }

    /**
     * Sets the parent of the entity
     *
     * @param parent            Parent entity object.
     *
     * @return                  True on succes, false otherwise.
     */
    public bool SetParent(int parent) {
        SetVariantString("!activator");
        return AcceptEntityInput(this.Index, "SetParent", parent, this.Index, 0);
    }

    /**
     * Invokes a named input method on an entity.
     *
     * After completion (successful or not), the current global variant is re-initialized.
     *
     * @note You have been warning that:
     * - This is only used for this entity object what we are manipulating.
     * - This is only a warpper for easily handling the input.
     * - If you have other purposeing of handing the entity, you should use AcceptEntityInput() directly.
     *
     * @param input             Input action.
     * @param activator         Entity index which initiated the sequence of actions (-1 for a NULL entity).
     * @param caller            Entity index from which this event is sent (-1 for a NULL entity).
     * @param outputid          Unknown.
     * @return                  True if successful otherwise false.
     * @error                   Invalid entity index or no mod support.
     */
    public bool AcceptInput(const char[] input, int activator=-1, int caller=-1, int outputid=0)
    {
        #if defined _sdktools_included
            return AcceptEntityInput(this.Index, input, activator, caller, outputid);
        #else
            #warning '<sdktools> is not included, this function will not work'
            return false;
        #endif
    }

    /**
     * @section Entity offset functions
     *
     * Offsets should be specified in byte distance from the CBaseEntity
     * structure, not short (double byte) or integer (four byte) multiples.
     * It is somewhat common practice to use offsets aligned to their final
     * type, and thus make sure you are not falling to this error in SourceMod.
     * For example, if your "integer-aligned" offset was 119, your byte-aligned
     * offset is 119*4, or 476.
     * 
     * Specifying incorrect offsets or the incorrect data type for an offset
     * can have fatal consequences.  If you are hardcoding offsets, and the
     * layout of CBaseEntity does not match, you can easily crash the server.
     *
     * The reasonable bounds for offsets is greater than or equal to 0 and
     * below 32768.  Offsets out of these bounds will throw an error.  However,
     * this does not represent any real range, it is simply a sanity check for
     * illegal values.  Any range outside of the CBaseEntity structure's private
     * size will cause undefined behavior or even crash.
     */

    /**
     * Peeks into an entity's object data and retrieves the integer value at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @param size              Number of bytes to read (valid values are 1, 2, or 4).
     * @return                  Value at the given memory location.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public int GetDataInt(int offset, int size=4) {
        return GetEntData(this.Index, offset, size);
    }

    /**
     * Peeks into an entity's object data and sets the integer value at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @param value             Value to set.
     * @param size              Number of bytes to write (valid values are 1, 2, or 4).
     * @param changeState       If true, change will be sent over the network.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetDataInt(int offset, any value, int size=4, bool changeState=false) {
        SetEntData(this.Index, offset, value, size, changeState);
    }

    /**
     * Peeks into an entity's object data and retrieves the float value at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @return                  Value at the given memory location.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public float GetDataFloat(int offset) {
        return GetEntDataFloat(this.Index, offset);
    }

    /**
     * Peeks into an entity's object data and sets the float value at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @param value             Value to set.
     * @param changeState       If true, change will be sent over the network.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetDataFloat(int offset, float value, bool changeState=false) {
        SetEntDataFloat(this.Index, offset, value, changeState);
    }
    /**
     * Peeks into an entity's object data and retrieves the entity index
     * at the given offset.
     *
     * Note: This will only work on offsets that are stored as "entity
     * handles" (which usually looks like m_h* in properties).  These
     * are not SourceMod Handles, but internal Source structures.
     *
     * @param offset            Offset to use.
     * @return                  Entity index at the given location.  If there is no entity,
     *                          or the stored entity is invalid, then -1 is returned.
     * @error                   Invalid input entity, or offset out of reasonable bounds.
     */
    public int GetDataEnt(int offset) {
        return GetEntDataEnt2(this.Index, offset);
    }
    
    /**
     * Peeks into an entity's object data and sets the entity index at the
     * given offset.
     *
     * Note: This will only work on offsets that are stored as "entity
     * handles" (which usually looks like m_h* in properties).  These
     * are not SourceMod Handles, but internal Source structures.
     *
     * @param offset            Offset to use.
     * @param other             Entity index to set, or -1 to clear.
     * @param changeState       If true, change will be sent over the network.
     * @error                   Invalid input entity, or offset out of reasonable bounds.
     */
    public void SetDataEnt(int offset, int other, bool changeState=false) {
        SetEntDataEnt2(this.Index, offset, other, changeState);
    }

    /**
     * Peeks into an entity's object data and retrieves the vector at the
     * given offset.
     * @note Both a Vector and a QAngle are three floats.  This is a
     *       convenience function and will work with both types.
     *
     * @param offset            Offset to use.
     * @param vec               Vector buffer to store data in.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void GetDataVector(int offset, float vec[3]) {
        GetEntDataVector(this.Index, offset, vec);
    }

    /**
     * Peeks into an entity's object data and sets the vector at the given
     * offset.
     * @note Both a Vector and a QAngle are three floats.  This is a
     *       convenience function and will work with both types.
     *
     * @param offset            Offset to use.
     * @param vec               Vector to set.
     * @param changeState       If true, change will be sent over the network.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetDataVector(int offset, const float vec[3], bool changeState=false) {
        SetEntDataVector(this.Index, offset, vec, changeState);
    }

    /**
     * Peeks into an entity's object data and retrieves the string at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @param buffer            Destination string buffer.
     * @param maxlen            Maximum length of output string buffer.
     * @return                  Number of non-null bytes written.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public int GetDataString(int offset, char[] buffer, int maxlen) {
        return GetEntDataString(this.Index, offset, buffer, maxlen);
    }

    /**
     * Peeks into an entity's object data and sets the string at
     * the given offset.
     *
     * @param offset            Offset to use.
     * @param buffer            String to set.
     * @param maxlen            Maximum length of bytes to write.
     * @param changeState       If true, change will be sent over the network.
     * @return                  Number of non-null bytes written.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public int SetDataString(int offset, const char[] buffer, int maxlen, bool changeState=false) {
        return SetEntDataString(this.Index, offset, buffer, maxlen, changeState);
    }

    /**
     * @endsection
     */

    /**
     * Copies an array of cells from an entity at a given offset.
     *
     * @param offset            Offset to use.
     * @param array             Array to read into.
     * @param arraySize         Number of values to read.
     * @param dataSize          Size of each value in bytes (1, 2, or 4).
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void GetDataIntArray(int offset, int[] array, int arraySize, int dataSize=4) {
        for (int i = 0; i < arraySize; i++) {
            array[i] = this.GetDataInt(offset + i*dataSize, dataSize);
        }
    }

    /**
     * Copies an array of cells to an entity at a given offset.
     *
     * @param offset            Offset to use.
     * @param array             Array of values to copy.
     * @param arraySize         Number of values to copy.
     * @param dataSize          Size of each value in bytes (1, 2, or 4).
     * @param changeState       True to set the network state as changed; false otherwise.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetDataIntArray(int offset, const int[] array, int arraySize, int dataSize=4, bool changeState=false) {
        for (int i = 0; i < arraySize; i++) {
            this.SetDataInt(offset+i*dataSize, array[i], dataSize, changeState);
        }
    }

    /**
     * Given an entity, finds a nested datamap property offset.
     * This information is cached for future calls.
     *
     * @param prop              Property name.
     * @param type              Optional parameter to store the type.
     * @param num_bits          Optional parameter to store the number of bits the field
     *                          uses.  The bit count will either be 1 (for boolean) or
     *                          divisible by 8 (including 0 if unknown).
     * @param local_offset      Optional parameter to store the local offset, as
     *                          FindDataMapOffs() would return.
     * @return                  An offset, or -1 on failure.
     */
    public int GetDataMapInfo(const char[] prop, PropFieldType &type=view_as<PropFieldType>(0), int &num_bits=0, int &local_offset=0) {
        return FindDataMapInfo(this.Index, prop, type, num_bits, local_offset);
    }

    /**
     * Wrapper function for finding a send property for a particular entity.
     *
     * @param prop              Property name.
     * @param actual            Defaults to false for backwards compatibility.
     *                          If true, the newer FindSendPropInfo() function
     *                          is used instead.
     * @return                  An offset, or -1 on failure.
     */
    public int GetSendPropOffset(const char[] prop, bool actual=false) {
        return GetEntSendPropOffs(this.Index, prop, actual);
    }

    /**
     * Checks if an entity property exists on an entity.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @return                  Whether the property exists on the entity.
     * @error                   Invalid entity.
     */
    public bool HasProp(PropType type, const char[] prop) {
        return HasEntProp(this.Index, type, prop);
    }

    /**
     * Retrieves an integer value from an entity's property.
     *
     * This function is considered safer and more robust over GetEntData,
     * because it performs strict offset checking and typing rules.
     *
     * Note: Yes, I know, we need to consider bool.
     * But you need to remember that: Accoring to <stdbool.h>, the bool is the fact of:
     * - false: 0
     * - true: 1
     * So that we cast bool as int.
     * But this means that once you need to get something what requires bool, you must static_cast (What sourcemod called it
     * as view_as) to boolean.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param size              Number of bytes to write (valid values are 1, 2, or 4).
     *                          This value is auto-detected, and the size parameter is
     *                          only used as a fallback in case detection fails.
     * @param element           Element # (starting from 0) if property is an array.
     * @return                  Value at the given property offset.
     * @error                   Invalid entity or property not found.
    */
    public int GetPropInt(PropType type, const char[] prop, int size=4, int element=0) {
        return GetEntProp(this.Index, type, prop, size, element);
    }

    /**
     * Sets an integer value in an entity's property.
     *
     * This function is considered safer and more robust over SetEntData,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param value             Value to set.
     * @param size              Number of bytes to write (valid values are 1, 2, or 4).
     *                          This value is auto-detected, and the size parameter is
     *                          only used as a fallback in case detection fails.
     * @param element           Element # (starting from 0) if property is an array.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetPropInt(PropType type, const char[] prop, any val, int size=4, int element=0) {
        SetEntProp(this.Index, type, prop, val, size, element);
    }

    /**
     * Retrieves a float value from an entity's property.
     *
     * This function is considered safer and more robust over GetEntDataFloat,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param element           Element # (starting from 0) if property is an array.
     * @return                  Value at the given property offset.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public float GetPropFloat(PropType type, const char[] prop, int element=0) {
        return GetEntPropFloat(this.Index, type, prop, element);
    }

    /**
     * Sets a float value in an entity's property.
     *
     * This function is considered safer and more robust over SetEntDataFloat,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param value             Value to set.
     * @param element           Element # (starting from 0) if property is an array.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetPropFloat(PropType type, const char[] prop, float val, int element=0) {
        SetEntPropFloat(this.Index, type, prop, val, element);
    }

    /**
     * Retrieves an entity index from an entity's property.
     *
     * This function is considered safer and more robust over GetEntDataEnt*,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param element           Element # (starting from 0) if property is an array.
     * @return                  Entity index at the given property.
     *                          If there is no entity, or the entity is not valid,
     *                          then -1 is returned.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public int GetPropEnt(PropType type, const char[] prop, int element=0) {
        return GetEntPropEnt(this.Index, type, prop, element);
    }

    /**
     * Sets an entity index in an entity's property.
     *
     * This function is considered safer and more robust over SetEntDataEnt*,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param other             Entity index to set, or -1 to unset.
     * @param element           Element # (starting from 0) if property is an array.
     * @error                   Invalid entity or offset out of reasonable bounds.
     */
    public void SetPropEnt(PropType type, const char[] prop, int other, int element=0) {
        SetEntPropEnt(this.Index, type, prop, other, element);
    }

    /**
     * Retrieves a vector of floats from an entity, given a named network property.
     *
     * This function is considered safer and more robust over GetEntDataVector,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param vec               Vector buffer to store data in.
     * @param element           Element # (starting from 0) if property is an array.
     * @error                   Invalid entity, property not found, or property not
     *                          actually a vector data type.
     */
    public void GetPropVector(PropType type, const char[] prop, float vec[3], int element=0) {
        GetEntPropVector(this.Index, type, prop, vec, element);
    }

    /**
     * Sets a vector of floats in an entity, given a named network property.
     *
     * This function is considered safer and more robust over SetEntDataVector,
     * because it performs strict offset checking and typing rules.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @param vec               Vector to set.
     * @param element           Element # (starting from 0) if property is an array.
     * @error                   Invalid entity, property not found, or property not
     *                          actually a vector data type.
     */
    public void SetPropVector(PropType type, const char[] prop, float vec[3], int element=0) {
        SetEntPropVector(this.Index, type, prop, vec, element);
    }

    /**
     * Gets a network property as a string.
     *
     * @param type              Property type.
     * @param prop              Property to use.
     * @param buffer            Destination string buffer.
     * @param maxlen            Maximum length of output string buffer.
     * @param element           Element # (starting from 0) if property is an array.
     * @return                  Number of non-null bytes written.
     * @error                   Invalid entity, offset out of reasonable bounds, or property is not a valid string.
     */
    public int GetPropString(PropType type, const char[] prop, char[] buffer, int maxlen, int element=0) {
        return GetEntPropString(this.Index, type, prop, buffer, maxlen, element);
    }

    /**
     * Sets a network property as a string.
     *
     * @param type              Property type.
     * @param prop              Property to use.
     * @param buffer            String to set.
     * @param element           Element # (starting from 0) if property is an array.
     * @return                  Number of non-null bytes written.
     * @error                   Invalid entity, offset out of reasonable bounds, or property is not a valid string.
     */
    public int SetPropString(PropType type, const char[] prop, const char[] buffer, int element=0) {
        return SetEntPropString(this.Index, type, prop, buffer, element);
    }

    /**
     * Retrieves the count of values that an entity property's array can store.
     *
     * @param type              Property type.
     * @param prop              Property name.
     * @return                  Size of array (in elements) or 1 if property is not an array.
     * @error                   Invalid entity or property not found.
     */
    public int GetPropArraySize(PropType type, const char[] prop) {
        return GetEntPropArraySize(this.Index, type, prop);
    }

    /**
     * Memory address.
     * The another name what you should be fimilar with: Pointer.
     */
    property Address Addr {
        /**
         * Gets the memory address of an entity.
         *
         * @return              Address of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return GetEntityAddress(this.Index);
        }
    }

    /**
     * Retrieves the classname of an entity.
     * This is like GetEdictClassname(), except it works for ALL
     * entities, not just edicts.
     *
     * @param clsname           Buffer to store the classname.
     * @param maxlength         Maximum length of the buffer.
     * @return                  True on success, false if there is no classname set.
     */
    public bool GetClassname(char[] clsname, int maxlen) {
        return !!this.GetPropString(Prop_Data, "m_iClassname", clsname, maxlen);
    }

    /**
     * Teleports an entity.
     *
     * WARNING: You must include sdktools for letting this function works. Otherwise it will not WORK!
     *
     * @param origin            New origin, or NULL_VECTOR for no change.
     * @param angles            New angles, or NULL_VECTOR for no change.
     * @param velocity          New velocity, or NULL_VECTOR for no change.
     * @error                   Invalid entity or client not in game, or lack of mod support.
     */
    public void Teleport(const float origin[3], const float angles[3], const float velocity[3]) {
        #if defined _sdktools_included
            TeleportEntity(this.Index, origin, angles, velocity);
        #else
            PrintToServer("<sdktools> not found, this function doesn't work.");
            PrintToServer("include <sdktools> for letting this function works.");
        #endif
    }

    /**
     * From this part begins, you have been warning that:
     * 
     * 1. These functions, and properties below, are imported from tools.inc.
     * 2. These functions, and properties below, are only based on projects what I have
     * used, or problems what I've met. This means that: Not everything will be covered.
     * 3. These functions, and properties below, are only tested in games what I have been
     * instructed in readme.md, and you should read it already.
     * 4. If you have found something that can make an improvement, or modify, please make 
     * your own PR, or send message to me, to let me know.
     * 
     * Once you are using these functions and properties below, means that you have already
     * read the instructions, and already known that these functions and properties may cause
     * some unexpected circumstances in your own projects.
     */

    /**
     * Gets the velocity of the entity.
     *
     * @param vel               Velocity buffer.
     */
    public void GetVelocity(float vel[3]) {
        this.GetPropVector(Prop_Data, "m_vecVelocity", vel);
    }

    /**
     * Sets the velocity of the entity.
     *
     * @param vel               Velocity input
     * @param apply             True to get velocity, false to set
     * @param stack             If modifying velocity, then true will stack new velocity onto the entity of the
     *                          current velocity, false will reset it.
     */
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

    /**
     * Magnitude of the velocity, what we call it as speed.
     */
    property float Speed {
        /**
         * Gets the speed of an entity.
         *
         * @return              Speed of the entity.
         * @error               Invalid entity.
         */
        public get() {
            float vel[3];
            this.GetVelocity(vel);

            return GetVectorLength(vel);
        }
    }

    /**
     * Gets the absolute origin of the entity.
     *
     * @param vel               Absolute origin buffer.
     */
    public void GetAbsOrigin(float pos[3]) {
        this.GetPropVector(Prop_Data, "m_vecAbsOrigin", pos);
    }

    /**
     * Gets the absolute angle rotation of the entity.
     *
     * @param vel               Absolute angle rotation buffer.
     */
    public void GetAbsAngles(float ang[3]) {
        this.GetPropVector(Prop_Data, "m_angAbsRotation", ang);
    }

    /**
     * Gets the max size of the entity.
     *
     * @param vel               Maxs buffer.
     */
    public void GetMaxs(float maxs[3]) {
        this.GetPropVector(Prop_Data, "m_vecMaxs", maxs);
    }

    /**
     * Gets the min size of the entity.
     *
     * @param vel               Mins buffer.
     */
    public void GetMins(float mins[3]) {
        this.GetPropVector(Prop_Data, "m_vecMins", mins);
    }

    /**
     * CBaseEntity::m_iHealth
     */
    property int m_iHealth {
        /**
         * Gets the health of an entity.
         *
         * @return              Health of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iHealth");
        }

        /**
         * Sets the health of an entity.
         *
         * @param val           Value to modify.
         * 
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iHealth", val);
        }
    }

    /**
     * CBaseEntity::m_iMaxHealth
     */
    property int m_iMaxHealth {
        /**
         * Gets the health of an entity.
         *
         * @return              Max health of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iMaxHealth");
        }

        /**
         * Sets the max health of an entity.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iMaxHealth", val);
        }
    }

    /**
     * CBaseEntity::m_hOwnerEntity
     */
    property int m_hOwnerEntity {
        /**
         * Gets the owner of an entity.
         *
         * @return              The owner of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropEnt(Prop_Data, "m_hOwnerEntity");
        }

        /**
         * Sets the owner of an entity.
         *
         * @param               Owner entity index.
         *
         * @error               Invalid entity.
         */
        public set(int owner) {
            this.SetPropEnt(Prop_Data, "m_hOwnerEntity", owner);
        }
    }

    /**
     * CBaseEntity::m_pParent
     */
    property int m_pParent {
        /**
         * Gets the parent of an entity.
         *
         * @return              Parent of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropEnt(Prop_Data, "m_pParent");
        }

        /**
         * Sets the parent of an entity.
         *
         * @param parent        Parent entity index.
         *
         * @error               Invalid entity.
         */
        public set(int parent) {
            this.SetPropEnt(Prop_Data, "m_pParent", parent);
        }
    }

    /**
     * CBaseEntity::m_hRagdoll
     */
    property int m_hRagdoll {
        /**
         * Gets the ragdoll of an entity.
         *
         * @return              Max health of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropEnt(Prop_Data, "m_hRagdoll");
        }
    }

    /**
     * CBaseEntity::m_pActivator
     */
    property int m_pActivator {
        /**
         * Gets the activator of an entity.
         *
         * @return              The activator of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropEnt(Prop_Data, "m_pActivator");
        }
    }
    
    /**
     * CBaseEntity::m_hMyWeapons
     */
    property int m_hMyWeapons {
        /**
         * Gets the weapons count of an entity.
         *
         * @return              The weapons count of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropArraySize(Prop_Data, "m_hMyWeapons");
        }
    }

    /**
     * Get the weapon at the specific position.
     *
     * @param pos               The position what we want to get.
     *
     * @return                  The weapon index.
     */
    public int GetWeapon(int pos) {
        return this.GetPropEnt(Prop_Data, "m_hMyWeapons", pos);
    }

    /**
     * CBaseEntity::m_flLaggedMovementValue
     */
    property float m_flLaggedMovementValue {
        /**
         * Gets the LMV of an entity.
         *
         * @return              The LMV of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropFloat(Prop_Data, "m_flLaggedMovementValue");
        }

        /**
         * Sets the LMV of an entity.
         *
         * @param val           The LMV value.
         *
         * @error               Invalid entity.
         */
        public set(float val) {
            this.SetPropFloat(Prop_Data, "m_flLaggedMovementValue", val);
        }
    }

    /**
     * CBaseEntity::m_ArmorValue
     */
    property int m_ArmorValue {
        /**
         * Gets the armor value of an entity.
         *
         * @return              The armor value of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_ArmorValue");
        }

        /**
         * Sets the armor value of an entity.
         *
         * @param val           Value to modify.
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_ArmorValue", val);
        }
    }

    /**
     * CBaseEntity::m_iTeamNum
     * 
     * WARNING: You need to implement setter by your own. This property only provides getter.
     */
    property int m_iTeamNum {
        /**
         * Gets the team of an entity.
         *
         * @return              The team of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iTeamNum");
        }
    }
    
    /**
     * CBaseEntity::m_bHasNightVision
     */
    property bool m_bHasNightVision {
        /**
         * Gets the whether has night vision of an entity.
         *
         * @return              True if has the night vision, false otherwise.
         * @error               Invalid entity.
         */
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasNightVision"));
        }

        /**
         * Sets whether could have the night vision.
         *
         * @param val           Value to set.
         *
         * @error               Invalid entity.
         */
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasNightVision", val);
        }
    }

    /**
     * CBaseEntity::m_bNightVision
     */
    property bool m_bNightVisionOn {
        /**
         * Gets whether the night vision has enabled.
         *
         * @return              The night vision enable status of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bNightVisionOn"));
        }

        /**
         * Sets the night vision enable status of the entity.
         *
         * @param val           The value to modify.
         *
         * @error               Invalid entity.
         */
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bNightVisionOn", val);
        }
    }

    /**
     * CBaseEntity::m_bHasDefuser
     */
    property bool m_bHasDefuser {
        /**
         * Gets whether owns defuser.
         *
         * @return              True if owns defuser, false otherwise.
         * @error               Invalid entity.
         */
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasDefuser"));
        }

        /**
         * Sets the defuser owning status.
         *
         * @param val           Value to modify. 
         *
         * @error               Invalid entity.
         */
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasDefuser", val);
        }
    }

    /**
     * CBaseEntity::m_bHasHelmet
     */
    property bool m_bHasHelmet {
        /**
         * Gets whether owns helmet.
         *
         * @return              True if owns helmet, false otherwise.
         * @error               Invalid entity.
         */
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasHelmet"));
        }
        
        /**
         * Sets whether own defuser.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasHelmet", val);
        }
    }
    
    /**
     * CBaseEntity::m_bHasHeavyArmor
     */
    property bool m_bHasHeavyArmor {
        /**
         * Gets whether has heavy armor.
         *
         * @return              True if owns heavy armor, false otherwise.
         * @error               Invalid entity.
         */
        public get() {
            return view_as<bool>(this.GetPropInt(Prop_Send, "m_bHasHeavyArmor"));
        }

        /**
         * Sets the ownership of the heavy armor.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(bool val) {
            this.SetPropInt(Prop_Send, "m_bHasHeavyArmor", val);
        }
    }
    
    /**
     * CBaseEntity::m_hActiveWeapon
     */
    property int m_hActiveWeapon {
        /**
         * Gets the active weapon.
         *
         * @return              Current active weapon index.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_hActiveWeapon");
        }
    }

    /**
     * CBaseEntity::m_iAddonBits
     */
    property int m_iAddonBits {
        /**
         * Gets the addon bits.
         *
         * @return              Addon bits.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_iAddonBits");
        }

        /**
         * Sets the addon bits.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iAddonBits", val);
        }
    }

    /**
     * CBaseEntity::m_iObserverMode
     */
    property int m_iObserverMode {
        /**
         * Gets the observer mode.
         *
         * @return              Observer mode value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iObserverMode");
        }
    }

    /**
     * CBaseEntity::m_hObserverTarget
     */
    property int m_hObserverTarget {
        /**
         * Gets the observer target.
         *
         * @return              Observer target.
         * @error               Invalid entity. If target is nullptr, may crash the server.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_hObserverTarget");
        }
    }
    
    /**
     * CBaseEntity::m_LastHitGroup
     */
    property int m_LastHitGroup {
        /**
         * Gets the last hit group.
         *
         * @return              Last hit group.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_LastHitGroup");
        }
    }

    /**
     * CBaseEntity::m_iFrags
     */
    property int m_iFrags {
        /**
         * Gets the score.
         *
         * @return              Score value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iFrags");
        }

        /**
         * Sets the score.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iFrags", val);
        }
    }

    /**
     * CBaseEntity::m_iDeaths
     */
    property int m_iDeaths {
        /**
         * Gets the death.
         *
         * @return              Death value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iDeaths");
        }

        /**
         * Sets the death.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iDeaths", val);
        }
    }

    /**
     * CBaseEntity::m_flGravity
     */
    property float m_flGravity {
        /**
         * Gets the gravity.
         *
         * @return              Gravity value.
         * @error               Invalid entity.
         */
        public get() {
            this.GetPropFloat(Prop_Data, "m_flGravity");
        }

        /**
         * Sets the gravity.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(float val) {
            this.SetPropFloat(Prop_Data, "m_flGravity", val);
        }
    }

    /**
     * CBaseEntity::m_iAccount
     */
    property int m_iAccount {
        /**
         * Gets the money.
         *
         * @return              Money value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_iAccount");
        }

        /**
         * Sets the money.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_iAccount", val);
        }
    }

    /**
     * Sets the arm model.
     *
     * @param path              The path buffer.
     */
    public void SetArmsModel(const char[] path) {
        this.SetPropString(Prop_Send, "m_szArmsModel", path);
    }

    /**
     * CBaseEntity::m_flNextAttack
     */
    property float m_flNextAttack {
        /**
         * Gets the next attack.
         *
         * @return              Next attack value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropFloat(Prop_Send, "m_flNextAttack");
        }

        /**
         * Sets the next attack.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(float val) {
            this.SetPropFloat(Prop_Send, "m_flNextAttack", val);
        }
    }
    
    /**
     * CBaseEntity::m_iFOV
     */
    property int m_iFOV {
        /**
         * Gets the FOV.
         *
         * @return              The FOV value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_iFOV");
        }

        /**
         * Sets the FOV.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iFOV", val);
        }
    }

    /**
     * CBaseEntity::m_iDefaultFOV
     */
    property int m_iDefaultFOV {
        /**
         * Gets the default FOV.
         *
         * @return              The default FOV value.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_iDefaultFOV");
        }

        /**
         * Sets the default FOV.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_iDefaultFOV", val);
        }
    }
    
    /**
     * CBaseEntity::m_nBody
     */
    property int m_nBody {
        /**
         * Gets the body index.
         *
         * @return              The body index.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_nBody");
        }

        /**
         * Sets the body index.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nBody", val);
        }
    }

    /**
     * CBaseEntity::m_nSkin
     */
    property int m_nSkin {
        /**
         * Gets the skin index.
         *
         * @return              The skin index.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_nSkin");
        }

        /**
         * Sets the skin index.
         *
         * @param val           Value to modify.
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nSkin", val);
        }
    }

    /**
     * CBaseEntity::m_fEffects
     */
    property int m_fEffects {
        /**
         * Gets the effects of an entity.
         *
         * @return              The owner of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_fEffects");
        }
        
        /**
         * Sets the effects of an entity.
         *
         * @param val           Value to modify. 
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_fEffects", val);
        }
    }

    /**
     * CBaseEntity::m_nModelIndex
     */
    property int m_nModelIndex {
        /**
         * Gets the model index of an entity.
         *
         * @return              The owner of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Send, "m_nModelIndex");
        }

        /**
         * Gets the owner of an entity.
         *
         * @return              The owner of the entity.
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Send, "m_nModelIndex", val);
        }
    }

    /**
     * CBaseEntity::m_CollisionGroup
     */
    property int m_CollisionGroup {
        /**
         * Gets the collision group of an entity.
         *
         * @return              The collision group of the entity.
         * @error               Invalid entity.
         */
        public get() {
            return this.GetPropInt(Prop_Data, "m_CollisionGroup");
        }

        /**
         * Sets the collision group of an entity.
         *
         * @param val           Value to modify. 
         *
         * @error               Invalid entity.
         */
        public set(int val) {
            this.SetPropInt(Prop_Data, "m_CollisionGroup", val);
        }
    }
}

methodmap EntityEx {
    /**
     * @brief Ignites the entity on a fire.
     * 
     * @param entity            The entity index. 
     * @param flDurationTime    The number of seconds to set on a fire.
     */
    public static void Ignite(int entity, float flDurationTime)
    {
        // Validate duration
        if (flDurationTime > 0.0) 
        {
            // Put fire on it
            IgniteEntity(entity, flDurationTime);
        }
    }

    /**
     * @brief Extinguishes the entity that is on a fire.
     * 
     * @param entity            The entity index. 
     */
    public static void Extinguish(int entity)
    {
        // Validate fire entity
        int iFire = GetEntPropEnt(entity, Prop_Data, "m_hEffectEntity");
        if (IsValidEdict(iFire))
        {
            // Make sure the entity is a flame, so we can extinguish it
            char sClassname[SMALL_LINE_LENGTH];
            GetEdictClassname(iFire, sClassname, sizeof(sClassname));
            
            // Validate classname
            if (!strcmp(sClassname, "entityflame", false))
            {
                // Reduce entity's lifetime 
                SetEntPropFloat(iFire, Prop_Data, "m_flLifetime", 0.0);
            }
        }
    }

    /**
     * @brief Gets the health of a entity.
     *
     * @param entity            The entity index.
     * @param bMax              True to get maximum value, false to get health.  
     * @return                  The health value.
     */
    public static int GetHealth(int entity, bool bMax = false) {
        return GetEntProp(entity, Prop_Data, bMax ? "m_iMaxHealth" : "m_iHealth");
    }

    /**
     * @brief Sets the health of a entity.
     *
     * @param entity            The entity index.
     * @param iValue            The health value.
     * @param bSet              True to set maximum value, false to modify health.  
     */
    public static void SetHealth(int entity, int iValue, bool bSet=false) {
        SetEntProp(entity, Prop_Send, "m_iHealth", iValue);
    
        // If set is true, then set max health
        if (bSet) 
        {
            // Sets max health of the entity
            SetEntProp(entity, Prop_Data, "m_iMaxHealth", iValue);
        }
    }

    /**
     * @brief Gets or sets the velocity of a entity.
     *
     * @param entity            The entity index.
     * @param vVelocity         The velocity output, or velocity to set on entity.
     * @param bApply            True to get entity velocity, false to set it.
     * @param bStack            If modifying velocity, then true will stack new velocity onto the entity.
     *                          current velocity, false will reset it.
     */
    public static void SetVelocity(int entity, float vVelocity[3], bool bApply = true, bool bStack = true) {
        // If retrieve if true, then get entity velocity
        if (!bApply)
        {
            // Gets entity velocity
            EntityEx.GetVelocity(entity, vVelocity);
            
            // Stop here
            return;
        }
        
        // If stack is true, then add entity velocity
        if (bStack)
        {
            // Gets entity velocity
            static float vSpeed[3];
            EntityEx.GetVelocity(entity, vSpeed);

            
            // Add to the current
            AddVectors(vSpeed, vVelocity, vVelocity);
        }
        
        // Apply velocity on entity
        TeleportEntity(entity, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }

    /**
     * @brief Gets the velocity of a entity.
     *
     * @param entity            The entity index.
     * @param vVelocity         The velocity output.
     */
    public static void GetVelocity(int entity, float vVelocity[3]) {
        // Gets origin of the entity
        GetEntPropVector(entity, Prop_Data, "m_vecVelocity", vVelocity);
    }

    /**
     * @brief Gets the speed of a entity.
     *
     * @param entity            The entity index.
     */
    public static float GetSpeed(int entity) {
        static float vVeclocity[3];
        EntityEx.GetVelocity(entity, vVeclocity);

        return GetVectorLength(vVeclocity);
    }

    
    /**
     * @brief Gets the abs origin of a entity.
     *
     * @param entity            The entity index.
     * @param vPosition         The origin output.
     */
    public static void GetAbsOrigin(int entity, float vPosition[3])
    {
        // Gets origin of the entity
        GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vPosition);
    }

    /**
    * @brief Gets the abs angle of a entity.
    *
    * @param entity            The entity index.
    * @param vAngle            The angle output.
    */
    public static void GetAbsAngles(int entity, float vAngle[3])
    {
        // Gets angles of the entity
        GetEntPropVector(entity, Prop_Data, "m_angAbsRotation", vAngle);
    }

    /**
     * @brief Gets the max size vector of a entity.
     *
     * @param entity            The entity index.
     * @param vMaxs            The max size vector output.
     */
    public static void GetMaxs(int entity, float vMaxs[3])
    {
        // Gets the max size vector of the entity.
        GetEntPropVector(entity, Prop_Data, "m_vecMaxs", vMaxs);
    }

    /**
     * @brief Get m_vecMins.
     *
     * @param entity            The entity index.
     * @param vMaxs            The max size vector output.
     */
    public static void GetMins(int entity, float vMins[3])
    {
        GetEntPropVector(entity, Prop_Data, "m_vecMins", vMins);
    }

    /**
     * @brief Gets the max weapons of a entity.
     *
     * @param entity            The entity index.
     * @return                  The max weapon amount.
     */
    public static int GetMyWeapons(int entity)
    {
        // Gets weapons of the entity
        return GetEntPropArraySize(entity, Prop_Data, "m_hMyWeapons");
    }

    /**
    * @brief Gets weapon on the position of a entity.
    *
    * @param entity            The entity index.
    * @param iPosition         The weapon position.
    * @return                  The weapon index.
    */
    public static int GetWeapon(int entity, int iPosition)
    {
        // Gets weapon of the entity
        return GetEntPropEnt(entity, Prop_Data, "m_hMyWeapons", iPosition);
    }

    /**
     * @brief Gets the speed of a entity.
     *
     * @param entity            The entity index.
     * @return                  The LMV value.
     */
    public static float GetLMV(int entity)
    {
        // Gets lagged movement value of the entity
        return GetEntPropFloat(entity, Prop_Data, "m_flLaggedMovementValue");
    }

    /**
     * @brief Sets the speed of a entity.
     *
     * @param entity            The entity index.
     * @param flValue           The LMV value.
     */
    public static void SetLMV(int entity, float flValue)
    {
        // Sets lagged movement value of the entity
        SetEntPropFloat(entity, Prop_Data, "m_flLaggedMovementValue", flValue);
    }

    /**
     * @brief Gets the armor of a entity.
     *
     * @param entity            The entity index.
     * @return                  The armor value.
     */
    public static int GetArmor(int entity)
    {
        // Gets armor of the entity
        return GetEntProp(entity, Prop_Send, "m_ArmorValue");
    }

    /**
     * @brief Sets the armor of a entity.
     *
     * @param entity            The entity index.
     * @param iValue            The armor value.
     */
    public static void SetArmor(int entity, int iValue)
    {
        // Sets armor of the entity
        SetEntProp(entity, Prop_Send, "m_ArmorValue", iValue);
    }

    /**
     * @brief Gets the team of an entity.
     * 
     * @param entity            The entity index.
     * @return                  The team index.
     */
    public static int GetTeam(int entity)
    {
        // Gets team on the entity
        return GetEntProp(entity, Prop_Data, "m_iTeamNum");
    }

    /**
     * @brief Sets the team of a entity.
     *
     * @param entity            The entity index.
     * @param iValue            The team index.
     */
    public static void SetTeam(int entity, int iValue)
    {
        // Validate team
        if (EntityEx.GetTeam(entity) <= TEAM_SPECTATOR) /// Fix, thanks to inklesspen!
        {
            // Sets team of the entity
            ChangeClientTeam(entity, iValue);
        }
        else
        {
            #if defined _cstrike_included
                // Switch team of the entity
                CS_SwitchTeam(entity, iValue);
            #else
                #warning 'This function is game-specified. Please help us to update this part for manipulating specific game to let it works.'
            #endif 
        }
    }

    
    /**
     * @brief Gets nightvision values on a entity.
     *
     * @param entity            The entity index.
     * @param ownership         If true, function will return the value of the entity ownership of nightvision.
     *                          If false, function will return the value of the entity on/off state of the nightvision.
     * @return                  True if aspect of nightvision is enabled on the entity, false if not.
     */
    public static bool GetNightVision(int entity, bool bOwnership = false)
    {
        // If ownership is true, then gets the ownership of nightvision on entity
        return view_as<bool>(GetEntProp(entity, Prop_Send, bOwnership ? "m_bHasNightVision" : "m_bNightVisionOn"));
    }

    /**
     * @brief Controls nightvision values on a entity.
     *
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of nightvision. (see ownership parameter)
     * @param bOwnership        If true, enable will toggle the entity ownership of nightvision.
     *                          If false, enable will toggle the entity on/off state of the nightvision.
     */
    public static void SetNightVision(int entity, bool bEnable, bool bOwnership = false)
    {
        // If ownership is true, then toggle the ownership of nightvision on entity
        SetEntProp(entity, Prop_Send, bOwnership ? "m_bHasNightVision" : "m_bNightVisionOn", bEnable);
    }

    /**
    * @brief Gets defuser value on a entity.
    *
    * @param entity            The entity index.
    * @return                  The aspect of the entity defuser.
    */
    public static bool GetDefuser(int entity)
    {
        // Gets defuser on the entity
        return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasDefuser"));
    }

    /**
     * @brief Controls defuser value on a entity.
     *
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of defuser.
     */
    public static void SetDefuser(int entity, bool bEnable)
    {
        // Sets defuser on the entity
        SetEntProp(entity, Prop_Send, "m_bHasDefuser", bEnable);
    }

    /**
     * @brief Gets helmet value on a entity.
     *
     * @param entity            The entity index.
     * @return                  The aspect of the entity helmet.
     */
    public static bool GetHelmet(int entity)
    {
        // Gets helmet on the entity
        return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasHelmet"));
    }

    /**
     * @brief Controls helmet value on a entity.
     *
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of helmet.
     */
    public static void SetHelmet(int entity, bool bEnable)
    {
        // Sets helmet on the entity
        SetEntProp(entity, Prop_Send, "m_bHasHelmet", bEnable);
    }

    /**
     * @brief Gets suit value on a entity.
     *
     * @param entity            The entity index.
     * @return                  The aspect of the entity suit.
     */
    public static bool GetHeavySuit(int entity)
    {
        // Gets suit on the entity
        return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasHeavyArmor"));
    }

    /**
     * @brief Controls suit value on a entity.
     *
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of suit.
     */
    public static void SetHeavySuit(int entity, bool bEnable)
    {
        // Sets suit on the entity
        SetEntProp(entity, Prop_Send, "m_bHasHeavyArmor", bEnable);
    }

    /**
     * @brief Gets the active weapon index of a entity.
     *
     * @param entity            The entity index.
     * @return                  The weapon index.
     */
    public static int GetActiveWeapon(int entity)
    {
        // Gets weapon on the entity
        return GetEntPropEnt(entity, Prop_Send, "m_hActiveWeapon");
    }

    /**
     * @brief Sets the active weapon index of a entity.
     *
     * @param entity            The entity index.
     * @param weapon            The weapon index.
     */
    /*void SetActiveWeapon(int entity, int weapon)
    {
        // Sets weapon on the entity    
        SetEntPropEnt(entity, Prop_Send, "m_hActiveWeapon", weapon);
    }*/

    /**
     * @brief Gets the addon bits of a entity.
     *
     * @param entity            The entity index.
     * @return                  The addon bits.
     */
    public static int GetAddonBits(int entity)
    {
        // Gets addon value on the entity    
        return GetEntProp(entity, Prop_Send, "m_iAddonBits");
    }

    /**
     * @brief Sets the addon bits index of a entity.
     *
     * @param entity            The entity index.
     * @param iValue            The addon bits.
     */
    public static void SetAddonBits(int entity, int iValue)
    {
        // Sets addon value on the entity    
        SetEntProp(entity, Prop_Send, "m_iAddonBits", iValue);
    }

    /**
     * @brief Gets the observer mode of a entity.
     *
     * @param entity            The entity index.
     * @return                  The mode index.
     */
    public static int GetObserverMode(int entity)
    {
        // Gets obs mode on the entity    
        return GetEntProp(entity, Prop_Data, "m_iObserverMode");
    }

    /**
     * @brief Gets the observer target of a entity.
     *
     * @param entity            The entity index.
     * @return                  The target index.
     */
    public static int GetObserverTarget(int entity)
    {
        // Gets obs mode on the entity    
        return GetEntPropEnt(entity, Prop_Data, "m_hObserverTarget");
    }

    /**
     * @brief Gets hitgroup value on a entity.
     *
     * @param entity            The entity index.
     * @return                  The hitgroup index.
     */
    public static int GetHitGroup(int entity)
    {
        // Gets hitgroup on the entity    
        return GetEntProp(entity, Prop_Send, "m_LastHitGroup");
    }

    /**
     * @brief Gets or sets a entity score or deaths.
     * 
     * @param entity            The entity index.
     * @param bScore            True to look at score, false to look at deaths.  
     * @return                  The score or death count of the entity.
     */
    public static int GetScore(int entity, bool bScore = true)
    {
        // If score is true, then return entity score, otherwise return entity deaths
        return GetEntProp(entity, Prop_Data, bScore ? "m_iFrags" : "m_iDeaths");
    }

    /**
     * @brief Sets a entity score or deaths.
     * 
     * @param entity            The entity index.
     * @param bScore            True to look at score, false to look at deaths.  
     * @param iValue            The score/death amount.
     */
    public static void SetScore(int entity, bool bScore = true, int iValue = 0)
    {
        // If score is true, then set entity score, otherwise set entity deaths
        SetEntProp(entity, Prop_Data, bScore ? "m_iFrags" : "m_iDeaths", iValue);
    }

    public static float GetGravity(int entity)
    {
        return GetEntPropFloat(entity, Prop_Data, "m_flGravity");
    }

    /**
     * @brief Sets the gravity of a entity.
     * 
     * @param entity            The entity index.
     * @param flValue           The gravity amount.
     */
    public static void SetGravity(int entity, float flValue)
    {
        // Sets gravity on the entity
        SetEntPropFloat(entity, Prop_Data, "m_flGravity", flValue);
    }

    /**
     * @brief Gets the money of an entity.
     *
     * @param entity            The entity index.
     * 
     * @return                  The money amount.
     */
    public static int GetMoney(int entity)
    {
        return GetEntProp(entity, Prop_Send, "m_iAccount");
    }

    /**
     * @brief Sets the money of an entity.
     *
     * @param entity            The entity index.
     * @param amount            The money value.
     */
    public static void SetMoney(int entity, int amount)
    {
        SetEntProp(entity, Prop_Send, "m_iAccount", amount);
    }

    /**
     * @brief Sets the spotting of a entity.
     * 
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of spotting.
     */
    /* void SetSpot(int entity, bool bEnable)
    {
        // If retrieve if true, then reset variables
        if (!bEnable)
        {
            // Sets value on the entity
            SetEntData(entity, Player_Spotted, false, 1, true);
            SetEntData(entity, Player_SpottedByMask, false, _, true);
            SetEntData(entity, Player_SpottedByMask + 4, false, _, true); /// That is table
            SetEntData(entity, Player_Spotted - 4, 0, _, true);
        }
        else
        {
            // Sets value on the entity
            SetEntData(entity, Player_Spotted - 4, 9, _, true);
        }
    } */

    /**
     * @brief Sets the detecting of a entity.
     * 
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of detection.
     */
    public static void SetDetecting(int entity, bool bEnable)
    {
        // Sets glow on the entity
        SetEntPropFloat(entity, Prop_Send, "m_flDetectedByEnemySensorTime", bEnable ? (GetGameTime() + 9999.0) : 0.0);
    }

    /**
     * @brief Sets the hud of a entity.
     * 
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of hud.
     */
    public static void SetHud(int entity, bool bEnable, int iFlag)
    {   
        // bEnable ? (GetEntProp(entity, Prop_Send, "m_iHideHUD") & ~HIDEHUD_CROSSHAIR) : (GetEntProp(entity, Prop_Send, "m_iHideHUD") | HIDEHUD_CROSSHAIR)
        // Sets hud type on the entity
        SetEntProp(
            entity, 
            Prop_Send, 
            "m_iHideHUD", 
            bEnable ? (GetEntProp(entity, Prop_Send, "m_iHideHUD") & ~iFlag) : (GetEntProp(entity, Prop_Send, "m_iHideHUD") | iFlag)
            );
    }

    /**
     * @brief Sets the arms of a entity.
     * 
     * @param entity            The entity index.
     * @param sModel            The model path.
     */
    public static void SetArmsModel(int entity, char[] sModel)
    {
        // Sets arm on the entity
        SetEntPropString(entity, Prop_Send, "m_szArmsModel", sModel);
    }

    /**
     * @brief Sets the attack delay of a entity.
     * 
     * @param entity            The entity index.
     * @param flValue           The speed amount.
     */
    public static void SetAttack(int entity, float flValue)
    {
        // Sets next attack on the entity
        SetEntPropFloat(entity, Prop_Send, "m_flNextAttack", flValue);
    }
    
    /**
     * @brief Gets the effect of an entity.
     * 
     * @param entity            The entity index.
     * @return                  The effect value.
     */
    public static int GetEffect(int entity)
    {
        // Gets effect on the entity    
        return GetEntProp(entity, Prop_Send, "m_fEffects");
    }

    /**
     * @brief Sets the effect of an entity.
     * 
     * @param entity            The entity index.
     * @param iValue            The effect value.
     */
    public static void SetEffect(int entity, int iValue)
    {
        // Sets effect on the entity
        SetEntProp(entity, Prop_Send, "m_fEffects", iValue);
    }

    /**
     * @brief Sets the flashlight of a entity.
     * 
     * @param entity            The entity index.
     * @param bEnable           Enable or disable an aspect of flashlight.
     */
    public static void SetFlashLight(int entity, bool bEnable)
    {
        // Sets flashlight on the entity
        EntityEx.SetEffect(entity, bEnable ? (EntityEx.GetEffect(entity) ^ EF_DIMLIGHT) : 0);
    }

    /**
     * @brief Sets the fov of a entity.
     * 
     * @param entity            The entity index.
     * @param iValue            (Optional) The fov amount.
     */
    public static void SetFov(int entity, int iValue = 90)
    {
        // Sets fov on the entity
        SetEntProp(entity, Prop_Send, "m_iFOV", iValue);
        SetEntProp(entity, Prop_Send, "m_iDefaultFOV", iValue);
    }

    /**
     * @brief Sets body/skin for the entity.
     *
     * @param entity            The entity index.
     * @param iBody             (Optional) The body index.
     * @param iSkin             (Optional) The skin index.
     */
    public static void SetTextures(int entity, int iBody = -1, int iSkin = -1)
    {
        if (iBody != -1) SetEntProp(entity, Prop_Send, "m_nBody", iBody);
        if (iSkin != -1) SetEntProp(entity, Prop_Send, "m_nSkin", iSkin);
    }

    /**
     * @brief Gets the activator of an entity.
     *
     * @param entity            The entity index.
     * @return                  The activator index.
     */
    public static int GetActivator(int entity)
    {
        // Gets activator on the entity
        return GetEntPropEnt(entity, Prop_Data, "m_pActivator");
    }

    /**
     * @brief Sets the model of an entity.
     * 
     * @param entity            The entity index.
     * @param iModel            The model index.
     */
    public static void SetModelIndex(int entity, int iModel)
    {
        // Sets index on the entity
        SetEntProp(entity, Prop_Send, "m_nModelIndex", iModel);
    }

    /**
     * @brief Gets the owner of an entity.
     * 
     * @param entity            The entity index.
     * @return                  The owner index.
     */
    public static int GetOwner(int entity)
    {
        // Gets owner on the entity
        return GetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity");
    }

    /**
     * @brief Sets the owner of an entity.
     * 
     * @param entity            The entity index.
     * @param owner             The owner index.
     */
    public static void SetOwner(int entity, int owner)
    {
        // Sets owner on the entity
        SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", owner);
    }

    /**
     * @brief Gets the parent of an entity.
     * 
     * @param entity            The entity index.
     * @return                  The parent index.
     */
    public static int GetParent(int entity)
    {
        // Gets owner on the entity
        return GetEntPropEnt(entity, Prop_Data, "m_pParent");
    }

    /**
     * @brief Sets the parent of an entity.
     * 
     * @param entity            The entity index.
     * @param parent            The parent index.
     */
    public static void SetParent(int entity, int parent)
    {
        // Sets parent on the entity
        SetEntPropEnt(entity, Prop_Data, "m_pParent", parent);
    }

    /**
     * @brief Gets the ragdoll index on a client.
     *
     * @param client            The client index.
     * @return                  The ragdoll index.
     */
    public static int GetRagdollIndex(int client)
    {
        return GetEntPropEnt(client, Prop_Send, "m_hRagdoll");
    }

    /**
     * @brief Gets the collision group on a client.
     *
     * @param client            The client index.
     * @return                  The collision group on the client.
     */
    public static int GetCollisionGroup(int client)
    {
        return GetEntProp(client, Prop_Data, "m_CollisionGroup");
    }

    /**
     * @brief Sets the collision group on a client.
     *
     * @param client            The client index.
     * @param collisionGroup    The group flag.
     */
    public static void SetCollisionGroup(int client, int collisionGroup)
    {
        SetEntProp(client, Prop_Data, "m_CollisionGroup", collisionGroup);
    }
}