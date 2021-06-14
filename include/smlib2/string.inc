#if defined _smlib2_string_included
    #endinput
#endif

#define _smlib2_string_included

methodmap String {
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
}