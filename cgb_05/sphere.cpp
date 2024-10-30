/**
 * Grundlagen der Computergrafik
 * Copyright © 2021-2024 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in C++
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

#include "sphere.h"

Sphere::Sphere(Color color)
{
    const int segments = 64;
    const int rings = segments / 2;
    int vcount = segments * rings * 4;

    std::vector<std::vector<Vector3>> vectors;
    vectors.resize(segments + 1);
    std::vector<Vector3> fillVector;
    fillVector.resize(rings + 1);
    std::fill(fillVector.begin(), fillVector.end(), Vector3{0.0, 0.0, 0.0});
    std::fill(vectors.begin(), vectors.end(), fillVector);

    for (int y = 0; y <= rings; y++)
    {
        float deg = 180.0f / rings * (y - rings * 0.5f);
        Matrix4 rotationMatrixX = Matrix4::rotateX(deg2rad(deg));
        Vector4 startVector = rotationMatrixX * Vector4(0, 0, 1, 1);
        vectors[0][y] = startVector.xyz();
        vectors[segments][y] = startVector.xyz();
        for (int x = 1; x < segments; x++)
        {
            float deg2 = 360.0f / (float)segments * (float)x;
            Matrix4 rotationMatrixY = Matrix4::rotateY(deg2rad(deg2));
            Vector4 result = rotationMatrixY * Vector4(vectors[0][y], 1.0);
            vectors[x][y] = result.xyz();
        }
    }
    int i = 0;
    for (int y = 0; y < rings; y++)
    {
        for (int x = 0; x < segments; x++)
        {
            vertices.emplace_back(vectors[x][y + 1], color);
            vertices.emplace_back(vectors[x + 1][y + 1], color);
            vertices.emplace_back(vectors[x + 1][y], color);
            vertices.emplace_back(vectors[x][y], color);
        }
    }
}

Sphere::~Sphere()
{
}

void Sphere::render() const
{
    Matrix4 translationMatrix = Matrix4::translate(position.x, position.y, position.z);
    Matrix4 rotationMatrix = Matrix4::rotateX(rotation.x) * Matrix4::rotateY(rotation.y) * Matrix4::rotateZ(rotation.z);

    Matrix4 worldMatrix = translationMatrix * rotationMatrix;

    glPushMatrix();
    float worldMatrixF[16];
    worldMatrix.toColumnMajor(worldMatrixF);
    glMultMatrixf(worldMatrixF);
    glBegin(GL_QUADS);
    for (auto vertex : vertices)
    {
        glColor3fv((float *)&vertex.color);
        glVertex3fv((float *)&vertex.position);
    }
    glEnd();
    glPopMatrix();
}

void Sphere::setPosition(Vector3 position)
{
    this->position = position;
}

void Sphere::setRotation(Vector3 rotationInDeg)
{
    this->rotation.x = deg2rad(rotationInDeg.x);
    this->rotation.y = deg2rad(rotationInDeg.y);
    this->rotation.z = deg2rad(rotationInDeg.z);
}