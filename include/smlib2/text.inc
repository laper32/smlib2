#if defined _text_included
#endinput
#endif
#define _text_included

// Sets default output prefix.
static char Prefix[32] = "[@greenSM@default]";

/**
 * @brief Format color regular with specific string.
 * 
 * @param sText             The text.
 * @param iMaxLen           The maximum length of string.
 */
inline void ColorString(char[] sText, int iMaxLen)
{
    //Replace color tokens with CS:GO color chars
    ReplaceString(sText, iMaxLen, "@default",       TEXT_COLOR_DEFAILT);            //x01
    ReplaceString(sText, iMaxLen, "@normal",        TEXT_COLOR_NORMAL);             //x01
    ReplaceString(sText, iMaxLen, "@white",	        TEXT_COLOR_WHITE);              //x01
    ReplaceString(sText, iMaxLen, "@darkred",       TEXT_COLOR_DARKRED);            //x02
    ReplaceString(sText, iMaxLen, "@pink",          TEXT_COLOR_PINK);               //x03
    ReplaceString(sText, iMaxLen, "@green",         TEXT_COLOR_GREEN);              //x04
    ReplaceString(sText, iMaxLen, "@lime",          TEXT_COLOR_LIME);               //x05
    ReplaceString(sText, iMaxLen, "@yellow",        TEXT_COLOR_YELLOW);             //x05
    ReplaceString(sText, iMaxLen, "@lightgreen",    TEXT_COLOR_LIGHTGREEN);         //x06
    ReplaceString(sText, iMaxLen, "@lightred",      TEXT_COLOR_LIGHTRED);           //x07
    ReplaceString(sText, iMaxLen, "@red",           TEXT_COLOR_RED);                //x07
    ReplaceString(sText, iMaxLen, "@grey",          TEXT_COLOR_GREY);               //x08
    ReplaceString(sText, iMaxLen, "@gray",          TEXT_COLOR_GRAY);               //x08
    ReplaceString(sText, iMaxLen, "@olive",         TEXT_COLOR_OLIVE);              //x09
    ReplaceString(sText, iMaxLen, "@orange",        TEXT_COLOR_ORANGE);             //x10
    ReplaceString(sText, iMaxLen, "@silver",        TEXT_COLOR_SILVER);             //x0A
    ReplaceString(sText, iMaxLen, "@lightblue",     TEXT_COLOR_LIGHTBLUE);          //x0B
    ReplaceString(sText, iMaxLen, "@blue",          TEXT_COLOR_BLUE);               //x0C
    ReplaceString(sText, iMaxLen, "@purple",        TEXT_COLOR_PURPLE);             //x0E
    ReplaceString(sText, iMaxLen, "@darkorange",    TEXT_COLOR_DARKORANGE);         //x0F
}

/**
 * @brief set prefix.
 *
 * @param prefix                The string index.
 */
inline int SetPrefix(const char[] prefix)
{
    return strcopy(Prefix, sizeof(Prefix), prefix);
}

/**
 * @brief Format the string before output the text.
 *
 * @param sText                 The text index.
 * @param iMaxLen               The length of the string.
 * @param bColor                (Optional) Will this text output with color? ture->yes, false->no.
 */
inline void FormatString(char[] sText, int iMaxLen, bool bColor = true)
{
    if(bColor)
    {
        //Format prefix onto the string
        Format(sText, iMaxLen, " @green%t @default%s", "Prefix", sText);
        ColorString(sText, iMaxLen);
    }
    else
    {
        Format(sText, iMaxLen, "%s %s", "Prefix", sText);
    }
}

/**
 * @brief Print console text to the client. (with style)
 * 
 * @param client            The client index.
 * @param ...               Translation formatting parameters.  
 */
inline void LPrintToConsole(int client, any ...)
{
    if (!IsFakeClient(client))
    {
        SetGlobalTransTarget(client);

        static char sTranslation[CONSOLE_LINE_LENGTH];
        VFormat(sTranslation, sizeof(sTranslation), "%t", 2);

        FormatString(sTranslation, sizeof(sTranslation));
        
        PrintToConsole(client, sTranslation);
    }
}

/**
 * @brief Print console text to all players or server. (with style)
 * 
 * @param bServer           True to also print text to server console, false just to the clients.
 * @param ...               Translation formatting parameters.
 **/
inline void LPrintToConsoleAll(bool bServer, any ...)
{
    static char sTranslation[CONSOLE_LINE_LENGTH];

    // Validate server
    if (bServer)
    {
        // Sets translation target
        SetGlobalTransTarget(LANG_SERVER);

        // Translate phrase
        VFormat(sTranslation, sizeof(sTranslation), "%t", 3);

        // Format string to create plugin style.
        FormatString(sTranslation, sizeof(sTranslation), false);

        // Print translated phrase to server console.
        PrintToServer(sTranslation);
    }
    
    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Client validation
        if (!IsPlayerExist(i, false))
        {
            continue;
        }

        // Validate real client
        if (!IsFakeClient(i))
        {
            // Set translation target.
            SetGlobalTransTarget(i);

            // Translation phrase.
            VFormat(sTranslation, sizeof(sTranslation), "%t", 3);

            // Format string.
            FormatString(sTranslation, sizeof(sTranslation));

            PrintToConsole(i, sTranslation);
        }
    }
}

/**
 * @brief Print hint center text to the client.
 * 
 * @param client            The client index.
 * @param ...               Formatting parameters.
 **/
inline void LPrintHintText(int client, any ...)
{
    // Real client validation
    if (!IsFakeClient(client))
    {
        // Sets translation target
        SetGlobalTransTarget(client);

        // Translate phrase
        static char sTranslation[CHAT_LINE_LENGTH];
        VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 2);

        // Print translated phrase to the client screen
        UTIL_CreateClientHint(client, sTranslation);
    }
}

/**
 * @brief Print hint center text to all clients.
 *
 * @param ...               Formatting parameters.
 **/
inline void LPrintHintTextAll(any ...)
{
    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Validate client
        if (!IsPlayerExist(i, false))
        {
            continue;
        }
        
        // Validate real client
        if (!IsFakeClient(i))
        {
            // Sets translation target
            SetGlobalTransTarget(i);
            
            // Translate phrase
            static char sTranslation[CHAT_LINE_LENGTH];
            VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 1);
            
            // Print translated phrase to the client screen
            UTIL_CreateClientHint(i, sTranslation);
        }
    }
}

/**
 * @brief Print hud text to the client.
 * 
 * @param hSync             New HUD synchronization object.
 * @param client            The client index.
 * @param x                 x coordinate, from 0 to 1. -1.0 is the center.
 * @param y                 y coordinate, from 0 to 1. -1.0 is the center.
 * @param holdTime          Number of seconds to hold the text.
 * @param r                 Red color value.
 * @param g                 Green color value.
 * @param b                 Blue color value.
 * @param a                 Alpha transparency value.
 * @param effect            0/1 causes the text to fade in and fade out. 2 causes the text to flash[?].
 * @param fxTime            Duration of chosen effect (may not apply to all effects).
 * @param fadeIn            Number of seconds to spend fading in.
 * @param fadeOut           Number of seconds to spend fading out.
 * @param ...               Formatting parameters.
 **/
inline void LPrintHudText(Handle hSync,
                                    int client, float x, float y,
                                    float holdTime,
                                    int r, int g, int b, int a,
                                    int effect,
                                    float fxTime,
                                    float fadeIn, float fadeOut,
                                    any ...)
{
    // Validate real client
    if (!IsFakeClient(client))
    {
        // Sets translation target
        SetGlobalTransTarget(client);

        // Translate phrase
        static char sTranslation[CHAT_LINE_LENGTH];
        VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 14);

        // Print translated phrase to the client screen
        UTIL_CreateClientHud(hSync, client, x, y, holdTime, r, g, b, a, effect, fxTime, fadeIn, fadeOut, sTranslation);
    }
}

/**
 * @brief Print hud text to all clients.
 *
 * @param hSync             New HUD synchronization object.
 * @param x                 x coordinate, from 0 to 1. -1.0 is the center.
 * @param y                 y coordinate, from 0 to 1. -1.0 is the center.
 * @param holdTime          Number of seconds to hold the text.
 * @param r                 Red color value.
 * @param g                 Green color value.
 * @param b                 Blue color value.
 * @param a                 Alpha transparency value.
 * @param effect            0/1 causes the text to fade in and fade out. 2 causes the text to flash[?].
 * @param fxTime            Duration of chosen effect (may not apply to all effects).
 * @param fadeIn            Number of seconds to spend fading in.
 * @param fadeOut           Number of seconds to spend fading out.
 * @param ...               Formatting parameters.
 **/
inline void LPrintHudTextAll(Handle hSync,
                            float x, float y,
                            float holdTime,
                            int r, int g, int b, int a,
                            int effect,
                            float fxTime,
                            float fadeIn, float fadeOut,
                            any ...)
{
    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Validate client
        if (!IsPlayerExist(i, false))
        {
            continue;
        }
        
        // Validate real client
        if (!IsFakeClient(i))
        {
            // Sets translation target
            SetGlobalTransTarget(i);
            
            // Translate phrase
            static char sTranslation[CHAT_LINE_LENGTH];
            VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 13);

            // Print translated phrase to the client screen
            UTIL_CreateClientHud(hSync, i, x, y, holdTime, r, g, b, a, effect, fxTime, fadeIn, fadeOut, sTranslation);
        }
    }
}

/**
 * @brief Print chat text to the client.
 * @note Dual line only, with default 192 string length.
 * 
 * @param client            The client index.
 * @param ...               Formatting parameters. 
 **/
inline void LPrintToChatSingleLine(int client, any ...)
{
    // Real client validation
    if (!IsFakeClient(client))
    {
        // Sets translation target
        SetGlobalTransTarget(client);

        // Translate phrase
        static char sTranslation[CHAT_LINE_LENGTH];
        VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 2);

        // Format string to create plugin style
        FormatString(sTranslation, CHAT_LINE_LENGTH);

        // Print translated phrase to the client chat
        PrintToChat(client, sTranslation);
    }
}

inline void LPrintToChatTeamSingleLine(int team, any ...)
{
    for (int i = 1; i <= MaxClients; i++)
    {
        if (!IsPlayerExist(i, false)) continue;

        if (ToolsGetTeam(i) != team) continue;

        if (!IsFakeClient(i))
        {
            // Sets translation target
            SetGlobalTransTarget(i);
            
            // Translate phrase
            static char sTranslation[CHAT_LINE_LENGTH];
            VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 1);
            
            // Format string to create plugin style
            FormatString(sTranslation, CHAT_LINE_LENGTH);
            
            // Print translated phrase to the client chat
            PrintToChat(i, sTranslation);
        }
    }
}

/**
 * @brief Print center text to all clients.
 *
 * @param ...                  Formatting parameters.
 **/
inline void LPrintToChatAllSingleLine(any ...)
{
    // i = client index
    for (int i = 1; i <= MaxClients; i++)
    {
        // Validate client
        if (!IsPlayerExist(i, false))
        {
            continue;
        }
        
        // Validate real client
        if (!IsFakeClient(i))
        {
            // Sets translation target
            SetGlobalTransTarget(i);
            
            // Translate phrase
            static char sTranslation[CHAT_LINE_LENGTH];
            VFormat(sTranslation, CHAT_LINE_LENGTH, "%t", 1);
            
            // Format string to create plugin style
            FormatString(sTranslation, CHAT_LINE_LENGTH);
            
            // Print translated phrase to the client chat
            PrintToChat(i, sTranslation);
        }
    }
}

/**
 * @brief Print text to server. (with style)
 * 
 * @param ...               Translation formatting parameters.  
 **/
inline void LPrintToServer(any:...)
{
    // Sets translation target
    SetGlobalTransTarget(LANG_SERVER);

    // Translate phrase
    static char sTranslation[CONSOLE_LINE_LENGTH];
    VFormat(sTranslation, sizeof(sTranslation), "%t", 1);

    // Format string to create plugin style
    FormatString(sTranslation, sizeof(sTranslation), false);

    // Print translated phrase to server console
    PrintToServer(sTranslation);
}

/**
 * @brief Print into console for client. (with style)
 * 
 * @param client            The client index.
 * @param ...               Formatting parameters. 
 **/
inline void LReplyToCommand(int client, any ...)
{
    // Validate client
    if (!IsPlayerExist(client, false))
    {
        return;
    }
    
    // Sets translation target
    SetGlobalTransTarget(client);
    
    // Translate phrase
    static char sTranslation[CONSOLE_LINE_LENGTH];
    VFormat(sTranslation, CONSOLE_LINE_LENGTH, "%t", 2);

    // Format string to create plugin style
    FormatString(sTranslation, CONSOLE_LINE_LENGTH);

    // Print translated phrase to the client console
    ReplyToCommand(client, sTranslation);
}

// _________________________________________________________________________________________________ //

/**
 * @brief Randomly output string.
 *
 * @param sBuffer           The string buffer.
 * @param iMaxlen           The string maxlen.
 */
inline void RandomString(char[] sBuffer, int iMaxlen)
{
    // Terminator
    iMaxlen--;

    char sCharacters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234556789";
    int iRandLen = strlen(sCharacters);

    int n = 0;
    int c = 0;

    while(n < iMaxlen)
    {
        if(sCharacters[0] == '\0')
        {
            c = GetRandomInt(33, 126);
            sBuffer[n] = c;
        }
        else
        {
            c = GetRandomInt(0, iRandLen);
            sBuffer[n] = sCharacters[c];
        }

        n++;
    }

    sBuffer[iMaxlen] = '\0';
}