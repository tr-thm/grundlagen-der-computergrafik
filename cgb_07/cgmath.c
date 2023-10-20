/**
 * Grundlagen der Computergrafik
 * Copyright (C) 2023 Tobias Reimann
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <math.h>
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

vector3 matrixVector3Multiply(matrix m, vector3 v)
{
    vector3 result = {
        m.m11 * v.x + m.m21 * v.y + m.m31 * v.z,
        m.m12 * v.x + m.m22 * v.y + m.m32 * v.z,
        m.m13 * v.x + m.m23 * v.y + m.m33 * v.z
    };
    return result;
}

float deg2rad(float deg)
{
    return deg * M_PI / 180.0f;
}
