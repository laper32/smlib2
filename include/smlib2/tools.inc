#if defined _tools_included
#endinput
#endif
#define _tools_included

/**
 * @brief Gets or sets the velocity of a entity.
 *
 * @param entity            The entity index.
 * @param vVelocity         The velocity output, or velocity to set on entity.
 * @param bApply            True to get entity velocity, false to set it.
 * @param bStack            If modifying velocity, then true will stack new velocity onto the entity.
 *                          current velocity, false will reset it.
 */
inline void ToolsSetVelocity(int entity, float vVelocity[3], bool bApply = true, bool bStack = true)
{
    // If retrieve if true, then get entity velocity
    if (!bApply)
    {
        // Gets entity velocity
        ToolsGetVelocity(entity, vVelocity);
        
        // Stop here
        return;
    }
    
    // If stack is true, then add entity velocity
    if (bStack)
    {
        // Gets entity velocity
        static float vSpeed[3];
        ToolsGetVelocity(entity, vSpeed);
        
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
inline void ToolsGetVelocity(int entity, float vVelocity[3])
{
    // Gets origin of the entity
    GetEntPropVector(entity, Prop_Data, "m_vecVelocity", vVelocity);
}

/**
 * @brief Gets the speed of a entity.
 *
 * @param entity            The entity index.
 */
inline float ToolsGetSpeed(int entity)
{
    static float vVeclocity[3];
    ToolsGetVelocity(entity, vVeclocity);

    return GetVectorLength(vVeclocity);
}

/**
 * @brief Gets the abs origin of a entity.
 *
 * @param entity            The entity index.
 * @param vPosition         The origin output.
 */
inline void ToolsGetAbsOrigin(int entity, float vPosition[3])
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
inline void ToolsGetAbsAngles(int entity, float vAngle[3])
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
inline void ToolsGetMaxSizeVector(int entity, float vMaxs[3])
{
    // Gets the max size vector of the entity.
    GetEntPropVector(entity, Prop_Data, "m_vecMaxs", vMaxs);
}

/**
 * @brief Gets the center origin of an entity.
 *
 * @param entity            The entity index.
 * @param vOutput           The vector output.
 */
inline void ToolsGetCenterPosition(int entity, float vOutput[3])
{
    // Get abs origin.
    ToolsGetAbsOrigin(entity, vOutput);

    static float vMaxs[3]; 
    // Client index is from 1-66.
    if (entity <= MaxClients) GetClientMaxs(entity, vMaxs);
    // Otherwise, get this entity's max size vector.
    else ToolsGetMaxSizeVector(entity, vMaxs);

    vOutput[2] += vMaxs[2] / 2.0; 
}

/**
 * @brief Gets the entity's eye position.
 * 
 * @param entity            The entity index.     
 * @param vOutput           The vector output.
 **/
inline void ToolsGetEyePosition(int entity, float vOutput[3])
{
    // Client index is from 1-66.
    if (entity <= MaxClients) GetClientEyePosition(entity, vOutput);
    else
    {
        static float vMaxs[3]; 
        ToolsGetAbsOrigin(entity, vOutput);
        ToolsGetMaxSizeVector(entity, vMaxs); 
        vOutput[2] += vMaxs[2]; 
    }
}

/**
 * @brief Gets the max weapons of a entity.
 *
 * @param entity            The entity index.
 * @return                  The max weapon amount.
 */
inline int ToolsGetMyWeapons(int entity)
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
inline int ToolsGetWeapon(int entity, int iPosition)
{
    // Gets weapon of the entity
    return GetEntPropEnt(entity, Prop_Data, "m_hMyWeapons", iPosition);
}

/**
 * @brief Gets the health of a entity.
 *
 * @param entity            The entity index.
 * @param bMax              True to get maximum value, false to get health.  
 * @return                  The health value.
 */
inline int ToolsGetHealth(int entity, bool bMax = false)
{
    // Gets health of the entity
    return GetEntProp(entity, Prop_Data, bMax ? "m_iMaxHealth" : "m_iHealth");
}

/**
 * @brief Sets the health of a entity.
 *
 * @param entity            The entity index.
 * @param iValue            The health value.
 * @param bSet              True to set maximum value, false to modify health.  
 */
inline void ToolsSetHealth(int entity, int iValue, bool bSet = false)
{
    // Sets health of the entity
    SetEntProp(entity, Prop_Send, "m_iHealth", iValue);
    
    // If set is true, then set max health
    if (bSet) 
    {
        // Sets max health of the entity
        SetEntProp(entity, Prop_Data, "m_iMaxHealth", iValue);
    }
}

/**
 * @brief Gets the speed of a entity.
 *
 * @param entity            The entity index.
 * @return                  The LMV value.
 */
inline float ToolsGetLMV(int entity)
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
inline void ToolsSetLMV(int entity, float flValue)
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
inline int ToolsGetArmor(int entity)
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
inline void ToolsSetArmor(int entity, int iValue)
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
inline int ToolsGetTeam(int entity)
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
inline void ToolsSetTeam(int entity, int iValue)
{
    // Validate team
    if (ToolsGetTeam(entity) <= TEAM_SPECTATOR) /// Fix, thanks to inklesspen!
    {
        // Sets team of the entity
        ChangeClientTeam(entity, iValue);
    }
    else
    {
        // Switch team of the entity
        CS_SwitchTeam(entity, iValue); 
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
inline bool ToolsGetNightVision(int entity, bool bOwnership = false)
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
inline void ToolsSetNightVision(int entity, bool bEnable, bool bOwnership = false)
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
inline bool ToolsGetDefuser(int entity)
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
inline void ToolsSetDefuser(int entity, bool bEnable)
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
inline bool ToolsGetHelmet(int entity)
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
inline void ToolsSetHelmet(int entity, bool bEnable)
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
inline bool ToolsGetHeavySuit(int entity)
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
inline void ToolsSetHeavySuit(int entity, bool bEnable)
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
inline int ToolsGetActiveWeapon(int entity)
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
/*void ToolsSetActiveWeapon(int entity, int weapon)
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
inline int ToolsGetAddonBits(int entity)
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
inline void ToolsSetAddonBits(int entity, int iValue)
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
inline int ToolsGetObserverMode(int entity)
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
inline int ToolsGetObserverTarget(int entity)
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
inline int ToolsGetHitGroup(int entity)
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
inline int ToolsGetScore(int entity, bool bScore = true)
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
inline void ToolsSetScore(int entity, bool bScore = true, int iValue = 0)
{
    // If score is true, then set entity score, otherwise set entity deaths
    SetEntProp(entity, Prop_Data, bScore ? "m_iFrags" : "m_iDeaths", iValue);
}

/**
 * @brief Sets the gravity of a entity.
 * 
 * @param entity            The entity index.
 * @param flValue           The gravity amount.
 */
inline void ToolsSetGravity(int entity, float flValue)
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
inline int ToolsGetMoney(int entity)
{
    return GetEntProp(entity, Prop_Data, "m_iAccount");
}

/**
 * @brief Sets the money of an entity.
 *
 * @param entity            The entity index.
 * @param amount            The money value.
 */
inline void ToolsSetMoney(int entity, int amount)
{
    SetEntProp(entity, Prop_Data, "m_iAccount", amount);
}

/**
 * @brief Sets the spotting of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of spotting.
 */
/* void ToolsSetSpot(int entity, bool bEnable)
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
inline void ToolsSetDetecting(int entity, bool bEnable)
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
inline void ToolsSetHud(int entity, bool bEnable, int iFlag)
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
inline void ToolsSetArm(int entity, char[] sModel)
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
inline void ToolsSetAttack(int entity, float flValue)
{
    // Sets next attack on the entity
    SetEntPropFloat(entity, Prop_Send, "m_flNextAttack", flValue);
}

/**
 * @brief Sets the flashlight of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of flashlight.
 */
inline void ToolsSetFlashLight(int entity, bool bEnable)
{
    // Sets flashlight on the entity
    ToolsSetEffect(entity, bEnable ? (ToolsGetEffect(entity) ^ EF_DIMLIGHT) : 0);
}

/**
 * @brief Sets the fov of a entity.
 * 
 * @param entity            The entity index.
 * @param iValue            (Optional) The fov amount.
 */
inline void ToolsSetFov(int entity, int iValue = 90)
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
inline void ToolsSetTextures(int entity, int iBody = -1, int iSkin = -1)
{
    if (iBody != -1) SetEntProp(entity, Prop_Send, "m_nBody", iBody);
    if (iSkin != -1) SetEntProp(entity, Prop_Send, "m_nSkin", iSkin);
}

/**
 * @brief Gets the effect of an entity.
 * 
 * @param entity            The entity index.
 * @return                  The effect value.
 */
inline int ToolsGetEffect(int entity)
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
inline void ToolsSetEffect(int entity, int iValue)
{
    // Sets effect on the entity
    SetEntProp(entity, Prop_Send, "m_fEffects", iValue);
}

/**
 * @brief Gets the activator of an entity.
 *
 * @param entity            The entity index.
 * @return                  The activator index.
 */
inline int ToolsGetActivator(int entity)
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
inline void ToolsSetModelIndex(int entity, int iModel)
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
inline int ToolsGetOwner(int entity)
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
inline void ToolsSetOwner(int entity, int owner)
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
inline int ToolsGetParent(int entity)
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
inline void ToolsSetParent(int entity, int parent)
{
    // Sets parent on the entity
    SetEntPropEnt(entity, Prop_Data, "m_pParent", parent);
}

/**
 * @brief Gets the ragdoll index on a client.
 *
 * @param client            The client index.
 * @return                  The ragdoll index.
 **/
inline int ToolsGetRagdollIndex(int client)
{
    return GetEntPropEnt(client, Prop_Send, "m_hRagdoll");
}

/**
 * @brief Gets the collision group on a client.
 *
 * @param client            The client index.
 * @return                  The collision group on the client.
 **/
inline int ToolsGetCollisionGroup(int client)
{
    return GetEntProp(client, Prop_Data, "m_CollisionGroup");
}

/**
 * @brief Sets the collision group on a client.
 *
 * @param client            The client index.
 * @param collisionGroup    The group flag.
 **/
inline void ToolsSetCollisionGroup(int client, int collisionGroup)
{
    SetEntProp(client, Prop_Data, "m_CollisionGroup", collisionGroup);
}

/**
 * @brief Checks if a player is currently stuck within another player.
 *
 * @param client     1      The first client index.
 * @param client     2      The second client index.
 * @return                  True if they are stuck together, false if not.
 **/
inline bool ToolsIsModelBoxColliding(int clientIndex1, int clientIndex2)
{
    // Initialize vector variables
    float client1modelbox[BoxBound][3];
    float client2modelbox[BoxBound][3];
    
    // Build model boxes for each client
    ToolsBuildModelBox(clientIndex1, client1modelbox, DEFAULT_HULL_WIDTH);
    ToolsBuildModelBox(clientIndex2, client2modelbox, DEFAULT_HULL_WIDTH);
    
    // Compare x values
    float max1x = ToolsGetBoxMaxBoundary(0, client1modelbox);
    float max2x = ToolsGetBoxMaxBoundary(0, client2modelbox);
    float min1x = ToolsGetBoxMaxBoundary(0, client1modelbox, true);
    float min2x = ToolsGetBoxMaxBoundary(0, client2modelbox, true);
    
    if (max1x < min2x || min1x > max2x)
    {
        return false;
    }
    
    // Compare y values
    float max1y = ToolsGetBoxMaxBoundary(1, client1modelbox);
    float max2y = ToolsGetBoxMaxBoundary(1, client2modelbox);
    float min1y = ToolsGetBoxMaxBoundary(1, client1modelbox, true);
    float min2y = ToolsGetBoxMaxBoundary(1, client2modelbox, true);
    
    if (max1y < min2y || min1y > max2y)
    {
        return false;
    }
    
    // Compare z values
    float max1z = ToolsGetBoxMaxBoundary(2, client1modelbox);
    float max2z = ToolsGetBoxMaxBoundary(2, client2modelbox);
    float min1z = ToolsGetBoxMaxBoundary(2, client1modelbox, true);
    float min2z = ToolsGetBoxMaxBoundary(2, client2modelbox, true);
    
    if (max1z < min2z || min1z > max2z)
    {
        return false;
    }
    
    // They are intersecting
    return true;
}

/**
 * @brief Used to iterate all the clients collision within a sphere.
 * 
 * @param it                The iterator.
 * @param vPosition         The sphere origin.
 * @param flRadius          The sphere radius.
 **/
inline int ToolsFindPlayerInSphere(int &it, float vPosition[3], float flRadius)
{
    // Initialize vector variables
    float clientmodelbox[BoxBound][3];

    // i = client index
    for (int i = it; i <= MaxClients; i++)
    {
        // Validate client
        if (IsPlayerExist(i))
        {
            // Build model boxes for client
            ToolsBuildModelBox(i, clientmodelbox, DEFAULT_HULL_WIDTH);

            // Validate collision
            if (ToolsIsBoxIntersectingSphere(clientmodelbox, vPosition, flRadius))
            { 
                // Move iterator
                it = i + 1;
        
                // Return index
                return i;
            }
        }
    }
    
    // Client doesn't exist
    return -1;
}

/**
 * @brief Returns true if there's an intersection between box and sphere.
 * 
 * @param flBoundaries      Array with 'BoxBound' for indexes to return bounds into.
 * @param vPosition         The sphere center.
 * @param flRadius          The sphere radius.
 * 
 * @return                  True or false. 
 *
 * @link https://github.com/erich666/GraphicsGems/blob/master/gems/BoxSphere.c
 */
inline bool ToolsIsBoxIntersectingSphere(float flBoundaries[BoxBound][3], float vPosition[3], float flRadius)
{
    // See graphics gems, box-sphere intersection
    float flDelta; float flDistance;

    /// Unrolled the loop.. this is a big cycle stealer...

    // Compare x values
    float maxBx = ToolsGetBoxMaxBoundary(0, flBoundaries);
    float minBx = ToolsGetBoxMaxBoundary(0, flBoundaries, true);  

    if (vPosition[0] < minBx) 
    {
        flDelta = vPosition[0] - minBx;
        flDistance += flDelta * flDelta;
    }
    else if (vPosition[0] > maxBx) 
    {   
        flDelta = vPosition[0] - maxBx;
        flDistance += flDelta * flDelta;   
    }
    
    // Compare y values
    float maxBy = ToolsGetBoxMaxBoundary(1, flBoundaries);
    float minBy = ToolsGetBoxMaxBoundary(1, flBoundaries, true);  
    
    if (vPosition[1] < minBy) 
    {
        flDelta = vPosition[1] - minBy;
        flDistance += flDelta * flDelta;
    }
    else if (vPosition[1] > maxBy) 
    {   
        flDelta = vPosition[1] - maxBy;
        flDistance += flDelta * flDelta;   
    }
    
    // Compare z values
    float maxBz = ToolsGetBoxMaxBoundary(2, flBoundaries);
    float minBz = ToolsGetBoxMaxBoundary(2, flBoundaries, true); 
    
    if (vPosition[2] < minBz) 
    {
        flDelta = vPosition[2] - minBz;
        flDistance += flDelta * flDelta;
    }
    else if (vPosition[2] > maxBz) 
    {   
        flDelta = vPosition[2] - maxBz;
        flDistance += flDelta * flDelta;   
    }

    // Return true on the collision
    return flDistance <= (flRadius * flRadius);
}

/**
 * @brief Gets the max/min value of a 3D box on any axis.
 * 
 * @param iAxis             The axis to check.
 * @param flBoundaries      The boundaries to check.
 * @param bMin              Return the min value instead.
 **/
inline float ToolsGetBoxMaxBoundary(int iAxis, float flBoundaries[BoxBound][3], bool bMin = false)
{
    // Creates 'outlier' with initial value of first boundary
    float flOutlier = flBoundaries[0][iAxis];
    
    // x = Boundary index. (Start at 1 because we initialized 'outlier' with the 0 index value)
    int iSize = sizeof(flBoundaries);
    for (int x = 1; x < iSize; x++)
    {
        if (!bMin && flBoundaries[x][iAxis] > flOutlier)
        {
            flOutlier = flBoundaries[x][iAxis];
        }
        else if (bMin && flBoundaries[x][iAxis] < flOutlier)
        {
            flOutlier = flBoundaries[x][iAxis];
        }
    }
    
    // Return value
    return flOutlier;
}

/**
 * @brief Build the model box by finding all vertices.
 * 
 * @param client            The client index.
 * @param flBoundaries      Array with 'BoxBounds' for indexes to return bounds into.
 * @param width             The width of the model box.
 **/
inline void ToolsBuildModelBox(int client, float flBoundaries[BoxBound][3], float flWidth)
{
    // Initialize vector variables
    static float vTwistAngle[3]; static float vCornerAngle[3];
    static float vOriginLoc[3]; static float vSideLoc[3]; static float vFinalLoc[4][3];

    // Gets needed vector info
    ToolsGetAbsOrigin(client, vOriginLoc);

    // Sets pitch to 0
    vTwistAngle[1] = 90.0;
    vCornerAngle[1] = 0.0;

    // i = side index
    for (int x = 0; x < 4; x++)
    {
        // Jump to point on player left side.
        ToolsJumpToPoint(vOriginLoc, vTwistAngle, flWidth / 2, vSideLoc);

        // From this point, jump to the corner, which would be half the width from the middle of a side
        ToolsJumpToPoint(vSideLoc, vCornerAngle, flWidth / 2, vFinalLoc[x]);

        // Twist 90 degrees to find next side/corner
        vTwistAngle[1] += 90.0;
        vCornerAngle[1] += 90.0;

        // Fix angles
        if (vTwistAngle[1] > 180.0)
        {
            vTwistAngle[1] -= 360.0;
        }

        if (vCornerAngle[1] > 180.0)
        {
            vCornerAngle[1] -= 360.0;
        }
    }

    // Copy all horizontal model box data to array
    flBoundaries[BoxBound_FUR][0] = vFinalLoc[3][0];
    flBoundaries[BoxBound_FUR][1] = vFinalLoc[3][1];
    flBoundaries[BoxBound_FUL][0] = vFinalLoc[0][0];
    flBoundaries[BoxBound_FUL][1] = vFinalLoc[0][1];
    flBoundaries[BoxBound_FDR][0] = vFinalLoc[3][0];
    flBoundaries[BoxBound_FDR][1] = vFinalLoc[3][1];
    flBoundaries[BoxBound_FDL][0] = vFinalLoc[0][0];
    flBoundaries[BoxBound_FDL][1] = vFinalLoc[0][1];
    flBoundaries[BoxBound_BUR][0] = vFinalLoc[2][0];
    flBoundaries[BoxBound_BUR][1] = vFinalLoc[2][1];
    flBoundaries[BoxBound_BUL][0] = vFinalLoc[1][0];
    flBoundaries[BoxBound_BUL][1] = vFinalLoc[1][1];
    flBoundaries[BoxBound_BDR][0] = vFinalLoc[2][0];
    flBoundaries[BoxBound_BDR][1] = vFinalLoc[2][1];
    flBoundaries[BoxBound_BDL][0] = vFinalLoc[1][0];
    flBoundaries[BoxBound_BDL][1] = vFinalLoc[1][1];

    // Sets Z bounds
    static float vEyeLoc[3];
    GetClientEyePosition(client, vEyeLoc);

    flBoundaries[BoxBound_FUR][2] = vEyeLoc[2];
    flBoundaries[BoxBound_FUL][2] = vEyeLoc[2];
    flBoundaries[BoxBound_FDR][2] = vOriginLoc[2] + 15.0;
    flBoundaries[BoxBound_FDL][2] = vOriginLoc[2] + 15.0;
    flBoundaries[BoxBound_BUR][2] = vEyeLoc[2];
    flBoundaries[BoxBound_BUL][2] = vEyeLoc[2];
    flBoundaries[BoxBound_BDR][2] = vOriginLoc[2] + 15.0;
    flBoundaries[BoxBound_BDL][2] = vOriginLoc[2] + 15.0;
}

/**
 * @brief Jumps from a point to another based off angle and distance.
 * 
 * @param flVector          Point to jump from.
 * @param flAngle           Angle to base jump off of.
 * @param flDistance        Distance to jump
 * @param flResult          Resultant point.
 **/
inline void ToolsJumpToPoint(float vVector[3], float vAngle[3], float flDistance, float vResult[3])
{
    // Initialize vector variable
    static float vViewLoc[3];
    
    // Turn client angle, into a vector
    GetAngleVectors(vAngle, vViewLoc, NULL_VECTOR, NULL_VECTOR);
    
    // Normalize vector
    NormalizeVector(vViewLoc, vViewLoc);
    
    // Scale to the given distance
    ScaleVector(vViewLoc, flDistance);
    
    // Add the vectors together
    AddVectors(vVector, vViewLoc, vResult);
}

/**
 * @brief Calculate whether the sector is intersecing with the disk.
 *
 * @link https://zhuanlan.zhihu.com/p/23903445?hmsr=toutiao.io
 *
 * @param vSectorOrigin                         The sector origin.
 * @param vSectorDirection                      The sector direction.
 * @param flSectorScannedAngle                  The sector scanned angle.
 * @param flSectorRadius                        The sector radius.
 * @param flDiskOrigin                          The disk origin.
 * @param flDiskRadius                          The disk radius.
 * @return                                      True when they are intersecting, false otherwise.
 */
inline bool ToolsIsSectorDiskIntersect(
    float vSectorOrigin[3], float vSectorDirection[3], float flSectorScannedAngle,
    float flSectorRadius, float vDiskOrigin[3], float flDiskRadius
    )
{
    // First to calculate whether is sepearable.
    // In this term, treat sector as a disk. This is because: Sector is (X/Y) of a circle.

    // Subtract vector.
    // vOriginDistance = vDiskOrigin - vSectorOrigin
    static float vOriginDistance[3];
    SubtractVectors(vDiskOrigin, vSectorOrigin, vOriginDistance);

    // Calculate the distance between two points.
    float flOriginDistanceBetween = GetVectorLength(vOriginDistance, true);

    // Calculate the sum of two disks radius.
    float flRangeSum = flSectorRadius + flDiskRadius;

    // We know that if the distance between two points greater than the sum of the range of the sector and the disk, then
    // it is absolutely not intersecting.
    if (flOriginDistanceBetween <= flRangeSum * flRangeSum)  return true;

    // We changed basis of the coordinate, so that we need to re-calculate the origin of the disk.
    // Treat the disk's origin is P.

    // Calculate X-axis value.
    float Px = GetVectorDotProduct(vOriginDistance, vSectorDirection);

    // Calculate Y-axis value.
    // Before calculate P, we need to calculate the sector's unit vector's transform.
    static float vSectorDirectionTransformed[3];
    vSectorDirectionTransformed[0] = -vSectorDirection[1]; // x' = -y
    vSectorDirectionTransformed[1] =  vSectorDirection[0]; // y' = x
    vSectorDirectionTransformed[2] =  vSectorDirection[2]; // We don't consider anything about Z-Value(Why we consider about this??)

    // We dont need to consider negative condition.
    // Why we need to consider it when it is symmetry?
    float Py = fabs(GetVectorDotProduct(vOriginDistance, vSectorDirectionTransformed));

    // Px > |p|*cos(angle) -> Not intersecting
    if (Px > ( sqrt(flOriginDistanceBetween) * Cosine(flSectorScannedAngle) ) ) return true;

    // Calculate left line whether intersect with the disk.
    static float vLineAngle[3], vLineWithAngleCalculated[3], vLineTransposedDisk[3];
    vLineAngle[0] = Cosine(flSectorScannedAngle);
    vLineAngle[1] = Sine(flSectorScannedAngle);
    vLineAngle[2] = 0.0;

    // Construct line what the disk is using.
    vLineWithAngleCalculated[0] = flSectorRadius * vLineAngle[0];
    vLineWithAngleCalculated[1] = flSectorRadius * vLineAngle[1];
    vLineWithAngleCalculated[2] = vLineAngle[2];

    // Construct transposed disk position.
    vLineTransposedDisk[0] = Px;
    vLineTransposedDisk[1] = Py;
    vLineTransposedDisk[2] = 0.0;

    // Construct zero vector.
    static float vZeroVec[3];
    vZeroVec[0] = 0.0;
    vZeroVec[1] = 0.0;
    vZeroVec[2] = 0.0;

    // When the distance is <= the disk range => Intersecting
    return (ToolsCalculateLinePointShortestSquaredDistance(vZeroVec, vLineWithAngleCalculated, vLineTransposedDisk) <= flDiskRadius * flDiskRadius)
}

/**
 * @brief Calculate the distance between a line and a point.
 * @note Formula: x(t) = x_0 + t * u.
 *              x_0: original point
 *              u: the end point of the line.
 *
 * @param vLineOrigin               The origin point of a line.
 * @param vLineEnd                  The end point of a line.
 * @param vPoint                    Any point.
 * @return                          The shortest squared distance between two a line and a point.
 */
inline float ToolsCalculateLinePointShortestSquaredDistance(float vLineOrigin[3], float vLineEnd[3], float vPoint[3])
{
    // We need to calculate t-value, using formula below:
    // t = (x-x0)*u/|u|^2
    // x-x0 forms a vector, and then dot product the point, so that can calculate the t value.

    // Make vector.
    static float vLineVec[3];
    MakeVectorFromPoints(vLineOrigin, vLineEnd, vLineVec);

    // Calculate t-value
    float t = GetVectorDotProduct(vLineVec, vPoint) / GetVectorLength(vPoint, true);

    // Formula d = | x - ( x_0 + clamp(t, 0, 1) * u ) |
    // NOTE: x, x_0, u are all vectors.
    // We need to calculate from inside to outside.

    // Scale vector at first.
    ScaleVector(vPoint, clamp(t, 0.0, 1.0));

    // Calculate the vector about the line-origin and the point.
    static float vAddVectorTemp[3];
    AddVectors(vLineOrigin, vPoint, vAddVectorTemp);

    // Subtract the vector about the line end & the vector added what we calculated.
    static float vSubtractVectorTemp[3];
    SubtractVectors(vLineEnd, vAddVectorTemp, vSubtractVectorTemp);

    // Get end point.
    // We dont need to get its squared root, for optimization.
    return GetVectorLength(vSubtractVectorTemp, true);
}