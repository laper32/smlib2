/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          matrix.sp
 *  Description:   Matrix implentation.
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

#if defined _matrix_included
    #endinput
#endif

#define _matrix_included

inline void Matrix3x4Identity(float[16] matrix)
{
    matrix[ 0] = 1.0;        matrix[ 1] = 0.0;        matrix[ 2] = 0.0;        matrix[ 3] = 0.0;
    matrix[ 4] = 0.0;        matrix[ 5] = 1.0;        matrix[ 6] = 0.0;        matrix[ 7] = 0.0;
    matrix[ 8] = 0.0;        matrix[ 9] = 0.0;        matrix[10] = 1.0;        matrix[11] = 0.0;
    matrix[12] = 0.0;        matrix[13] = 0.0;        matrix[14] = 0.0;        matrix[15] = 1.0;
}