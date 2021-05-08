/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          hint.sp
 *  Type:          Hint
 *  Description:   Interface for instructor hint.
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

#if defined _hint_included
    #endinput
#endif

#define _hint_included

/**
 * @section Instructor HUD Icon indexes.
 */
enum InstructorHud_Icon
{
    Icon_bulb = 0,
    Icon_caution,
    Icon_alert,
    Icon_alert_red,
    Icon_tip,
    Icon_skull,
    Icon_no,
    Icon_run,
    Icon_interact,
    Icon_button,
    Icon_door,
    Icon_arrow_plain,
    Icon_arrow_plain_white_dn,
    Icon_arrow_plain_white_up,
    Icon_arrow_up,
    Icon_arrow_right,
    Icon_fire,
    Icon_present
};

/**
 * @section Instructor HUD icon name.
 */
static char InstructorHud_Icon_String[InstructorHud_Icon][32] =
{
    "icon_bulb",
    "icon_caution",
    "icon_alert",
    "icon_alert_red",
    "icon_tip",
    "icon_skull",
    "icon_no",
    "icon_run",
    "icon_interact",
    "icon_button",
    "icon_door",
    "icon_arrow_plain",
    "icon_arrow_plain_white_dn",
    "icon_arrow_plain_white_up",
    "icon_arrow_up",
    "icon_arrow_right",
    "icon_fire",
    "icon_present"
};

/**
 * @brief Methodmap about InstructorHud.
 * @note  It is related to events.
 */
methodmap InstructorHud < Event
{
    /**
     * @brief Property about Instructor HUD target
     */
    property int target 
    {
        /**
         * @brief Gets the target about the hint.
         */
        public get() 
        {
            return this.GetInt("hint_target", 0); 
        }

        /**
         * @brief Sets the owner about the hint.
         * 
         * @param entity            The entity index.
         */
        public set(int entity) 
        {
            this.SetInt("hint_target", entity);
        }
    }
    
    /**
     * @brief Property about Instructor HUD flags.
     */
    property int flags 
    {
        /**
         * @brief Gets the flag of the hint.
         */
        public get() 
        {
            return this.GetInt("hint_flags", 0);
        }

        /**
         * @brief Sets the flag of the hint.
         * 
         * @param  iFlags          The Flags index.
         */
        public set(int iFlags)
        {
            this.SetInt("hint_flags", iFlags); 
        }
    }

    /**
     * @brief Property about Instructor HUD activator user ID.
     */
    property int activator_userid 
    {
        /**
         * @brief Gets the hint's activator's user id.
         */
        public get()
        {
            return this.GetInt("hint_activator_userid", 0);
        }

        /**
         * @brief Sets the hint's activator's user ID.
         * 
         * @param userid            The user ID index.
         */
        public set(int userid)
        {
            this.SetInt("hint_activator_userid", userid);
        }
    }

    /**
     * @brief Property about Instructor HUD positioning index.
     * @note  If true, following, false otherwise.
     */
    property bool positioning
    {
        /**
         * @brief Gets whether this hint is static.
         */
        public get()
        {
            return this.GetBool("hint_static", true);
        }

        /**
         * @brief Sets whether this hint is static.
         * 
         * @param bStatic           Sets whether this hint is static.
         */
        public set(bool bStatic)
        {
            this.SetBool("hint_static", bStatic);
        }
    }

    /**
     * @brief Property about whether this hint nodraw.
     * @note  true -> end immed on nodraw; false -> yes.
     */
    property bool invisible 
    {
        /**
         * @brief Gets whether this hint render to client.
         */
        public get()
        {
            return this.GetBool("hint_allow_nodraw_target", true);
        }

        /**
         * @brief Sets whether this hint render to client.
         * 
         * @param bNodraw           Sets whether this hint nodraw.
         */
        public set (bool bNodraw)
        {
            this.SetBool("hint_allow_nodraw_target", bNodraw);
        }
    }

    /**
     * @brief Property about whether this hint force caption.
     * @note  true -> no; false -> show when occluded.
     */

    property bool forcecaption { 
        /**
         * @brief Gets whether this hint force caption.
         */
        public get()
        {
            return this.GetBool("hint_forcecaption", false);
        }

        /**
         * @brief Sets whether this hint force caption.
         * 
         * @param bForceCaption    Sets whether this hint force caption.
         */
        public set(bool bForceCaption)
        { 
            this.SetBool("hint_forcecaption", bForceCaption);
        }
    }
    
    /**
     * @brief Property about getting the icon displaying on the screen.
     */
    property InstructorHud_Icon icon_onscreen
    {
        /**
         * @brief Gets the icon.
         */
        public get ()
        {
            char iconname[32];
            this.GetString("hint_icon_onscreen", iconname, 32);

            for (int i = 0; i < view_as<int>(InstructorHud_Icon); ++i)
            {
                if ( strcmp( iconname, InstructorHud_Icon_String[ view_as<InstructorHud_Icon>(i) ] ) == 0)
                {
                    return view_as<InstructorHud_Icon>(i);
                }
            }

            return Icon_bulb;
        }

        /**
         * @brief Sets the icon.
         * 
         * @param iIcon             The icon index.
         */
        public set(InstructorHud_Icon iIcon)
        {
            this.SetString("hint_icon_onscreen", InstructorHud_Icon_String[iIcon]);
        }
    }
    
    /**
     * @brief Property of the icon about remove on the screen.
     */
    property InstructorHud_Icon icon_offscreen 
    { 
        /**
         * @brief Get the icon.
         */
        public get ()
        {
            char iconname[32];
            this.GetString("hint_icon_offscreen", iconname, 32);

            for(int i = 0; i < view_as<int>(InstructorHud_Icon); ++i)
            {
                if(strcmp( iconname, InstructorHud_Icon_String[ view_as<InstructorHud_Icon>(i) ] ) == 0)
                {
                    return view_as<InstructorHud_Icon>(i);
                }
            }

            return Icon_bulb;
        }

        /**
         * @brief Sets the icon.
         * 
         * @param iIcon             The Icon index.
         */
        public set(InstructorHud_Icon iIcon)
        {
            this.SetString("hint_icon_offscreen", InstructorHud_Icon_String[iIcon]);
        }
    }

    /**
     * @brief Gets whether the icon displaying on the screen.
     * @note  true -> don't show; false -> show.
     */
    property bool show_offscreen
    {
        public get()
        {
            return this.GetBool("hint_nooffscreen", false);
        }
        public set(bool val)
        {
            this.SetBool("hint_nooffscreen", val);
        }
    }
    
    /**
     * @brief Property the range about displaying on the screen.
     */
    property float range
    {
        /**
         * @brief Gets the range about displaying on the screen.
         */
        public get ()
        {
            return this.GetFloat("hint_range", 1000.0);
        }

        /**
         * @brief Sets the range about displaying on the screen.
         * 
         * @param flRange           The range index.
         */
        public set(float flRange)
        {
            this.SetFloat("hint_nooffscreen", flRange); 
        }
    }
    
    /**
     * @brief property the time about remove the hint on the screen.
     */
    property float timeout
    {
        /**
         * @brief Gets the time about remove the hint on the screen.
         */
        public get()
        {
            return this.GetFloat("hint_timeout", 1.0);
        }

        /**
         * @brief Sets the time about remove the hint on the screen.
         * 
         * @param flTime            The time index.
         */
        public set(float flTime)
        {
            this.SetFloat("hint_timeout", flTime);
        }
    }
    
    /**
     * @brief Property about the position of displaying hint on the screen.
     */
    property float offset
    {
        /**
         * @brief Gets the offset of the hint position index.
         */
        public get()
        {
            return this.GetFloat("hint_icon_offset", 0.0);
        }

        /**
         * @brief Sets the offset of the hint position index.
         * 
         * @param iOffset           The offset index.
         */
        public set(float iOffset)
        {
            this.SetFloat("hint_icon_offset", iOffset);
        }
    }
    
    /**
     * @brief Property about pulse.
     */
    property int pulseoption
    {
        /**
         * @brief Gets the pulse option.
         */
        public get()
        {
            return this.GetInt("hint_pulseoption", 0);
        }

        /**
         * @brief Sets the pulse option.
         * 
         * @param iPulse            The pulse option
         */
        public set(int iPulse)
        {
            this.SetInt("hint_pulseoption", iPulse);
        }
    }
    
    /**
     * @brief Property about alpha.
     */
    property int alphaoption
    {
        /**
         * @brief Gets the alpha option.
         */
        public get()
        {
            return this.GetInt("hint_alphaoption", 0);
        }

        /**
         * @brief Sets the alpha.
         * 
         * @param iAlpha            The alpha index.
         */
        public set(int iAlpha)
        {
            this.SetInt("hint_alphaoption", iAlpha);
        }
    }
    
    /**
     * @brief Property about shake index.
     */
    property int shakeoption 
    {
        /**
         * @brief Gets shake option.
         */
        public get() 
        {
            return this.GetInt("hint_shakeoption", 0);
        }

        /**
         * @brief Sets shake option.
         * @note  0 -> No; 1 -> Narrow; 2 -> Wide.
         * 
         * @param iShake            The shake index.
         */
        public set(int iShake)
        {
            this.SetInt("hint_shakeoption", iShake); 
        }
    }
    
    /**
     * @brief Set hint color.
     * 
     * @param r             Red.
     * @param g             Green.
     * @param b             Blue.
     */
    public void color(int r, int g, int b)
    {
        char clr[32];
        FormatEx(clr, 32, "%d %d %d", r, g, b);
        this.SetString("hint_color", clr);
    }

    /**
     * @brief Create an event to create hint.
     * 
     * @param name              The event name.
     * @param target            (Not compulsory) The target index.
     * @return                  The event index.
     */
    public InstructorHud(const char[] name = "", int target = 0)
    {
        Event e = CreateEvent("instructor_server_hint_create", true);
        if(e == null)
        {
            ThrowNativeError(SP_ERROR_NATIVE, "Unable to create event \"instructor_server_hint_create\": The event is null.");
        }

        e.SetBool("hint_local_player_only", true);

        e.SetInt("hint_flags", 0);
        e.SetInt("hint_activator_userid", 0);
        e.SetInt("hint_target", target);

        if(name[0] == 0)
        {
            e.SetString("hint_name", name);
            e.SetString("hint_replace_key", name);
        }
        else
        {
            char buffer[32];
            RandomString(buffer, 32);
            e.SetString("hint_name", buffer);
            e.SetString("hint_replace_key", buffer);
        }

        return view_as<InstructorHud>(e);
    }
    
    /**
     * @brief Initialize hint index.
     */
    public void Init()
    {
        this.color(57, 197, 187);
        this.positioning = false;
        this.invisible = true;
        this.forcecaption = false;
        this.show_offscreen = false;
        this.range = 1000.0;
        this.offset = 1.0;
        this.pulseoption = 0;
        this.alphaoption = 0;
        this.shakeoption = 0;
    }

    /**
     * @brief Remove hint event.
     */
    public void Destroy()
    {
        delete view_as<Event>(this);
    }

    /**
     * @brief Display a hint to a specific user.
     * 
     * @param client            The client index.
     * @param buffer            The string what input.
     */
    public void Display(int client, const char[] buffer, any ...)
    {
        char caption[256];
        VFormat(caption, 256, buffer, 3);
        this.activator_userid = GetClientUserId(client);
        this.SetString("hint_caption", caption);
        this.SetString("hint_activator_caption", caption);
        this.FireToClient(client);
        this.activator_userid = 0;
    }

    /**
     * @brief Display a hint to all users.
     * 
     * @param buffer            The string what input.
     */
    public void DisplayAll(const char[] buffer, any ...)
    {
        char caption[256];
        VFormat(caption, 256, buffer, 2);
        this.SetString("hint_caption", caption);
        this.SetString("hint_activator_caption", caption);
        this.Fire();
    }

    /**
     * @brief Display a hint to a specific user.
     * @note  Same as Display(), but with translation included.
     * 
     * @param client            The client index.
     * @param buffer            The string what input.
     */
    public void tDisplay(int client, const char[] buffer, any ...)
    {
        SetGlobalTransTarget(client);
        char caption[256];
        VFormat(caption, 256, buffer, 3);
        this.activator_userid = GetClientUserId(client);
        this.SetString("hint_caption", caption);
        this.SetString("hint_activator_caption", caption);
        this.FireToClient(client);
        this.activator_userid = 0;
        SetGlobalTransTarget(LANG_SERVER);
    }
    
    /**
     * @brief Display a hint to all users.
     * @note  Same as DisplayAll(), but with translaiton included.
     * 
     * @param buffer            The string what input.
     */
    public void tDisplayAll(const char[] buffer, any ...)
    {
        char caption[256];
        for(int client = 1; client <= MaxClients; ++client)
        {
            if(IsPlayerExist(client))
            {
                SetGlobalTransTarget(client);
                VFormat(caption, 256, buffer, 2);
                this.activator_userid = GetClientUserId(client);
                this.SetString("hint_caption", caption);
                this.SetString("hint_activator_caption", caption);
                this.FireToClient(client);
            }
        }

        this.activator_userid = 0;
        SetGlobalTransTarget(LANG_SERVER);
    }
}

/**
 * @brief Function to create instructor hint to a specific client.
 * 
 * @param client            The client index.
 * @param holdtime          The hint displaying time.
 * @param icon              The icon index.
 * @param radius            The radius about receving the hint.
 * @param r                 The color index :: red.
 * @param g                 The color index :: green.
 * @param b                 The color index :: blue.
 * @param caption           The alart message index.
 */
inline void CreateInstructorHint(int client,
                                float holdtime,
                                InstructorHud_Icon icon,
                                float radius,
                                int r,
                                int g,
                                int b,
                                const char[] caption,
                                any ...)
{
    InstructorHud hint = new InstructorHud("");
    hint.Init();
    hint.range = radius;
    hint.color(r, g, b);
    hint.timeout = holdtime;
    hint.icon_onscreen = icon;
    char sMessage[256];
    VFormat(sMessage, sizeof(sMessage), caption, 8);
    hint.Display(client, sMessage);

    hint.Destroy();
}

/**
 * @brief Function to create instructor hint to all users.
 * 
 * @param holdtime          The hint displaying time.
 * @param icon              The icon index.
 * @param radius            The radius about receving the hint.
 * @param r                 The color index :: red.
 * @param g                 The color index :: green.
 * @param b                 The color index :: blue.
 * @param caption           The alart message index.
 */
inline void CreateInstructorHintAll(float holdtime,
                                   InstructorHud_Icon icon,
                                   float radius,
                                   int r,
                                   int g,
                                   int b,
                                   const char[] caption,
                                   any ...)
{
    InstructorHud hint = new InstructorHud("");
    hint.Init();
    hint.color(r, g, b);
    hint.range = radius;
    hint.timeout = holdtime;
    hint.icon_onscreen = icon;
    char sMessage[256];
    VFormat(sMessage, 256, caption, 7);
    hint.DisplayAll(sMessage);
    hint.Destroy();
}