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

#include "mesh.h"

#include <GLFW/glfw3.h>

void Mesh::render() const
{
    Matrix4 worldMatrix = position * rotation;

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
        glVertex3fv((float *)&vertex.position);
    }
    glEnd();
    glPopMatrix();
}

void Mesh::setPosition(const Vector3 &position)
{
    this->position = Matrix4::translate(position.x, position.y, position.z);
}

void Mesh::setRotation(const Vector3 &rotation)
{
    this->rotation = Matrix4::rotateX(rotation.x) * Matrix4::rotateY(rotation.y) * Matrix4::rotateZ(rotation.z);
}