/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          matrix.sp
 *  Description:   Matrix implentation.
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

#if defined _smlib2_matrix_included
    #endinput
#endif

#define _smlib2_matrix_included

methodmap Matrix3x4 {
    public static void Identity(float matrix[16]) {
        matrix[ 0] = 1.0;        matrix[ 1] = 0.0;        matrix[ 2] = 0.0;        matrix[ 3] = 0.0;
        matrix[ 4] = 0.0;        matrix[ 5] = 1.0;        matrix[ 6] = 0.0;        matrix[ 7] = 0.0;
        matrix[ 8] = 0.0;        matrix[ 9] = 0.0;        matrix[10] = 1.0;        matrix[11] = 0.0;
        matrix[12] = 0.0;        matrix[13] = 0.0;        matrix[14] = 0.0;        matrix[15] = 1.0;
    }

    public static void RotateX(float mf[16], float angle) {
        mf[5] = Cosine(DegToRad(angle));
        mf[6] = Sine(DegToRad(angle));
        mf[9] = -Sine(DegToRad(angle));
        mf[10] = Cosine(DegToRad(angle));
    }

    public static void RotateY(float mf[16], float angle) {
        mf[0] = Cosine(DegToRad(angle));
        mf[2] = -Sine(DegToRad(angle));
        mf[8] = Sine(DegToRad(angle));
        mf[10] = Cosine(DegToRad(angle));
    }

    public static void RotateZ(float mf[16], float angle) {
        mf[0] = Cosine(DegToRad(angle));
        mf[1] = Sine(DegToRad(angle));
        mf[4] = -Sine(DegToRad(angle));
        mf[5] = Cosine(DegToRad(angle));
    }

    // Concatenate 2 matrices with the * operator
    public static void Concatenate(float mf[16], float inmf[16], float rmf[16]) {
        for (int i=0; i<16; i+=4) {
            for (int j=0; j<4; j++) {
                rmf[i + j] = mf[i + 0] * inmf[0 + j] + mf[i + 1] * inmf[4 + j] + mf[i + 2] * inmf[8 + j] + mf[i + 3] * inmf[12 + j];
            }
        }
    }

    // Use a matrix to transform a 3D point with the * operator
    public static void TransformPoint(float mf[16], float point[3], float out[3]) {
        out[0] = point[0] * mf[0] + point[1] * mf[4] + point[2] * mf[8] + mf[12];
        out[1] = point[0] * mf[1] + point[1] * mf[5] + point[2] * mf[9] + mf[13];
        out[2] = point[0] * mf[2] + point[1] * mf[6] + point[2] * mf[10] + mf[14];
    }

    // Rotate the mf matrix fDegrees counter-clockwise around a single axis( either x, y, or z )
    public static void Rotate(float mf[16], float fDegrees, int x, int y, int z) {
        float tmf[16];
        if (x == 1) Matrix3x4.RotateX(tmf, -fDegrees);
        if (y == 1) Matrix3x4.RotateY(tmf, -fDegrees);
        if (z == 1) Matrix3x4.RotateZ(tmf, -fDegrees);
        for (int i = 0; i < 16; i++) mf[i] = tmf[i] * mf[i];
    }

    public static void Scale(float mf[16], float sx, float sy, float sz) {
        int x;
        for (x = 0; x <  4; x++) mf[x] *= sx;
        for (x = 4; x <  8; x++) mf[x] *= sy;
        for (x = 8; x < 12; x++) mf[x] *= sz;
    }

    public static void Translate(float mf[16], float test[3]) {
        for (int j = 0; j < 4; j++) mf[12+j] += test[0] * mf[j] + test[1] * mf[4+j] + test[2] * mf[8+j]; 
    }

    public static void GetTranslate(float mf[16], float trn[3]) {
        trn[0] = mf[12];
        trn[1] = mf[13];
        trn[2] = mf[14];
    }

    public static void RotateByMatrix(float norm[3], float mf[16], float out[3]) {
        out[0] = norm[0] * mf[0] + norm[1] * mf[4] + norm[2] * mf[8];
        out[1] = norm[0] * mf[1] + norm[1] * mf[5] + norm[2] * mf[9];
        out[2] = norm[0] * mf[2] + norm[1] * mf[6] + norm[2] * mf[10];
    }

    // Zero out the translation part of the matrix
    public static void RotationOnly(float mf[16], float tmf[16]) {
        for (int i = 0; i < 16; i++) tmf[i] = mf[i];
        tmf[12] = 0.0; tmf[13] = 0.0; tmf[14] = 0.0;
    }

    // Create a rotation matrix for a counter-clockwise rotation of fDegrees around an arbitrary axis(x, y, z)
    public static void RotateMatrix(float mf[16], float fDegrees, float x, float y, float z) {
        Matrix3x4.Identity(mf);
        
        float cosA = Cosine(DegToRad(fDegrees));
        float sinA = Sine(DegToRad(fDegrees));
        float m = 1.0 - cosA;
        mf[0] = cosA + x * x * m;
        mf[5] = cosA + y * y * m;
        mf[10] = cosA + z * z * m;

        float tmp1 = x * y * m;
        float tmp2 = z * sinA;
        mf[4] = tmp1 + tmp2;
        mf[1] = tmp1 - tmp2;

        tmp1 = x * z * m;
        tmp2 = y * sinA;
        mf[8] = tmp1 - tmp2;
        mf[2] = tmp1 + tmp2;

        tmp1 = y * z * m;
        tmp2 = x * sinA;
        mf[9] = tmp1 + tmp2;
        mf[6] = tmp1 - tmp2;
    }

    // Simple but not robust matrix inversion. (Doesn't work properly if there is a scaling or skewing transformation.)
    public static void InvertSimple(float mf[16], float rmf[16]) {
        rmf[0] = mf[0]; rmf[1] = mf[4]; rmf[2] = mf[8]; rmf[3] = 0.0;
        rmf[4] = mf[1]; rmf[5] = mf[5]; rmf[6] = mf[9]; rmf[7] = 0.0;
        rmf[8] = mf[2]; rmf[9] = mf[6]; rmf[10] = mf[10]; rmf[11] = 0.0;
        
        rmf[12] = -(mf[12] * mf[0]) - (mf[13] * mf[1]) - (mf[14] * mf[2]);
        rmf[13] = -(mf[12] * mf[4]) - (mf[13] * mf[5]) - (mf[14] * mf[6]);
        rmf[14] = -(mf[12] * mf[8]) - (mf[13] * mf[9]) - (mf[14] * mf[10]);
        
        rmf[15] = 1.0;
    }

    public static void InvertRotation(float mf[16], float rmf[16]) {
        rmf[0] = mf[0]; rmf[1] = mf[4]; rmf[2] = mf[8]; rmf[3] = 0.0;
        rmf[4] = mf[1]; rmf[5] = mf[5]; rmf[6] = mf[9]; rmf[7] = 0.0;
        rmf[8] = mf[2]; rmf[9] = mf[6]; rmf[10] = mf[10]; rmf[11] = 0.0;
        rmf[12] = 0.0; rmf[13] = 0.0; rmf[14] = 0.0; rmf[15] = 1.0;
    }

}