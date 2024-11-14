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
#define GLFW_INCLUDE_GLEXT

#include "cube.h"

#include <GLFW/glfw3.h>

Cube::Cube(const Color &color, std::shared_ptr<Texture> &texture)
    : Mesh(texture)
{
    Vector3 p1(-1, -1, 1);
    Vector3 p2(1, -1, 1);
    Vector3 p3(1, 1, 1);
    Vector3 p4(-1, 1, 1);
    Vector3 normal(0, 0, 1);
    Vector2 t1(0, 0);
    Vector2 t2(1, 0);
    Vector2 t3(1, 1);
    Vector2 t4(0, 1);

    vertices.emplace_back(p1, normal, color, t1);
    vertices.emplace_back(p2, normal, color, t2);
    vertices.emplace_back(p3, normal, color, t3);
    vertices.emplace_back(p4, normal, color, t4);
    for (int i = 1; i < 6; i++)
    {
        Matrix4 rotationMatrix;
        if (i <= 3) rotationMatrix = Matrix4::rotateY(deg2rad(90.0 * i));
        if (i == 4) rotationMatrix = Matrix4::rotateX(deg2rad(90.0));
        if (i == 5) rotationMatrix = Matrix4::rotateX(deg2rad(-90.0));

        Vector3 normalRotated = (rotationMatrix * Vector4(normal, 1)).xyz();

        Vector4 result = rotationMatrix * Vector4(p1, 1.0);
        vertices.emplace_back(result.xyz(), normalRotated, color, t1);

        result = rotationMatrix * Vector4(p2, 1.0);
        vertices.emplace_back(result.xyz(), normalRotated, color, t2);

        result = rotationMatrix * Vector4(p3, 1.0);
        vertices.emplace_back(result.xyz(), normalRotated, color, t3);

        result = rotationMatrix * Vector4(p4, 1.0);
        vertices.emplace_back(result.xyz(), normalRotated, color, t4);
    }
}

void Cube::render() const
{
    Matrix4 translationMatrix = Matrix4::translate(position.x, position.y, position.z);
    Matrix4 rotationMatrix = Matrix4::rotateX(rotation.x) * Matrix4::rotateY(rotation.y) * Matrix4::rotateZ(rotation.z);

    Matrix4 worldMatrix = translationMatrix * rotationMatrix;

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    float worldMatrixF[16];
    worldMatrix.toColumnMajor(worldMatrixF);
    glMultMatrixf(worldMatrixF);
    glBegin(GL_QUADS);
    for (auto vertex : vertices)
    {
        glNormal3fv((float *)&vertex.normal);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float *)&vertex.color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&vertex.color);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0f);
        glTexCoord2fv((float *)&vertex.texcoord);
        glVertex3fv((float *)&vertex.position);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}