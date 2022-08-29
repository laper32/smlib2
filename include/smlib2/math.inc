/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          math.sp
 *  Description:   Mathlib.
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

#if defined _smlib2_math_included
    #endinput
#endif
#define _smlib2_math_included

methodmap Math {
    /**
     * @brief Returns the positive integer of the value.
     *
     * @param i1                The input value.
     * @return                  The positive integer.
     */
    public static int abs(int i1) {
        return (i1 ^ (i1 >> 31)) - (i1 >> 31);
    }

    /**
     * @brief Returns the positive float of the value.
     *
     * @param i1                The input value.
     * @return                  The positive float.
     */
    public static float fabs(float i1) {
        return FloatAbs(i1);
    }

    public static any min(any i1, any i2) {
        return min(i1, i2);
    }

    public static any max(any i1, any i2) {
        return max(i1, i2);
    }

    public static any clamp(any val, any i1, any i2) {
        return clamp(val, i1, i2);
    }
    
    public static any overflow(any value, any i1, any i2) {
        overflow(value, i1, i2);
    }

    public static float sqrt(any val) {
        sqrt(val);
    }

    public static int GetPercentageInt(int value, int all) {
        GetPercentageInt(value, all);
    }

    public static float GetPercentageFloat(float value, float all) {
        GetPercentageFloat(value, all);
    }

    public static any mean(any[] _array) {
        mean(_array);
    }

}

/**
 * @brief Returns the positive integer of the value.
 *
 * @param i1                The input value.
 * @return                  The positive integer.
 */
inline int abs(int i1)
{
    return (i1 ^ (i1 >> 31)) - (i1 >> 31);
}

/**
 * @brief Returns the positive float of the value.
 *
 * @param i1                The input value.
 * @return                  The positive float.
 */
inline float fabs(float i1)
{
    return FloatAbs(i1);
}

/**
 * @brief Returns the smaller of two provided values.
 *  
 * @param i1                The first value.
 * @param i2                The second value.
 *
 * @return                  The smallest value.
 **/
inline any min(any i1, any i2) 
{
    return (i1 < i2 ? i1 : i2); 
} 

/**
 * @brief Returns the bigger of two provided values.
 *  
 * @param i1                The first value.
 * @param i2                The second value.
 *
 * @return                  The biggest value.
 **/
inline any max(any i1, any i2) 
{
    return (i1 > i2 ? i1 : i2); 
}

/**
 * @brief Returns a clamped value in the range [min, max].
 * 
 * @param val               The value.
 * @param i1                Lower bound.
 * @param i2                Upper bound.
 *
 * @return                  The clamp value. 
 */
inline any clamp(any val, any i1, any i2)
{
    return ( (val > i2) ? i2 : (val < i1) ? i1 : val );
}

/**
 * @brief Returns a value what if "overflowed", fix it to a second round's value.
 *
 * @param value             The value.
 * @param i1                Lower bound.
 * @param i2                Upper bound.
 *
 * @return                  The overflowed value.
 */
inline any overflow(any value, any i1, any i2)
{
    return (value % i2) + i1;
}

/**
 * @brief Returns the square root of the input value, equivalent to floatpower(value, 0.5).
 * 
 * @param val               The input value.
 */
inline float sqrt(any val)
{
    return SquareRoot(val);
}

/**
 * Gets the percentage of amount in all as Integer where amount and all are numbers 
 * and amount usually is a subset of all.
 *
 * @param value         Integer value
 * @param all           Integer value
 * @return              An Integer value between 0 and 100 (inclusive).
 */
inline int GetPercentageInt(int value, int all)
{
    return RoundToNearest(float(value) / float(all) * 100.0);
}

/**
 * Gets the percentage of amount in all as Float where amount and all are numbers 
 * and amount usually is a subset of all.
 * 
 * @param value         A float value index.
 * @param all           A float value index.
 * @return              A float value between 0.0 and 100.0.
 */
inline float GetPercentageFloat(float value, float all)
{
    return (value / all) * 100.0;
}

inline any mean(any[] _array)
{
    int sum = 0;
    for (int i = 0; i < sizeof(_array[]); i++)
    {
        sum += _array[i];
    }
    return ( sum / sizeof(_array[]) );
}