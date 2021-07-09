#if defined _smlib2_string_included
    #endinput
#endif

#define _smlib2_string_included

methodmap StringEx {
    /**
     * @brief Converts uppercase chars in the string to lowercase chars.
     *
     * @param sBuffer           Input string buffer.
     */
    public static void ToLower(char[] sBuffer)
    {
        // i = char index
        int iLen = strlen(sBuffer);
        for (int i = 0; i < iLen; i++) 
        {
            // Character to convert
            sBuffer[i] = CharToLower(sBuffer[i]);
        }
    }

    /**
     * @brief Finds the amount of all occurrences of a character in a string.
     *
     * @param sBuffer           Input string buffer.
     * @param cSymbol           The character to search for.
     * @return                  The amount of characters in the string, or -1 if the characters were not found.
     */
    public static int CountOccurence(char[] sBuffer, char cSymbol) {
        // Initialize index
        int iCount;
        
        // i = char index
        int iLen = strlen(sBuffer);
        for (int i = 0; i < iLen; i++) 
        {
            // Validate char
            if (sBuffer[i] == cSymbol)
            {
                // Increment amount
                iCount++;
            }
        }

        // Return amount
        return iCount ? iCount : -1;
    }
    
    /**
     * @brief Randomly output string.
     *
     * @param sBuffer           The string buffer.
     * @param iMaxlen           The string maxlen.
     */
    public static void RandomOut(char[] sBuffer, int iMaxlen) {
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
    
    public static bool StrContainsEx(const char[] sStr, const char[] sSubStr)
    {
        int iLen = strlen(sStr);
        int iSubLen = strlen(sSubStr);

        if(iLen < iSubLen)
        {
            return false;
        }

        for(int x = 0; x < iSubLen; x++)
        {
            if(sStr[x] != sSubStr[x])
            {
                return false;
            }
        }

        return true;
    }
}