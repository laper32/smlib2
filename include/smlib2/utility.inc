/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          utility.sp
 *  Description:   Utilities, used for storing non-classfied functions.
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

#if defined _smlib2_utility_included
#endinput
#endif
#define _smlib2_utility_included

methodmap UTIL {
    /**
     * @brief Remove the entity from a world after some delay.
     * 
     * @param entity            The entity index. 
     * @param flDelayTime       The number of seconds to kill an entity.
     */
    public static void RemoveEntity(int entity, float flDelayTime) {
        // Initialize flags char
        char sFlags[SMALL_LINE_LENGTH];
        FormatEx(sFlags, sizeof(sFlags), "OnUser1 !self:Kill::%f:1", flDelayTime);
        
        // Sets modified flags on the entity
        SetVariantString(sFlags);
        AcceptEntityInput(entity, "AddOutput");
        AcceptEntityInput(entity, "FireUser1");
    }

    /**
     * @brief Create a train entity.
     * 
     * @param sClassname        The classname string.
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sPath             The name of the first path_track in the train's path.
     * @param sSpeed            The maximum speed that this train can move.
     * @param sSound            (Optional) The sound path.
     * @param iFlags            (Optional) The bits with some flags.
     *
     * @return                  The entity index.                       
     */
    public static int CreateTrain(
        char[] sClassname,  float vPosition[3],     float vAngle[3],  char[] sPath,
        char[] sSpeed,      char[] sSound = "",     int iFlags = 0) {
        // Create a train entity
        int entity = CreateEntityByName("func_tracktrain"); 
        
        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));

            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValueVector(entity, "angles", vAngle); 
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValue(entity, "target", sPath);
            DispatchKeyValue(entity, "startspeed", sSpeed);
            DispatchKeyValue(entity, "speed", sSpeed);
            DispatchKeyValue(entity, "wheels", "256");         /// Make moving smoother
            DispatchKeyValue(entity, "bank", "20");            /// Make turning smoother
            DispatchKeyValue(entity, "orientationtype", "2");  /// Linear blend, adds some smoothness
            DispatchKeyValue(entity, "spawnflags", sFlags);  
            if (hasLength(sSound)) DispatchKeyValue(entity, "MoveSound", sSound);
            
            // Sets render mode
            UTIL.SetRenderColor(entity, Clr_A, 0);
            
            // Spawn the entity
            DispatchSpawn(entity);
        }

        // Return index on the success
        return entity;
    }

    /**
     * @brief Create a path entity.
     * 
     * @param sClassname        The classname string.
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sNextTarget       The next '_track' in the path.
     * @param iFlags            (Optional) The bits with some flags.
     *
     * @return                  The entity index.                       
     */
    public static int CreatePath(char[] sClassname, float vPosition[3], float vAngle[3], char[] sNextTarget, int iFlags = 0) {
        // Create a path entity
        int entity = CreateEntityByName("path_track");
        
        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));

            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValueVector(entity, "angles", vAngle); 
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValue(entity, "target", sNextTarget);
            DispatchKeyValue(entity, "spawnflags", sFlags); 
            
            // Spawn the entity
            DispatchSpawn(entity);

            // Activate the entity
            ActivateEntity(entity);  
        }
        
        // Return index on the success
        return entity;
    }
    
    /**
     * @brief Create a monster entity.
     * 
     * @param sClassname        The classname string.
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sModel            The model path.
     * @param iFlags            (Optional) The bits with some flags.
     *
     * @return                  The entity index.                         
     */
    public static int CreateMonster(char[] sClassname, float vPosition[3], float vAngle[3], char[] sModel, int iFlags = 0) {
        // Create a monster entity
        int entity = CreateEntityByName("monster_generic"); 
            
        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));

            // Dispatch main values of the entity
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "model", sModel); 
            DispatchKeyValue(entity, "spawnflags", sFlags); 

            // Spawn the entity
            DispatchSpawn(entity);
            
            // Remove blood to avoid missing effects
            SetEntProp(entity, Prop_Data, "m_bloodColor", -1);
        }
        
        // Return index on the success
        return entity;
    }

    /**
     * @brief Create a physics entity.
     * 
     * @param sClassname        The classname string.
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sModel            The model path.
     * @param iFlags            (Optional) The bits with some flags.
     *
     * @return                  The entity index.                       
     */
    public static int CreatePhysics(char[] sClassname, float vPosition[3], float vAngle[3], char[] sModel, int iFlags = 0) {
        // Create a prop_physics_multiplayer entity
        int entity = CreateEntityByName("prop_physics_multiplayer"); 

        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));
        
            // Dispatch main values of the entity
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValueVector(entity, "origin", vPosition);
            DispatchKeyValueVector(entity, "angles", vAngle); 
            DispatchKeyValue(entity, "model", sModel);
            DispatchKeyValue(entity, "spawnflags", sFlags);
            
            // Spawn the entity
            DispatchSpawn(entity);
        }
        
        // Return index on the success
        return entity;
    }

    /**
     * @brief Create a dynamic entity.
     * 
     * @param sClassname        The classname string.
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sModel            The model path.
     * @param sDefaultAnim      (Optional) The default animation.
     * @param bOverride         (Optional) True for models with physics, false for fully dynamic models.
     * @param bHoldAnim         (Optional) If set, the prop will not loop its animation, but hold the last frame.
     * @param bSolid            (Optional) If set, the prop will be solid.
     * @param iFlags            (Optional) The bits with some flags.
     *
     * @return                  The entity index.                       
     */
    public static int CreateDynamic(char[] sClassname,      float vPosition[3],         float vAngle[3], 
                                    char[] sModel,          char[] sDefaultAnim = "",   bool bOverride = true, 
                                    bool bHoldAnim = false, bool bSolid = false,        int iFlags = DYN_COLLISIONDISABLED
                                    ) {
        // Create a prop_dynamic_override entity
        int entity = CreateEntityByName(bOverride ? "prop_dynamic_override" : "prop_dynamic");

        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));

            // Dispatch main values of the entity
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "model", sModel);
            DispatchKeyValue(entity, "spawnflags", sFlags);
            DispatchKeyValue(entity, "solid", bSolid ? "1" : "0");
            DispatchKeyValue(entity, "HoldAnimation", bHoldAnim ? "1" : "0");
            if (hasLength(sDefaultAnim)) DispatchKeyValue(entity, "DefaultAnim", sDefaultAnim);
            
            // Spawn the entity
            DispatchSpawn(entity);
        }
        
        // Return index on the success
        return entity;
    }

    /**
     * @brief Create a projectile entity.
     * 
     * @param vPosition         The position to the spawn.
     * @param vAngle            The angle to the spawn.
     * @param sModel            (Optional) The model path.
     *
     * @return                  The entity index.                       
     */
    public static int CreateProjectile(float vPosition[3], float vAngle[3], char[] sModel = "") {
        // Create a static entity
        int entity = CreateEntityByName("hegrenade_projectile");

        // Validate entity
        if (entity != -1)
        {
            // Spawn the entity
            DispatchSpawn(entity);
            TeleportEntity(entity, vPosition, vAngle, NULL_VECTOR);
            
            // Sets model
            if (hasLength(sModel)) SetEntityModel(entity, sModel);
        }

        // Return index on the success
        return entity;
    }

    /**
     * @brief Create a stack of the smoke entity.
     * 
     * @param parent            (Optional) The parent index.
     * @param vPosition         (Optional) The position to the spawn.
     * @param vAngle            (Optional) The angle to the spawn.
     * @param sAttach           (Optional) The attachment name.
     * @param sSpreadBase       (Optional) The amount of random spread in the origins of the smoke particles when they're spawned.     
     * @param sSpreadSpeed      (Optional) The amount of random spread in the velocity of the smoke particles after they're spawned.
     * @param sSpeed            (Optional) The speed at which the smoke particles move after they're spawned.
     * @param sStartSize        (Optional) The size of the smoke particles when they're first emitted.
     * @param sEndSize          (Optional) The size of the smoke particles at the point they fade out completely.
     * @param sDensity          (Optional) The rate at which to emit smoke particles (i.e. particles to emit per second).
     * @param sLength           (Optional) The length of the smokestack. Lifetime of the smoke particles is derived from this & particle speed.
     * @param sTwist            (Optional) The amount, in degrees per second, that the smoke particles twist around the origin.
     * @param sColor            The color of the light. (RGB)
     * @param sTransparency     The amount of an alpha (0-255)
     * @param sSpriteName       The sprite path.
     * @param flRemoveTime      (Optional) The removing of the smoke.
     * @param flDurationTime    (Optional) The duration of the smoke.
     *
     * @return                  The entity index.
     */
    public static int CreateSmoke(  int parent = -1,            float vPosition[3] = NULL_VECTOR,   float vAngle[3] = NULL_VECTOR, 
                                    char[] sAttach = "",        char[] sSpreadBase = "100",         char[] sSpreadSpeed = "70", 
                                    char[] sSpeed = "80",       char[] sStartSize = "200",          char[] sEndSize = "2", 
                                    char[] sDensity = "30",     char[] sLength = "400",             char[] sTwist = "20", 
                                    char[] sColor,              char[] sTransparency,               char[] sSpriteName, 
                                    float flRemoveTime = 0.0,   float flDurationTime = 0.0) {
        // Create a smokestack entity
        int entity = CreateEntityByName("env_smokestack");

        // Validate entity
        if (entity != -1)
        {
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "BaseSpread", sSpreadBase);
            DispatchKeyValue(entity, "SpreadSpeed", sSpreadSpeed);
            DispatchKeyValue(entity, "Speed", sSpeed);
            DispatchKeyValue(entity, "StartSize", sStartSize);
            DispatchKeyValue(entity, "EndSize", sEndSize);
            DispatchKeyValue(entity, "Rate", sDensity);
            DispatchKeyValue(entity, "JetLength", sLength);
            DispatchKeyValue(entity, "Twist", sTwist); 
            DispatchKeyValue(entity, "RenderColor", sColor);
            DispatchKeyValue(entity, "RenderAmt", sTransparency); 
            DispatchKeyValue(entity, "SmokeMaterial", sSpriteName);
            
            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Activate the entity
            AcceptEntityInput(entity, "TurnOn");
            
            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator");
                AcceptEntityInput(entity, "SetParent", parent, entity);
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (strlen(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }

            // Validate duration
            if (flDurationTime > 0.0 && flRemoveTime > 0.0)
            {
                // Initialize flags char
                char sFlags[SMALL_LINE_LENGTH];
                FormatEx(sFlags, sizeof(sFlags), "OnUser2 !self:TurnOff::%f:1", flRemoveTime);
                
                // Sets modified flags on the entity
                SetVariantString(sFlags);
                AcceptEntityInput(entity, "AddOutput");
                AcceptEntityInput(entity, "FireUser2");
                
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
        }
        
        // Return on the success
        return entity;
    }
    
    /**
     * @brief Create a particle entity.
     * 
     * @param parent            (Optional) The parent index.
     * @param vPosition         (Optional) The origin of the spawn.
     * @param vAngle            (Optional) The angle to the spawn.
     * @param sAttach           (Optional) The attachment name.
     * @param sEffect           The particle name.
     * @param flDurationTime    (Optional) The duration of an effect.
     *
     * @return                  The entity index.
     */
    public static int CreateParticle(
        int parent = -1,        float vPosition[3] = NULL_VECTOR,   float vAngle[3] = NULL_VECTOR, 
        char[] sAttach = "",    char[] sEffect,                     float flDurationTime = 0.0) {
        // Create an attach particle entity
        int entity = CreateEntityByName("info_particle_system");
        
        // Validate entity
        if (entity != -1)
        {
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition);
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "start_active", "1");
            DispatchKeyValue(entity, "effect_name", sEffect);
            
            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator");
                AcceptEntityInput(entity, "SetParent", parent, entity);
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (strlen(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }
            
            // Activate the entity
            ActivateEntity(entity);
            AcceptEntityInput(entity, "Start");
            
            // Validate duration
            if (flDurationTime > 0.0)
            {
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
        }
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create an explosion entity.
     *
     * @param vPosition         The position to the spawn.
     * @param vAngle            (Optional) The angle to the spawn.
     * @param iFlags            (Optional) The bits with some flags.
     * @param sSpriteName       (Optional) The sprite path.
     * @param flDamage          (Optional) The amount of damage done by the explosion.
     * @param flRadius          (Optional) If set, the radius in which the explosion damages entities. If unset, the radius will be based on the magnitude.
     * @param sWeapon           (Optional) The classname defines the type of entity.
     * @param attacker          (Optional) The attacker index.
     * @param inflictor         (Optional) The inflictor index.
     * @param sIgnore           (Optional) Do not harm or affect the named entity.
     *
     * @return                  The entity index.
     */
    public static int CreateExplosion(
        float vPosition[3]/*,                                       float vAngle[3] = NULL_VECTOR*/,    int iFlags = 0, 
        char[] sSpriteName = "materials/sprites/xfireball3.vmt",    float flDamage = 0.0,               float flRadius = 0.0, 
        char[] sWeapon = "",                                        int attacker = -1,                  int inflictor = -1, 
        char[] sIgnore = "") {
        // Create an explosion entity
        int entity = CreateEntityByName("env_explosion");

        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));
            
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition);
            ///DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "spawnflags", sFlags);
            DispatchKeyValue(entity, "fireballsprite", sSpriteName);
            if (!(iFlags & EXP_NODAMAGE))
            {
                DispatchKeyValue(entity, "classname", sWeapon);
                IntToString(RoundToNearest(flDamage), sFlags, sizeof(sFlags));
                DispatchKeyValue(entity, "iMagnitude", sFlags);
                IntToString(RoundToNearest(flRadius), sFlags, sizeof(sFlags));
                DispatchKeyValue(entity, "iRadiusOverride", sFlags);
                if (hasLength(sIgnore)) DispatchKeyValue(entity, "ignoredEntity", sIgnore);
            }
            
            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Validate attacker
            if (attacker != -1)
            {
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", attacker);
            }
                
            // Validate inflictor
            if (inflictor != -1)
            {
                SetEntPropEnt(entity, Prop_Data, "m_hInflictor", inflictor);
            }
            
            // Activate the entity
            AcceptEntityInput(entity, "Explode");

            // Remove the entity from the world
            AcceptEntityInput(entity, "Kill");
        }
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create a point hurt entity.
     * 
     * @param parent            (Optional) The parent index. 
     * @param vPosition         (Optional) The origin of the spawn.
     * @param attacker          The attacker index.
     * @param flDamage          The amount of damage inflicted.
     * @param flRadius          The radius in which the hurt damages entities.
     * @param iBits             (Optional) The ditfield of damage types. 
     * @param weaponID          (Optional) The weapon index or -1 for unspecified.
     * @param sAttach           (Optional) The attachment name.
     *
     * @return                  The entity index.
     */
    public static int CreateDamage(
        int parent = -1,    float vPosition[3] = NULL_VECTOR,   int attacker,       float flDamage, 
        float flRadius,     int iBits = DMG_GENERIC,            int weaponID = -1,  char[] sAttach = "") {
        // Create a hurt entity
        int entity = CreateEntityByName("point_hurt");           

        // Validate entity
        if (entity != -1)
        {
            // Initialize variables
            char sDamage[SMALL_LINE_LENGTH];
            
            /*
            * The specified amount of damage will be halved. 
            * Consider multiplying your amount of damage by 2 and using it as the Value.
            */
            
            // Dispatch main values of the entity
            IntToString(RoundToNearest(flDamage) * 2, sDamage, sizeof(sDamage));
            DispatchKeyValue(entity, "Damage", sDamage);
            IntToString(iBits, sDamage, sizeof(sDamage));
            DispatchKeyValue(entity, "DamageType", sDamage);
            DispatchKeyValueFloat(entity, "Radius", flRadius);
            
            // Spawn the entity into the world
            DispatchSpawn(entity);      
            TeleportEntity(entity, vPosition, NULL_VECTOR, NULL_VECTOR);
            
            // Sets custom weapon id
            SetEntProp(entity, Prop_Data, "m_iHammerID", weaponID);

            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator"); 
                AcceptEntityInput(entity, "SetParent", parent, entity); 
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (hasLength(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }

            // Activate the entity
            AcceptEntityInput(entity, "Hurt", attacker);  
            
            // Remove the entity from the world
            AcceptEntityInput(entity, "Kill"); 
        }   
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create a sprite entity.
     * 
     * @param parent            (Optional) The parent index. 
     * @param vPosition         (Optional) The origin of the spawn.
     * @param vAngle            (Optional) The angle to the spawn.
     * @param sAttach           (Optional) The attachment name.
     * @param sSprite           The sprite path.
     * @param sScale            The scale multiplier of the sprite.
     * @param sRender           Set a non-standard rendering mode on this entity.
     * @param flDurationTime    (Optional) The duration of the beam.
     *
     * @return                  The entity index.
     */
    public static int CreateSprite(
        int parent = -1,    float vPosition[3] = NULL_VECTOR,   float vAngle[3] = NULL_VECTOR,  char[] sAttach = "", 
        char[] sSprite,     char[] sScale,                      char[] sRender,                 float flDurationTime = 0.0) {
        // Create a sprite entity
        int entity = CreateEntityByName("env_sprite");
        
        // If entity isn't valid, then skip
        if (entity != -1)
        {
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition);
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "model", sSprite);
            DispatchKeyValue(entity, "scale", sScale);
            DispatchKeyValue(entity, "rendermode", sRender);
            
            // Spawn the entity into the world
            DispatchSpawn(entity);
            
            // Activate the entity
            ActivateEntity(entity);
            
            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator"); 
                AcceptEntityInput(entity, "SetParent", parent, entity); 
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (hasLength(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }
            
            // Validate duration
            if (flDurationTime > 0.0)
            {
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
        }

        // Return on the success
        return entity;
    }

    /**
     * @brief Create a material controlller entity.
     * 
     * @param parent            The parent index. 
     * @param sSprite           The sprite path.
     * @param sVar              The name of the shader parameter you want to modify.
     *
     * @return                  The entity index.
     */
    public static int CreateSpriteController(int parent, char[] sSprite, char[] sVar) {
        // Create a material controller entity
        int entity = CreateEntityByName("material_modify_control");
        
        // If entity isn't valid, then skip
        if (entity != -1)
        {
            // Dispatch main values of the entity
            DispatchKeyValue(entity, "materialName", sSprite);
            DispatchKeyValue(entity, "materialVar", sVar);
            
            // Spawn the entity 
            DispatchSpawn(entity);

            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator");
                AcceptEntityInput(entity, "SetParent", parent, entity);
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
            }
        }
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create a tesla entity.
     * 
     * @param parent            (Optional) The parent index. 
     * @param vPosition         (Optional) The origin of the spawn.
     * @param vAngle            (Optional) The angle to the spawn.
     * @param sAttach           (Optional) The attachment name.
     * @param sRadius           (Optional) The radius around the origin to find a point to strike with a tesla lightning beam.
     * @param sSound            (Optional) The sound to be played whenever lightning is created.
     * @param sCountMin         (Optional) The minimum number of tesla lightning beams to create when creating an arc.
     * @param sCountMax         (Optional) The maximum number of tesla lightning beams to create when creating an arc.
     * @param sTextureName      (Optional) The material to use for the tesla lightning beams.
     * @param sColor            (Optional) The beam color.
     * @param sThickMin         (Optional) The minimum width of the tesla lightning beams.
     * @param sThinkMax         (Optional) The maximum width of the tesla lightning beams.
     * @param sLifeMin          (Optional) The minimum lifetime of the tesla lightning beams.
     * @param sLifeMax          (Optional) The maximum lifetime of the tesla lightning beams.
     * @param sIntervalMin      (Optional) The minimum time delay between random arcing.
     * @param sIntervalMax      (Optional) The maximum time delay between random arcing.
     * @param flDurationTime    (Optional) The duration of the beam.
     *
     * @return                  The entity index.
     */
    public static int CreateTesla(
        int parent = -1,                float vPosition[3] = NULL_VECTOR,   float vAngle[3] = NULL_VECTOR,  
        char[] sAttach = "",            char[] sRadius = "500.0",           char[] sSound = "DoSpark",
        char[] sCountMin = "42",        char[] sCountMax = "62",            char[] sTextureName = "materials/sprites/physbeam.vmt", 
        char[] sColor = "255 255 255",  char[] sThickMin = "10.0",          char[] sThickMax = "11.0", 
        char[] sLifeMin = "0.3",        char[] sLifeMax = "0.3",            char[] sIntervalMin = "0.1", 
        char[] sIntervalMax = "0.2",    float flDurationTime = 0.0) {
        // Create a tesla entity
        int entity = CreateEntityByName("point_tesla");

        // Validate entity
        if (entity != -1)
        {
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition);
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValue(entity, "m_flRadius", sRadius);  
            DispatchKeyValue(entity, "m_SoundName", sSound);  
            DispatchKeyValue(entity, "beamcount_min", sCountMin);  
            DispatchKeyValue(entity, "beamcount_max", sCountMax);
            DispatchKeyValue(entity, "texture", sTextureName);  
            DispatchKeyValue(entity, "m_Color", sColor);  
            DispatchKeyValue(entity, "thick_min", sThickMin);     
            DispatchKeyValue(entity, "thick_max", sThickMax);     
            DispatchKeyValue(entity, "lifetime_min", sLifeMin);  
            DispatchKeyValue(entity, "lifetime_max", sLifeMax);  
            DispatchKeyValue(entity, "interval_min", sIntervalMin);     
            DispatchKeyValue(entity, "interval_max", sIntervalMax);   

            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Activate the entity
            ActivateEntity(entity);
            AcceptEntityInput(entity, "TurnOn");     
            AcceptEntityInput(entity, "DoSpark");    

            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator"); 
                AcceptEntityInput(entity, "SetParent", parent, entity); 
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (hasLength(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }
            
            // Validate duration
            if (flDurationTime > 0.0)
            {
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
        }

        // Return on the success
        return entity;
    }

    /**
     * @brief Create a shooter entity.
     * 
     * @param parent            The parent index. 
     * @param sAttach           The attachment bone of the entity parent.
     * @param sRender           (Optional) Used to set a non-standard rendering mode on this entity. See also 'FX Amount' and 'FX Color'. 
     * @param sSound            (Optional) Material Sound. (-1: None | 0: Glass | 1: Wood | 2: Metal | 3: Flesh | 4: Concrete)
     * @param iSkin             (Optional) Some models have multiple skins.
     * @param sTextureName      Thing to shoot out. Can be a .mdl (model) or a .vmt (material/sprite).
     * @param vAngle            (Optional) The direction the gibs will fly. 
     * @param vGibAngle         (Optional) The orientation of the spawned gibs. 
     * @param iGibs             The number of gibs - Total number of gibs to shoot each time it's activated
     * @param flDelay           The delay (in seconds) between shooting each gib. If 0, all gibs shoot at once.
     * @param flVelocity        The speed of the fired gibs.
     * @param flVariance        How much variance in the direction gibs are fired.
     * @param flLife            Time in seconds for gibs to live +/- 5%. 
     * @param flDurationTime    The duration of the gibs.
     *
     * @return                  The entity index.
     */
    public static int CreateShooter(
        int parent,     char[] sAttach,         char[] sRender = "5",           char[] sSound = "-1", 
        int iSkin = 0,  char[] sTextureName,    float vAngle[3] = NULL_VECTOR,  float vGibAngle[3] = NULL_VECTOR, 
        float iGibs,    float flDelay,          float flVelocity,               float flVariance, 
        float flLife,   float flDurationTime) {
        // Create a shooter entity
        int entity = CreateEntityByName("env_shooter");

        // Validate entity
        if (entity != -1)
        {
            // Initialize skin char
            char sSkin[SMALL_LINE_LENGTH];
            IntToString(iSkin, sSkin, sizeof(sSkin));
            
            // Dispatch main values of the entity
            //DispatchKeyValueVector(entity, "origin", vPosition);
            DispatchKeyValueVector(entity, "angles", vAngle);
            DispatchKeyValueVector(entity, "gibangles", vGibAngle);
            DispatchKeyValue(entity, "rendermode", sRender);
            ///DispatchKeyValue(entity, "rendercolor", sColor);
            ///DispatchKeyValue(entity, "renderfx", sRenderFX); 
            DispatchKeyValue(entity, "shootsounds", sSound);
            DispatchKeyValue(entity, "shootmodel", sTextureName);
            DispatchKeyValue(entity, "skin", sSkin);
            DispatchKeyValueFloat(entity, "m_iGibs", iGibs);
            DispatchKeyValueFloat(entity, "delay", flDelay);
            DispatchKeyValueFloat(entity, "m_flVelocity", flVelocity);
            DispatchKeyValueFloat(entity, "m_flVariance", flVariance);
            DispatchKeyValueFloat(entity, "m_flGibLife", flLife);

            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Activate the entity
            ActivateEntity(entity);  
            AcceptEntityInput(entity, "Shoot");

            // Sets parent to the entity
            SetVariantString("!activator"); 
            AcceptEntityInput(entity, "SetParent", parent, entity); 
            SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);

            // Sets attachment to the entity
            if (hasLength(sAttach))
            { 
                SetVariantString(sAttach); 
                AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
            }

            // Kill entity after delay
            UTIL.RemoveEntity(entity, flDurationTime);
        }
        
        // Return on the success
        return entity;
    }  

    /**
     * @brief Create a beam entity.
     * 
     * @param vStartPosition    The start position of the beam.    
     * @param vEndPosition      The end position of the beam.    
     * @param sDamage           (Optional) How much damage this beam does per second to things it hits when it is continually on, or instantaneously if it strikes. For continuous damage, the value should be greater than 10 or it may not work.
     * @param sFrame            (Optional) The framerate at which the beam texture should animate, if it has multiple frames.
     * @param sWidth            (Optional) The pixel width of the beam. Range: 1 to MAX_BEAM_WIDTH.
     * @param sRenderFX         (Optional) The several GoldSrc-era visibility modes which change the way the entity is rendered, typically by fading it in and out.
     * @param sType             (Optional) If you want the beam to fire an output when touched by entities, choose the entity type here. (0: Not a tripwire | 1: Player Only | 2: NPC Only | 3: Player or NPC | 4: Player or NPC or Physprop)
     * @param sRate             (Optional) The framerate at which the beam texture should animate, if it has multiple frames.
     * @param sDecalName        (Optional) The decal to be applied at the end of the beam
     * @param sScroll           (Optional) The rate at which the beam texture should scroll along the beam. Range: 0 to MAX_BEAM_SCROLLSPEED.
     * @param sScale            (Optional) The float value to multiply sprite color by when running in HDR mode.
     * @param sTextureName      (Optional) The material used to draw the beam.
     * @param sLife             (Optional) The amount of time before the beam dies. Setting to zero will make the beam stay forever.
     * @param sStrike           (Optional) The refire time between random strikes of the beam. Only used if the 'Random Strike' spawnflag is set.
     * @param iFlags            (Optional) The bits with some flags.
     * @param sAmplitude        (Optional) The amount of noise in the beam. 0 is a perfectly straight beam. Range: 0 to MAX_BEAM_NOISEAMPLITUDE.
     * @param sRadius           (Optional) If the LightningStart and/or LightningEnd values are omitted, this radius determines the area within which the endpoints will randomly strike. A new random position will be appointed for every strike.
     * @param sRenderAMT        (Optional) The beam brightness. Useless when set to 0.
     * @param sColor            The beam color.
     * @param flDelayTime       The delay after the touch.
     * @param flDurationTime    The duration of the beam.
     * @param sName             The name of the beam.
     *
     * @return                  The entity index.
     */
    public static int CreateBeam(
        float vStartPosition[3],        float vEndPosition[3],      char[] sDamage = "0",   char[] sFrame = "0", 
        char[] sWidth = "4.0",          char[] sRenderFX = "0",     char[] sType = "3",     char[] sRate = "0", 
        char[] sDecalName = "Bigshot",  char[] sScroll = "35",      char[] sScale = "1.0",  char[] sTextureName = "materials/sprites/purplelaser1.vmt", 
        char[] sLife = "0",             char[] sStrike = "1",       int iFlags = 0,         char[] sAmplitude = "0", 
        char[] sRadius = "256",         char[] sRenderAMT = "100",  char[] sColor,          float flDelayTime, 
        float flDurationTime,           char[] sName) {
        // Create a beam entity
        int entity = CreateEntityByName("env_beam");

        // Validate entity
        if (entity != -1)
        {
            // Initialize name char
            char sClassname[SMALL_LINE_LENGTH];
            FormatEx(sClassname, sizeof(sClassname), "%s%i", sName, entity);

            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));
            
            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vStartPosition);
            DispatchKeyValue(entity, "targetname", sClassname);
            DispatchKeyValue(entity, "damage", sDamage);
            DispatchKeyValue(entity, "framestart", sFrame);
            DispatchKeyValue(entity, "BoltWidth", sWidth);
            DispatchKeyValue(entity, "renderfx", sRenderFX);
            DispatchKeyValue(entity, "TouchType", sType);
            DispatchKeyValue(entity, "framerate", sRate);
            DispatchKeyValue(entity, "decalname", sDecalName);
            DispatchKeyValue(entity, "TextureScroll", sScroll);
            DispatchKeyValue(entity, "HDRColorScale", sScale);
            DispatchKeyValue(entity, "texture", sTextureName);
            DispatchKeyValue(entity, "life", sLife); 
            DispatchKeyValue(entity, "StrikeTime", sStrike); 
            DispatchKeyValue(entity, "LightningStart", sClassname);
            DispatchKeyValue(entity, "spawnflags", sFlags); 
            DispatchKeyValue(entity, "NoiseAmplitude", sAmplitude); 
            DispatchKeyValue(entity, "Radius", sRadius);
            DispatchKeyValue(entity, "renderamt", sRenderAMT);
            DispatchKeyValue(entity, "rendercolor", sColor);

            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Activate the entity
            AcceptEntityInput(entity, "TurnOff");
            AcceptEntityInput(entity, "TurnOn");
            
            // Sets model
            SetEntityModel(entity, sTextureName);
            
            // Sets size
            float flWidth = StringToFloat(sWidth);
            SetEntPropFloat(entity, Prop_Data, "m_fWidth", flWidth);
            SetEntPropFloat(entity, Prop_Data, "m_fEndWidth", flWidth);
            SetEntPropVector(entity, Prop_Data, "m_vecEndPos", vEndPosition);

            // Validate duration
            if (flDurationTime > 0.0)
            {
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
            
            // Validate delay
            if (flDelayTime > 0.0)
            {
                // Initialize time char
                FormatEx(sFlags, sizeof(sFlags), "OnUser2 !self:TurnOff::%f:1", flDelayTime - 0.001);
                
                // Sets modified flags on the entity
                SetVariantString(sFlags);
                AcceptEntityInput(entity, "AddOutput");
                
                // Initialize time char
                FormatEx(sFlags, sizeof(sFlags), "OnUser3 !self:TurnOn::%f:1", flDelayTime);
                
                // Sets modified flags on the entity
                SetVariantString(sFlags);
                AcceptEntityInput(entity, "AddOutput");
                
                // Execute touch hook tweak
                SetVariantString("OnTouchedByEntity !self:FireUser2::0.0:-1");
                AcceptEntityInput(entity, "AddOutput");
                SetVariantString("OnTouchedByEntity !self:FireUser3::0.0:-1");
                AcceptEntityInput(entity, "AddOutput");
            }
        }
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create a light dynamic entity.
     * 
     * @param parent            (Optional) The parent index. 
     * @param vPosition         (Optional) The origin of the spawn.
     * @param sAttach           (Optional) The attachment name.
     * @param sInnerCone        (Optional) The inner (bright) angle.
     * @param sCone             (Optional) The outer (fading) angle.
     * @param sBrightness       (Optional) The intensity of the spotlight.
     * @param sPitch            (Optional) Used instead of Pitch Yaw Roll's value for reasons unknown.
     * @param sStyle            (Optional) The lightstyle (see Appearance field for possible values).
     * @param iFlags            (Optional) The bits with some flags.
     * @param sColor            The color of the light. (RGBA)
     * @param flDistance        The distance of the light.
     * @param flRadius          The radius of the light.
     * @param flDurationTime    (Optional) The duration of the light.
     *
     * @return                  The entity index.
     */
    public static int CreateLight(
        int parent = -1,        float vPosition[3] = NULL_VECTOR,   char[] sAttach = "",    char[] sInnerCone = "0", 
        char[] sCone = "80",    char[] sBrightness = "1",           char[] sPitch = "90",   char[] sStyle = "1", 
        int iFlags = 0,         char[] sColor,                      float flDistance,       float flRadius, 
        float flDurationTime = 0.0) {
        // Create an light_dynamic entity
        int entity = CreateEntityByName("light_dynamic");

        // Validate entity
        if (entity != -1)
        {
            // Initialize flag char
            char sFlags[SMALL_LINE_LENGTH];
            IntToString(iFlags, sFlags, sizeof(sFlags));

            // Dispatch main values of the entity
            DispatchKeyValueVector(entity, "origin", vPosition); 
            DispatchKeyValue(entity, "spawnflags", sFlags);
            DispatchKeyValue(entity, "inner_cone", sInnerCone);
            DispatchKeyValue(entity, "cone", sCone);
            DispatchKeyValue(entity, "brightness", sBrightness);
            DispatchKeyValue(entity, "pitch", sPitch);
            DispatchKeyValue(entity, "style", sStyle);
            DispatchKeyValue(entity, "_light", sColor);
            DispatchKeyValueFloat(entity, "distance", flDistance);
            DispatchKeyValueFloat(entity, "spotlight_radius", flRadius);

            // Spawn the entity into the world
            DispatchSpawn(entity);

            // Activate the entity
            AcceptEntityInput(entity, "TurnOn");

            // Validate parent
            if (parent != -1)
            {
                // Sets parent to the entity
                SetVariantString("!activator"); 
                AcceptEntityInput(entity, "SetParent", parent, entity); 
                SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", parent);
                
                // Sets attachment to the entity
                if (hasLength(sAttach))
                { 
                    SetVariantString(sAttach); 
                    AcceptEntityInput(entity, "SetParentAttachment", parent, entity);
                }
            }
            
            // Validate duration
            if (flDurationTime > 0.0)
            {
                // Kill entity after delay
                UTIL.RemoveEntity(entity, flDurationTime);
            }
        }
        
        // Return on the success
        return entity;
    }

    /**
     * @brief Create a speaker entity.
     *
     * @param vPosition         The origin of the spawn.
     * @param vAngle            The angle of the spawn.
     * @param iSource           The source entity index.
     * @param flRemoveTime      About how many seconds delay to remove.
     *
     * @return                  The entity index.
     */
    public static int SpawnSpeaker(float vPosition[3], float vAngle[3], int iSource, float flRemoveTime = 0.1) {
        int entity = CreateEntityByName("info_target");

        if (entity != -1)
        {
            DispatchSpawn(entity);

            TeleportEntity(entity, vPosition, vAngle, NULL_VECTOR);

            SetVariantString("!activator");
            AcceptEntityInput(entity, "SetParent", iSource, entity, 0);

            if (flRemoveTime > 0.0)
            {
                UTIL.RemoveEntity(entity, flRemoveTime);
            }
        }

        return entity;
    }

    /**
     * @brief Sets the glowing on the entity.
     * 
     * @param entity            The entity index.
     * @param enableState       Sets to true to enable glowing, false to disable.
     * @param iType             (Optional) The type of the glowing.
     * @param iRed              (Optional) Amount of a red (0-255)
     * @param iGreen            (Optional) Amount of a green (0-255)
     * @param iBlue             (Optional) Amount of a blue (0-255)
     * @param iAlpha            (Optional) Amount of an alpha (0-255)
     */
    public static void CreateGlowing(
        int entity,         bool enableState,   int iType = 0, int iRed = 255, 
        int iGreen = 255,   int iBlue = 255,    int iAlpha = 255) {
        // Validate offset
        static int iGlowOffset;
        if (!iGlowOffset && (iGlowOffset = GetEntSendPropOffs(entity, "m_clrGlow")) == -1)
        {
            return;
        }
        
        // Sets glowing mode
        SetEntProp(entity, Prop_Send, "m_bShouldGlow", enableState, true);
        SetEntProp(entity, Prop_Send, "m_nGlowStyle", iType);
        SetEntPropFloat(entity, Prop_Send, "m_flGlowMaxDist", 100000.0);
        
        // Sets alpha and colors
        SetEntData(entity, iGlowOffset + 0, iRed,   _, true);
        SetEntData(entity, iGlowOffset + 1, iGreen, _, true);
        SetEntData(entity, iGlowOffset + 2, iBlue,  _, true);
        SetEntData(entity, iGlowOffset + 3, iAlpha, _, true);
    }

    /**
     * @brief Sets the render of a entity.
     *
     * @param entity            The entity index.
     * @param color             The offset index.
     * @param iRender           The render amount.
     */
    public static void SetRenderColor(int entity, RenderingColorType color, int iRender) {
        // Validate offset
        static int iRenderOffset;
        if (!iRenderOffset && (iRenderOffset = GetEntSendPropOffs(entity, "m_clrRender")) == -1)
        {
            return;
        }

        // Sets render of the entity
        SetEntProp(entity, Prop_Send, "m_nRenderMode", RENDER_TRANSALPHA);
        SetEntData(entity, iRenderOffset + view_as<int>(color), iRender, 1, true);
    }

    /**
     * @brief Gets the render of a entity.
     *
     * @param entity            The entity index.
     * @param color             The offset index.
     * @return                  The render amount.
     */
    public static int GetRenderColor(int entity, RenderingColorType color) {
        // Validate offset
        static int iRenderOffset;
        if (!iRenderOffset && (iRenderOffset = GetEntSendPropOffs(entity, "m_clrRender")) == -1)
        {
            return 255;
        }

        // Gets render of the entity
        return GetEntData(entity, iRenderOffset + view_as<int>(color), 1);
    }

    /**
     * @brief Create the tracer to a entity. (*not client)
     *
     * @param parent            The parent index.
     * @param sAttach           The attachment name.
     * @param sEffect           The effect name.
     * @param vBullet           The position of a bullet hit.
     * @param flDurationTime    The duration of life.
     */
    public static void CreateTracer(int parent, char[] sAttach, char[] sEffect, float vBullet[3], float flDurationTime) {
        // Validate name
        if (!hasLength(sEffect))
        {
            return;
        }
        
        #define StaticSrt  0
        #define StaticEnd  1
                                    /** Regards to Phoenix **/
                                /** Dont ask me how it works ;) **/


        // Initialize name char
        char sClassname[SMALL_LINE_LENGTH];

        // Create an attach particle entity
        static int entity[2];
        entity[StaticSrt] = CreateEntityByName("info_particle_system");
        entity[StaticEnd] = CreateEntityByName("info_particle_system");

        // If entity isn't valid, then skip
        if (entity[StaticEnd] != -1) /// Check the last entity ;)
        {
            // Gets the entity angle
            float vAngle[3], vEmpty[3];
            GetEntPropVector(parent, Prop_Data, "m_angAbsRotation", vAngle); 
            
            // Teleport the entity
            TeleportEntity(entity[StaticEnd], vBullet, vAngle, NULL_VECTOR);
            
            // Dispatch main values of the entity
            FormatEx(sClassname, sizeof(sClassname), "particle%d",  entity[StaticSrt]);
            DispatchKeyValue(entity[StaticSrt], "targetname", sClassname);
            DispatchKeyValue(entity[StaticEnd], "effect_name", sEffect);
            DispatchKeyValue(entity[StaticEnd], "cpoint1", sClassname);
            
            // Spawn the entity into the world
            DispatchSpawn(entity[StaticEnd]);
            
            // Sets owner to the entity 
            SetEntPropEnt(entity[StaticEnd], Prop_Data, "m_hOwnerEntity", parent);

            // Teleport the entity
            TeleportEntity(entity[StaticSrt], NULL_VECTOR, vAngle, NULL_VECTOR);

            // Sets parent to the entity
            SetVariantString("!activator");
            AcceptEntityInput(entity[StaticSrt], "SetParent", parent, entity[StaticSrt]);
            
            // Sets attachment to the entity
            SetVariantString(sAttach);
            AcceptEntityInput(entity[StaticSrt], "SetParentAttachment",  entity[StaticSrt], entity[StaticSrt]);

            // Teleport the entity
            TeleportEntity(entity[StaticSrt], vEmpty, NULL_VECTOR, NULL_VECTOR);

            /*______________________________________________________________________________*/
            
            // Activate the entity
            ActivateEntity(entity[StaticEnd]);
            AcceptEntityInput(entity[StaticEnd], "Start");

            // Kill entities after delay
            UTIL.RemoveEntity(entity[StaticEnd], flDurationTime);
            UTIL.RemoveEntity(entity[StaticSrt], flDurationTime);
        }
    }

    /**
     * @brief Push a client with specific parameters.
     * 
     * @param client            The client index.
     * @param vPosition         The force origin.
     * @param vOrigin           The client origin.
     * @param flDistance        The distance amount.
     * @param flForce           The force amount.
     * @param flRadius          The radius amount.
     */
    public static void CreatePhysForce(int client, float vPosition[3], float vOrigin[3], float flDistance, float flForce, float flRadius)
    {
        // Calculate the velocity vector
        float vVelocity[3];
        MakeVectorFromPoints(vPosition, vOrigin, vVelocity);
        
        // Calculate the push power
        float flKnockBack = flForce * (1.0 - (flDistance / flRadius));

        // Normalize the vector (equal magnitude at varying distances)
        NormalizeVector(vVelocity, vVelocity);

        // Apply the magnitude by scaling the vector
        ScaleVector(vVelocity, SquareRoot((flKnockBack * flKnockBack) / ((vVelocity[0] * vVelocity[0]) + (vVelocity[1] * vVelocity[1]) + (vVelocity[2] * vVelocity[2])))); vVelocity[2] * flForce;

        // Push the client
        TeleportEntity(client, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }

    /**
     * Precache models and also adding them into the downloading table.
     *
     * Note: This is considered as a more general case, for all Source Engine games.
     * 
     * @param sModel            The model path.
     *
     * @return                  The model index.
     */
    public static int PrecacheModel(char[] sModel)
    {
        // Precache main model
        int iModel = PrecacheModel(sModel, true);
        
        // Adding main model to the download list
        AddFileToDownloadsTable(sModel);

        // Initialize path char
        char sPath[PLATFORM_MAX_PATH];
        static const char sType[3][SMALL_LINE_LENGTH] = { ".dx90.vtx", ".phy", ".vvd" };

        // i = type index
        for (int i = 0; i < sizeof(sType); i++)
        {
            // Adding other parts to download list
            FormatEx(sPath, sizeof(sPath), "%s", sModel);
            ReplaceString(sPath, sizeof(sPath), ".mdl", sType[i]);
            if (!FileExists(sPath)) continue;
            AddFileToDownloadsTable(sPath);
        }
        
        // Return model index
        return iModel;
    }

    /**
     * Precache decals and also adding them into the downloading table.
     *
     * Note: This is considered as a more general case, for all Source Engine games.
     * 
     * @param sDecal            The decal path.
     *
     * @return                  The decal index.
     */
    public static int PrecacheDecal(char[] sDecal)
    {
        // Precache main decal
        int iDecal = PrecacheDecal(sDecal, true);
        
        // Adding main decal to the download list
        AddFileToDownloadsTable(sDecal);

        // Initialize path char
        char sPath[PLATFORM_MAX_PATH];
        
        // Adding other parts to download list
        FormatEx(sPath, sizeof(sPath), "%s", sDecal);
        ReplaceString(sPath, sizeof(sPath), ".vtf", ".vmt");
        if (FileExists(sPath)) AddFileToDownloadsTable(sPath);
        
        // Return decal index
        return iDecal;
    }

    /**
     * Precache sounds and also adding them into the downloading table.
     * 
     * Note: This is considered as a more general case, for all Source Engine games.
     *
     * @param soundPath         The sound path.
     */
    public static void PrecacheSound(char[] sSound)
    {
        // Initialize path char
        char sPath[PLATFORM_MAX_PATH];
        
        // Adding sound to the download list
        FormatEx(sPath, sizeof(sPath), "sound/%s", sSound);
        if (!FileExists(sPath)) return;
        AddFileToDownloadsTable(sPath);
        
        // Initialize the table index
        static int table = INVALID_STRING_TABLE;

        // Validate table
        if (table == INVALID_STRING_TABLE)
        {
            // Searches for a string table
            table = FindStringTable("soundprecache");
        }

        // Precache sound
        bool bSave = LockStringTables(false);
        FormatEx(sPath, sizeof(sPath), "*/%s", sSound);
        AddToStringTable(table, sPath);
        LockStringTables(bSave);
    }

    /**
     * @brief Gets the velocity and it's angle from the two vectors.
     * 
     * @param vStartPosition    The starting position.
     * @param vEndPosition      The ending position.     
     * @param vAngle            The calculated angle's vector output.
     * @param vVelocity         The calculated velocity's vector output.
     * @param flSpeedScale      (Optional) The speed scale value.
     * @param verticalScale     (Optional) Set to true for reversing vertical velocity's value, false to reset.
     */
    public static void GetVelocityByAim(
        float vStartPosition[3],    float vEndPosition[3],      float vAngle[3], 
        float vVelocity[3],         float flSpeedScale = 1.0,   bool verticalScale = false) {
        // Calculate the velocity's vector
        MakeVectorFromPoints(vStartPosition, vEndPosition, vVelocity);
        
        // Sets vertical scale
        vVelocity[2] = verticalScale ? -vVelocity[2] : 0.0;

        // Gets the vector's angle
        GetVectorAngles(vVelocity, vAngle);
        
        // Reset angle vectors
        vAngle[0] = vAngle[2] = 0.0;

        // Normalize the vector (equal magnitude at varying distances)
        NormalizeVector(vVelocity, vVelocity);

        // Apply the magnitude by scaling the vector
        ScaleVector(vVelocity, flSpeedScale);
    }
}

/**
 * @brief Validate that the entity is can see the target.
 *
 * @note Check 3 spots, or else when standing right next to someone looking at their eyes, 
 *       the angle will be too great to see their center. Thank to Pelipoika.
 *
 * @note This should be a validation that whether on same plane, not can see each other.
 * 		 To check whether can need, an intersection test is required.
 *
 * @param entity            The entity index. 
 * @param target            The target index. 
 * @param vPosition         The entity position.
 * @param filter            The function to use as a filter.
 *
 * @return                  True of false.        
 **/
inline bool UTIL_IsOnSamePlane(int entity, int target, float vPosition[3], TraceEntityFilter filter)
{
    // Initialize vectors
    float vOrigin[3], vMaxs[3];

    // Gets the target's bottom position
    GetEntPropVector(target, Prop_Data, "m_vecAbsOrigin", vOrigin);
    
    // Validate a bot point
    if (UTIL_TraceRay(entity, target, vPosition, vOrigin, filter))
    {
        return true;
    }
    
    /*___________________________________________________________________________________________________________*/

    // Gets the target's center position
    GetClientMaxs(target, vMaxs); vOrigin[2] += vMaxs[2] / 2;
    
    // Validate a center point
    if (UTIL_TraceRay(entity, target, vPosition, vOrigin, filter))
    {
        return true;
    }
    
    /*___________________________________________________________________________________________________________*/

    // Gets the target's eye position
    GetClientEyePosition(target, vOrigin);
    
    // Validate a top point
    if (UTIL_TraceRay(entity, target, vPosition, vOrigin, filter))
    {
        return true;
    }
        
    // Return on unsuccess
    return false;
}

/**
 * @brief Gets the End of the point what the entity traces to.
 *
 * @param entity            The entity index.
 * @param vPosition         The position of the ray.
 *
 * @return                  T/F.
 */
inline bool UTIL_GetTraceEndPoint(int entity, float vPosition[3])
{
    float vAngles[3], vOrigin[3];
    ToolsGetAbsOrigin(entity, vOrigin); // player's eye position
    ToolsGetAbsAngles(entity, vAngles); // plauer's eye angle

    // trace it to the end point
    Handle trace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, PlayersFilter); 
    
    bool bHit;
    if (TR_DidHit(trace))
    {
        TR_GetEndPosition(vPosition, trace);
        bHit = true;
    }
    delete trace;
    // CloseHandle(trace);
    return bHit;
}

/**
 * @brief Starts up a new trace ray using a new trace result and a customized trace ray filter. 
 *
 * @param entity            The entity index.
 * @param target            The target index. 
 * @param vStartPosition    The starting position of the ray.
 * @param vEndPosition      The ending position of the ray.
 * @param filter            The function to use as a filter.
 *
 * @return                  True of false.        
 **/
inline bool UTIL_TraceRay(int entity, int target, float vStartPosition[3], float vEndPosition[3], TraceEntityFilter filter)
{
    // Starts up a new trace ray using a new trace result and a customized trace ray filter
    TR_TraceRayFilter(vStartPosition, vEndPosition, (MASK_SHOT|CONTENTS_GRATE), RayType_EndPoint, filter, entity);

    // Validate any kind of collision along the trace ray
    bool bHit;
    if (!TR_DidHit() || TR_GetEntityIndex() == target) 
    {
        // If trace hit, then stop
        bHit = true;
    }

    // Return on the end
    return bHit;
}

/**
 * @brief Calculates the distance between two entities.
 *
 * @param client            The client index. 
 * @param entity            The entity index.
 *
 * @return                  The distance amount.        
 **/
inline float UTIL_GetDistanceBetween(int client, int entity)
{
    // Initialize vectors
    float vPosition[3], vEndPosition[3], vMins[3], vMaxs[3];

    // Gets positions
    GetEntPropVector(client, Prop_Data, "m_vecAbsOrigin", vPosition);
    GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vEndPosition);
    
    // Get the client's min and max size vector
    GetClientMins(client, vMins); 
    GetClientMaxs(client, vMaxs);
    
    // Gets height and distance
    float flHeight = vMins[2] - vMaxs[2] + 10;
    float fDistance = vPosition[2] - vEndPosition[2];
    
    // Move the calculation to 2D
    if (fDistance > flHeight) 
    {
        vPosition[2] -= flHeight;
    }
    else if (fDistance < (-1.0 * flHeight)) 
    {
        vPosition[2] -= flHeight;
    }
    else 
    {
        vPosition[2] = vEndPosition[2];
    }
    
    // Gets distance between them
    return GetVectorDistance(vPosition, vEndPosition);
}

// ______________________________________________________________________________________________ //

inline bool PlayersFilter(int entity, int contentsMask)
{
    return ( (entity == 0) || (entity > MaxClients) );
}