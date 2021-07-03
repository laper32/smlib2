/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          numeric.sp
 *  Description:   Numeric related
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

#if defined _smlib2_numeric_included
    #endinput
#endif

#define _smlib2_numeric_included

methodmap Numeric {
    public static int HexToDec(const char[] hex)
    {
        int i, result, value;
        while((value = Numeric.IsHexSymbol(hex[i++])) != -1)
        {
            result = result * 16 + value;
        }
        return result;
    }
    public static int IsHexSymbol(int ch)
    {
        if(!ch)
            return -1;
        
        if('0' <= ch && ch <= '9')
            return ch - '0';
        
        ch &= ~0x20;
        if('A' <= ch && ch <= 'F')
            return ch - 'A' + 10;
        
        return -1;
    }
}