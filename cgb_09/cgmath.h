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
typedef struct {
    float x;
    float y;
    float z;
    float w;
} vector4;
typedef struct {
    float x;
    float y;
    float z;
} vector3;
typedef struct {
    float x;
    float y;
} vector2;
typedef struct {
    float r;
    float g;
    float b;
    float a;
} color;
typedef struct {
    vector3 pos;
    vector3 norm;
    color color;
    vector2 texcoord;
} vertex;
typedef struct {
    vertex* vertices;
    int vcount;
} mesh;
#endif

matrix matrixTranslate(float x, float y, float z);
matrix matrixRotateX(float a);
matrix matrixRotateY(float a);
matrix matrixRotateZ(float a);
matrix matrixScale(float a);

vector3 matrixVector3Multiply(matrix m, vector3 v);
matrix matrixMultiply(matrix a, matrix b);

float deg2rad(float deg);
