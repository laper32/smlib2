/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          mem.sp
 *  Description:   Memory library
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

#if defined _mem_included
    #endinput
#endif

#define _mem_included

/**
 * @brief Create a memory for the custom convention call.
 *
 * @param gameConf          The game config handle.
 * @return                  The zero memory address.
 **/
inline Address CreateMemoryForSDKCall(GameData gameConf)
{
    // Validate zero memory
    static Address pZeroMemory = Address_Null;
    if (pZeroMemory != Address_Null)
    {
        return pZeroMemory;
    }
   
    // Gets the server address
    Address pServerBase; 
    InitGameConfAddress(gameConf, pServerBase, "server");
    int pAddress = view_as<int>(pServerBase) + GetModuleSize(pServerBase) - 1;
   
    // Find the free memory
    for(;;)
    {
        int iByte = LoadFromAddress(view_as<Address>(pAddress), NumberType_Int8);
        if (iByte != 0x00)
        {
            break;
        }
       
        pAddress--;
    }
   
    /* Align for safe code injection */
    pZeroMemory = view_as<Address>(pAddress + 0x100 & 0xFFFFFF00); // 255 bytes
    return pZeroMemory;
}

/**
 * @brief Gets the size of a module in the memory.
 *
 * @param pAddress          The module address.
 * @return                  The size value.
 **/
inline int GetModuleSize(Address pAddress)
{
    int iOffset = LoadFromAddress(pAddress + view_as<Address>(0x3C), NumberType_Int32);    // NT headers offset
    return LoadFromAddress(pAddress + view_as<Address>(iOffset + 0x50), NumberType_Int32); // nt->OptionalHeader.SizeOfImage
}

/**
 * @brief Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
 *
 * @param pDest        The destination address where the content is to be copied.
 * @param sSource      The source of data to be copied.
 * @param iSize        The number of bytes to copy.
 */
inline void memcpy(Address pDest, char[] sSource, int iSize)
{
    // For more copying speed
    int i = iSize / 4;
    memcpy4b(pDest, view_as<any>(sSource), i);
   
    // Copy the rest of staff
    for(i *= 4, pDest += view_as<Address>(i); i < iSize; i++)
    {
        StoreToAddress(pDest++, sSource[i], NumberType_Int8);
    }
}

/**
 * @brief Copies the 4 bytes from the location pointed to by source directly to the memory block pointed to by destination. 
 *
 * @param pDest        The destination address where the content is to be copied.
 * @param sSource      The source of data to be copied.
 * @param iSize        The number of bytes to copy.
 */
inline void memcpy4b(Address pDest, any[] sSource, int iSize)
{
    // Copy 4 bytes at once
    for(int i = 0; i < iSize; i++)
    {
        StoreToAddress(pDest, sSource[i], NumberType_Int32);
        pDest += view_as<Address>(4);
    }
}

/**
 * @brief Writes the DWord D (i.e. 4 bytes) to the string. 
 *
 * @param asm             The assemly string.
 * @param pAddress        The address of the call.
 * @param iOffset         (Optional) The address offset. (Where 0x0 starts)
 */
inline void writeDWORD(char[] asm, any pAddress, int iOffset = 0)
{
    asm[iOffset]   = pAddress & 0xFF;
    asm[iOffset+1] = pAddress >> 8 & 0xFF;
    asm[iOffset+2] = pAddress >> 16 & 0xFF;
    asm[iOffset+3] = pAddress >> 24 & 0xFF;
}