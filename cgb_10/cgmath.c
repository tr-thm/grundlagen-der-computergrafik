#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include "cgmath.h"

matrix matrixTranslate(float x, float y, float z)
{
    matrix m = {};
    m.m11 = 1;  m.m21 = 0;  m.m31 = 0;  m.m41 = x;
    m.m12 = 0;  m.m22 = 1;  m.m32 = 0;  m.m42 = y;
    m.m13 = 0;  m.m23 = 0;  m.m33 = 1;  m.m43 = z;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

matrix matrixRotateX(float a)
{
    matrix m = {};
    m.m11 = 1;  m.m21 =      0;  m.m31 =       0;  m.m41 = 0;
    m.m12 = 0;  m.m22 = cos(a);  m.m32 = -sin(a);  m.m42 = 0;
    m.m13 = 0;  m.m23 = sin(a);  m.m33 =  cos(a);  m.m43 = 0;
    m.m14 = 0;  m.m24 =      0;  m.m34 =       0;  m.m44 = 1;
    return m;
}

matrix matrixRotateY(float a)
{
    matrix m = {};
    m.m11 =  cos(a);  m.m21 = 0;  m.m31 = sin(a);  m.m41 = 0;
    m.m12 =       0;  m.m22 = 1;  m.m32 =      0;  m.m42 = 0;
    m.m13 = -sin(a);  m.m23 = 0;  m.m33 = cos(a);  m.m43 = 0;
    m.m14 =       0;  m.m24 = 0;  m.m34 =      0;  m.m44 = 1;
    return m;
}

matrix matrixRotateZ(float a)
{
    matrix m = {};
    m.m11 = cos(a);  m.m21 = -sin(a);  m.m31 = 0;  m.m41 = 0;
    m.m12 = sin(a);  m.m22 =  cos(a);  m.m32 = 0;  m.m42 = 0;
    m.m13 =      0;  m.m23 =       0;  m.m33 = 1;  m.m43 = 0;
    m.m14 =      0;  m.m24 =       0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

matrix matrixScale(float a)
{
    matrix m = {};
    m.m11 = a;  m.m21 = 0;  m.m31 = 0;  m.m41 = 0;
    m.m12 = 0;  m.m22 = a;  m.m32 = 0;  m.m42 = 0;
    m.m13 = 0;  m.m23 = 0;  m.m33 = a;  m.m43 = 0;
    m.m14 = 0;  m.m24 = 0;  m.m34 = 0;  m.m44 = 1;
    return m;
}

vector3 matrixVector3Multiply(matrix m, vector3 v)
{
    vector3 result = {
        m.m11 * v.x + m.m21 * v.y + m.m31 * v.z,
        m.m12 * v.x + m.m22 * v.y + m.m32 * v.z,
        m.m13 * v.x + m.m23 * v.y + m.m33 * v.z
    };
    return result;
}

matrix matrixMultiply(matrix a, matrix b)
{
    matrix m = {};

    //row 1
    m.m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14;
    m.m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24;
    m.m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34;
    m.m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44;
    
    //row 2
    m.m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14;
    m.m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24;
    m.m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34;
    m.m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44;

    //row 3
    m.m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14;
    m.m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24;
    m.m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34;
    m.m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44;

    //row 4
    m.m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14;
    m.m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24;
    m.m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34;
    m.m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44;

    return m;
}

float deg2rad(float deg)
{
    return deg * M_PI / 180.0f;
}

float timePeriod(unsigned long period, unsigned long offset)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    unsigned long seconds = ((unsigned long)(t.tv_sec) + offset) % period;
    double microseconds = (unsigned long)(t.tv_usec) / 1000000.0;
    double time = seconds + microseconds;
    return (float)(time / period);
}