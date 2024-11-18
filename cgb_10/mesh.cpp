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

#include "mesh.h"

#include "texture.h"

Mesh::Mesh(std::shared_ptr<Texture> &texture)
    : texture(texture)
{
}

void Mesh::render() const
{
    Matrix4 worldMatrix = position * rotation * scale;

    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }

    glPushMatrix();
    float worldMatrixF[16];
    worldMatrix.toColumnMajor(worldMatrixF);
    glMultMatrixf(worldMatrixF);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float *)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float *)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, (float *)&emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBegin(GL_QUADS);
    for (auto vertex : vertices)
    {
        glNormal3fv((float *)&vertex.normal);
        glTexCoord2fv((float *)&vertex.texcoord);
        glVertex3fv((float *)&vertex.position);
    }
    glEnd();
    glPopMatrix();
    if (texture) glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setPosition(const Vector3 &position)
{
    this->position = Matrix4::translate(position.x, position.y, position.z);
}

void Mesh::setRotation(const Vector3 &rotation)
{
    this->rotation = Matrix4::rotateX(rotation.x) * Matrix4::rotateY(rotation.y) * Matrix4::rotateZ(rotation.z);
}

void Mesh::setScale(const double scale)
{
    this->scale = Matrix4::scale(scale);
}

void Mesh::setMaterial(const Color &diffuse, const Color &specular, const Color &emission, const Color &ambient, const float shininess)
{
    std::copy(&diffuse.r, &diffuse.r + 3, this->diffuse);
    std::copy(&specular.r, &specular.r + 3, this->specular);
    std::copy(&emission.r, &emission.r + 3, this->emission);
    std::copy(&ambient.r, &ambient.r + 3, this->ambient);
    this->shininess = shininess;
}