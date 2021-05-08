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