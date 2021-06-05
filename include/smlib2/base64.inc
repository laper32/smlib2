/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          base64.sp
 *  Description:   Base 64 algorithm.
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

#if defined _smlib2_base64_included
    #endinput
#endif

#define _smlib2_base64_included

/**********************************************************************************
 *
 * Base64 Encoding/Decoding Functions
 * All Credits to to SirLamer & ScriptCoderPro
 * Taken from http://forums.alliedmods.net/showthread.php?t=101764
 *
 ***********************************************************************************/

static const char table[] = 
  // 0000000000111111111122222222223333333333444444444455555555556666
  // 0123456789012345678901234567890123456789012345678901234567890123
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int decodeTable[] = 
{
//  0   1   2   3   4   5   6   7   8   9
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //   0 -   9
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  10 -  19
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  20 -  29
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  30 -  39
    0,  0,  0,  62, 0,  0,  0,  63, 52, 53,  //  40 -  49
    54, 55, 56, 57, 58, 59, 60, 61, 0,  0,   //  50 -  59
    0,  0,  0,  0,  0,  0,  1,  2,  3,  4,   //  60 -  69
    5,  6,  7,  8,  9,  10, 11, 12, 13, 14,  //  70 -  79
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,  //  80 -  89
    25, 0,  0,  0,  0,  0,  0,  26, 27, 28,  //  90 -  99
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38,  // 100 - 109
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48,  // 110 - 119
    49, 50, 51, 0,  0,  0,  0,  0,  0,  0,   // 120 - 129
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 130 - 139
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 140 - 149
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 150 - 159
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 160 - 169
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 170 - 179
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 180 - 189
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 190 - 199
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 200 - 209
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 210 - 219
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 220 - 229
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 230 - 239
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 240 - 249
    0,  0,  0,  0,  0,  0                    // 250 - 256
};

/*
 * For some reason the standard demands a string in 24-bit (3 character) intervals.
 * This fill character is used to identify unused bytes at the end of the string.
 */
static const char cFillChar          = '=';

// The conversion characters between the standard and URL-compliance Base64 protocols
static const char mime_chars[]       = "+/=";
static const char url_chars[]        = "-_.";

/**
 * An Object-oriented warpper for Base 64 algorithm.
 */
methodmap Base64 {
    /**
     * Encodes a string or binary data into Base64
     *
     * @param sSource		The input string or binary data to be encoded.
     * @param sResult		The storage buffer for the Base64-encoded result.
     * @param len			The maximum length of the storage buffer, in characters/bytes.
     * @param sourcelen 	(optional): The number of characters or length in bytes to be read from the input source.
     *						This is not needed for a text string, but is important for binary data since there is no end-of-line character.
     * @return				The length of the written Base64 string, in bytes.
     */
    public static int Encode(const char[] sSource, char[] sResult, int len, int sourcelen = 0) {
        return encode(sSource, sResult, len, sourcelen);
    }

    /**
     * Decodes a Base64 string.
     *
     * @param sSource		The input string in compliant Base64 format to be decoded.
     * @param sResult		The storage buffer for the decoded text strihg or binary data.
     * @param len			The maximum length of the storage buffer, in characters/bytes.
     * @return				The length of the decoded data, in bytes.
     */
    public static int Decode(const char[] sSource, char[] sResult, int len) {
        return decode(sSource, sResult, len);
    }

    /**
     * Converts a standards-compliant Base64 string to the commonly accepted URL-compliant alternative.
     * Note: The result will be the same length as the input string as long as the output buffer is large enough.
     *
     * @param sSource		The standards-compliant Base64 input string to converted.
     * @param sResult		The storage buffer for the URL-compliant result.
     * @param len			The maximum length of the storage buffer in characters/bytes.
     * @return				Number of cells written.
     */
    public static int MimeToURL(const char[] sSource, char[] sResult, int len) {
        return mime2url(sSource, sResult, len);
    }

    /**
     * Converts a URL-compliant Base64 string to the standards-compliant version.
     * Note: The result will be the same length as the input string as long as the output buffer is large enough.
     *
     * @param sSource		The URL-compliant Base64 input string to converted.
     * @param sResult		The storage buffer for the standards-compliant result.
     * @param len			The maximum length of the storage buffer in characters/bytes.
     * @return				Number of cells written.
     */
    public static int URLToMime(const char[] sSource, char[] sResult, int len) {
        return url2mime(sSource, sResult, len);
    }
}

/**
 * Encodes a string or binary data into Base64
 *
 * @param sSource		The input string or binary data to be encoded.
 * @param sResult		The storage buffer for the Base64-encoded result.
 * @param len			The maximum length of the storage buffer, in characters/bytes.
 * @param sourcelen 	(optional): The number of characters or length in bytes to be read from the input source.
 *						This is not needed for a text string, but is important for binary data since there is no end-of-line character.
 * @return				The length of the written Base64 string, in bytes.
 */
inline int encode(const char[] sSource, char[] sResult, int len, int sourcelen = 0)
{
    int nLength;	// The string length to be read from the input
    int resPos;		// The string position in the result buffer

    // If the read length was specified, use it; otherwise, pull the string length from the input.
    if (sourcelen > 0) { nLength = sourcelen; }
    else { nLength = strlen(sSource); }

    // Loop through and generate the Base64 encoded string
    // NOTE: This performs the standard encoding process.  Do not manipulate the logic within this loop.
    for (int nPos = 0; nPos < nLength; nPos++) 
    {
        int cCode;

        cCode = (sSource[nPos] >> 2) & 0x3f;

        resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);

        cCode = (sSource[nPos] << 4) & 0x3f;
        if (++nPos < nLength) { cCode |= (sSource[nPos] >> 4) & 0x0f; }
        resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);

        if ( nPos < nLength ) 
        {
            cCode = (sSource[nPos] << 2) & 0x3f;
            if (++nPos < nLength) { cCode |= (sSource[nPos] >> 6) & 0x03; }

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);
        }
        else 
        {
            nPos++;
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", cFillChar);
        }

        if (nPos < nLength) 
        {
            cCode = sSource[nPos] & 0x3f;
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);
        }
        else 
        {
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", cFillChar);
        }
    }

    return resPos;
}

/**
 * Decodes a Base64 string.
 *
 * @param sSource		The input string in compliant Base64 format to be decoded.
 * @param sResult		The storage buffer for the decoded text strihg or binary data.
 * @param len			The maximum length of the storage buffer, in characters/bytes.
 * @return				The length of the decoded data, in bytes.
 */
inline int decode(const char[] sSource, char[] sResult, int len)
{
    int nLength = strlen(sSource);  // The string length to be read from the input
    int resPos;                     // The string position in the result buffer

    // Loop through and generate the Base64 encoded string
    // NOTE: This performs the standard encoding process.  Do not manipulate the logic within this loop.
    for (int nPos = 0; nPos < nLength; nPos++) 
    {
        int c, c1;

        c	= decodeTable[sSource[nPos++]];
        c1	= decodeTable[sSource[nPos]];

        c = (c << 2) | ((c1 >> 4) & 0x3);

        resPos += FormatEx(sResult[resPos], len - resPos, "%c", c);

        if (++nPos < nLength) 
        {
            c = sSource[nPos];

            if (c == cFillChar) break;

            c = decodeTable[sSource[nPos]];
            c1 = ((c1 << 4) & 0xf0) | ((c >> 2) & 0xf);

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", c1);
        }

        if (++nPos < nLength) 
        {
            c1 = sSource[nPos];

            if (c1 == cFillChar) break;

            c1 = decodeTable[sSource[nPos]];
            c = ((c << 6) & 0xc0) | c1;

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", c);
        }
    }

    return resPos;
}

/*
 * Converts a standards-compliant Base64 string to the commonly accepted URL-compliant alternative.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The standards-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the URL-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
inline int mime2url(const char[] sSource, char[] sResult, int len)
{
    int chars_len = sizeof(mime_chars);	// Length of the two standards vs. URL character lists
    int nLength;								// The string length to be read from the input
    int temp_char;								// Buffer character

    nLength = strlen(sSource);

    char[] sTemp = new char[ nLength + 1 ]; // Buffer string

    // Loop through string
    for (int i = 0; i < nLength; i++) 
    {
        temp_char = sSource[i];

        for (int j = 0; j < chars_len; j++) 
        {
            if(temp_char == mime_chars[j]) 
            {
                temp_char = url_chars[j];
                break;
            }
        }
        sTemp[i] = temp_char;
    }
    sTemp[nLength] = '\0';
    return strcopy(sResult, len, sTemp);
}

/*
 * Converts a URL-compliant Base64 string to the standards-compliant version.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The URL-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the standards-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
inline int url2mime(const char[] sSource, char[] sResult, int len)
{
    int chars_len = sizeof(mime_chars);	// Length of the two standards vs. URL character lists
    int nLength;                        // The string length to be read from the input
    int temp_char;                      // Buffer character

    nLength = strlen(sSource);

    char[] sTemp = new char[ nLength + 1 ]; // Buffer string

    // Loop through string
    for (int i = 0; i < nLength; i++) 
    {
        temp_char = sSource[i];
        for (int j = 0; j < chars_len; j++) 
        {
            if (temp_char == url_chars[j]) 
            {
                temp_char = mime_chars[j];
                break;
            }
        }
        sTemp[i] = temp_char;
    }
    sTemp[nLength] = '\0';
    return strcopy(sResult, len, sTemp);
}
