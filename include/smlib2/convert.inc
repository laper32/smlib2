#if defined _convert_included
    #endinput
#endif

#define _convert_included

/**
 * @brief Converts string of "yes/on", "no/off", "false/true", "1/0" to a boolean value.
 * Always uses english as main language.
 * 
 * @param sOption           The string to be converted.
 * @return                  True if string is equivalent to "yes", false otherwise.
 **/
stock bool ConvertSettingToBool(char[] sOption)
{
    return (
        !strcmp(sOption, "yes",     false)      || 
        !strcmp(sOption, "on",      false)      || 
        !strcmp(sOption, "true",    false)      || 
        !strcmp(sOption, "1",       false)
        ) ? true : false;
}