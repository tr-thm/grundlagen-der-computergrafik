#ifndef CGMATH
#define CGMATH
typedef struct {
    float m11;
    float m12;
    float m13;
    float m14;
    float m21;
    float m22;
    float m23;
    float m24;
    float m31;
    float m32;
    float m33;
    float m34;
    float m41;
    float m42;
    float m43;
    float m44;
} matrix;
#endif

matrix matrixTranslate(float x, float y, float z);
matrix matrixRotateX(float a);
matrix matrixRotateY(float a);
matrix matrixRotateZ(float a);

float deg2rad(float deg);
