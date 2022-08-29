/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          convert.sp
 *  Description:   Convertion with specific requirements
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

#if defined _smlib2_convert_included
    #endinput
#endif

#define _smlib2_convert_included

methodmap Convert {
    /**
     * @brief Converts string of "yes/on", "no/off", "false/true", "1/0" to a boolean value.
     * Always uses english as main language.
     * 
     * @param sOption           The string to be converted.
     * @return                  True if string is equivalent to "yes", false otherwise.
     */
    public static bool SettingToBool(char[] sOption) {
        return (
        !strcmp(sOption, "yes",     false)      || 
        !strcmp(sOption, "on",      false)      || 
        !strcmp(sOption, "true",    false)      || 
        !strcmp(sOption, "1",       false)
        ) ? true : false;
    }
}