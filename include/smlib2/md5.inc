/**
 * ============================================================================
 *
 *  Zombie Plague
 *
 *  File:          md5.sp
 *  Type:          MD5
 *  Description:   MD5 algorithm.
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

#if defined _md5_included
    #endinput
#endif

#define _md5_included

/**
 * Calculate the md5 hash of a string.
 *
 * @param str			Input String
 * @param output		Output String Buffer
 * @param maxlen		Size of the Output String Buffer
 * @noreturn
 */
inline void md5sum(const char[] str, char[] output, int maxlen)
{
    int x[2], buf[4], input[64];
    int i, ii;

    int len = strlen(str);

    // MD5Init
    x[0] = x[1] = 0;
    buf[0] = 0x67452301;
    buf[1] = 0xefcdab89;
    buf[2] = 0x98badcfe;
    buf[3] = 0x10325476;

    // MD5Update
    int update[16];

    update[14] = x[0];
    update[15] = x[1];

    int mdi = (x[0] >>> 3) & 0x3F;

    if ((x[0] + (len << 3)) < x[0]) { x[1] += 1; }

    x[0] += len << 3;
    x[1] += len >>> 29;

    int c = 0;
    while (len--) 
    {
        input[mdi] = str[c];
        mdi += 1;
        c += 1;

        if (mdi == 0x40) {

            for (i = 0, ii = 0; i < 16; ++i, ii += 4)
            {
                update[i] = (input[ii + 3] << 24) | 
                            (input[ii + 2] << 16) | 
                            (input[ii + 1] <<  8) | 
                            (input[ii    ]      );
            }
            // Transform
            transform(buf, update);
            mdi = 0;
        }
    }

    // MD5Final
    int padding[64] = 
    {
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    int inx[16];
    inx[14] = x[0];
    inx[15] = x[1];

    mdi = (x[0] >>> 3) & 0x3F;

    len = (mdi < 56) ? (56 - mdi) : (120 - mdi);
    update[14] = x[0];
    update[15] = x[1];

    mdi = (x[0] >>> 3) & 0x3F;

    if ((x[0] + (len << 3)) < x[0]) { x[1] += 1; }

    x[0] += len << 3;
    x[1] += len >>> 29;

    c = 0;
    while (len--) 
    {
        input[mdi] = padding[c];
        mdi += 1;
        c += 1;

        if (mdi == 0x40) 
        {
            for (i = 0, ii = 0; i < 16; ++i, ii += 4) 
            {
                update[i] = (input[ii + 3] << 24) | 
                            (input[ii + 2] << 16) | 
                            (input[ii + 1] <<  8) | 
                            (input[ii    ]      ) ;
            }

            // Transform
            transform(buf, update);

            mdi = 0;
        }
    }

    for (i = 0, ii = 0; i < 14; ++i, ii += 4) 
    {
        inx[i] =    (input[ii + 3] << 24) | 
                    (input[ii + 2] << 16) | 
                    (input[ii + 1] <<  8) | 
                    (input[ii    ]      ) ;
    }

    transform(buf, inx);

    int digest[16];
    for (i = 0, ii = 0; i < 4; ++i, ii += 4) 
    {
        digest[ii    ] = (buf[i]        ) & 0xFF;
        digest[ii + 1] = (buf[i] >>>  8 ) & 0xFF;
        digest[ii + 2] = (buf[i] >>> 16 ) & 0xFF;
        digest[ii + 3] = (buf[i] >>> 24 ) & 0xFF;
    }

    FormatEx(output, maxlen, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], digest[7],
        digest[8], digest[9], digest[10], digest[11], digest[12], digest[13], digest[14], digest[15]);
}

// linear transformation
inline void transform(int[] _buffer, int[] _input)
{
    // 4bytes.
    int a = _buffer[0], b = _buffer[1], c = _buffer[2], d = _buffer[3];

    FF(a, b, c, d, _input[ 0],  7, 0xd76aa478);
    FF(d, a, b, c, _input[ 1], 12, 0xe8c7b756);
    FF(c, d, a, b, _input[ 2], 17, 0x242070db);
    FF(b, c, d, a, _input[ 3], 22, 0xc1bdceee);
    FF(a, b, c, d, _input[ 4],  7, 0xf57c0faf);
    FF(d, a, b, c, _input[ 5], 12, 0x4787c62a);
    FF(c, d, a, b, _input[ 6], 17, 0xa8304613);
    FF(b, c, d, a, _input[ 7], 22, 0xfd469501);
    FF(a, b, c, d, _input[ 8],  7, 0x698098d8);
    FF(d, a, b, c, _input[ 9], 12, 0x8b44f7af);
    FF(c, d, a, b, _input[10], 17, 0xffff5bb1);
    FF(b, c, d, a, _input[11], 22, 0x895cd7be);
    FF(a, b, c, d, _input[12],  7, 0x6b901122);
    FF(d, a, b, c, _input[13], 12, 0xfd987193);
    FF(c, d, a, b, _input[14], 17, 0xa679438e);
    FF(b, c, d, a, _input[15], 22, 0x49b40821);

    GG(a, b, c, d, _input[ 1],  5, 0xf61e2562);
    GG(d, a, b, c, _input[ 6],  9, 0xc040b340);
    GG(c, d, a, b, _input[11], 14, 0x265e5a51);
    GG(b, c, d, a, _input[ 0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, _input[ 5],  5, 0xd62f105d);
    GG(d, a, b, c, _input[10],  9, 0x02441453);
    GG(c, d, a, b, _input[15], 14, 0xd8a1e681);
    GG(b, c, d, a, _input[ 4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, _input[ 9],  5, 0x21e1cde6);
    GG(d, a, b, c, _input[14],  9, 0xc33707d6);
    GG(c, d, a, b, _input[ 3], 14, 0xf4d50d87);
    GG(b, c, d, a, _input[ 8], 20, 0x455a14ed);
    GG(a, b, c, d, _input[13],  5, 0xa9e3e905);
    GG(d, a, b, c, _input[ 2],  9, 0xfcefa3f8);
    GG(c, d, a, b, _input[ 7], 14, 0x676f02d9);
    GG(b, c, d, a, _input[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, _input[ 5],  4, 0xfffa3942);
    HH(d, a, b, c, _input[ 8], 11, 0x8771f681);
    HH(c, d, a, b, _input[11], 16, 0x6d9d6122);
    HH(b, c, d, a, _input[14], 23, 0xfde5380c);
    HH(a, b, c, d, _input[ 1],  4, 0xa4beea44);
    HH(d, a, b, c, _input[ 4], 11, 0x4bdecfa9);
    HH(c, d, a, b, _input[ 7], 16, 0xf6bb4b60);
    HH(b, c, d, a, _input[10], 23, 0xbebfbc70);
    HH(a, b, c, d, _input[13],  4, 0x289b7ec6);
    HH(d, a, b, c, _input[ 0], 11, 0xeaa127fa);
    HH(c, d, a, b, _input[ 3], 16, 0xd4ef3085);
    HH(b, c, d, a, _input[ 6], 23, 0x04881d05);
    HH(a, b, c, d, _input[ 9],  4, 0xd9d4d039);
    HH(d, a, b, c, _input[12], 11, 0xe6db99e5);
    HH(c, d, a, b, _input[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, _input[ 2], 23, 0xc4ac5665);

    II(a, b, c, d, _input[ 0],  6, 0xf4292244);
    II(d, a, b, c, _input[ 7], 10, 0x432aff97);
    II(c, d, a, b, _input[14], 15, 0xab9423a7);
    II(b, c, d, a, _input[ 5], 21, 0xfc93a039);
    II(a, b, c, d, _input[12],  6, 0x655b59c3);
    II(d, a, b, c, _input[ 3], 10, 0x8f0ccc92);
    II(c, d, a, b, _input[10], 15, 0xffeff47d);
    II(b, c, d, a, _input[ 1], 21, 0x85845dd1);
    II(a, b, c, d, _input[ 8],  6, 0x6fa87e4f);
    II(d, a, b, c, _input[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, _input[ 6], 15, 0xa3014314);
    II(b, c, d, a, _input[13], 21, 0x4e0811a1);
    II(a, b, c, d, _input[ 4],  6, 0xf7537e82);
    II(d, a, b, c, _input[11], 10, 0xbd3af235);
    II(c, d, a, b, _input[ 2], 15, 0x2ad7d2bb);
    II(b, c, d, a, _input[ 9], 21, 0xeb86d391);

    _buffer[0] += a;
    _buffer[1] += b;
    _buffer[2] += c;
    _buffer[3] += d;
}

static inline int FF(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += (((b) & (c))  | ((~b) & (d))) + x + ac;
    a =  (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int GG(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += (((b) & (d)) | ((c) & (~d))) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int HH(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += ((b) ^ (c) ^ (d)) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int II(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += ((c) ^ ((b) | (~d))) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}