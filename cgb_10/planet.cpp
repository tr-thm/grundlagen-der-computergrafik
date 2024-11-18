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

#include "planet.h"

Planet::Planet(const Color &color, std::shared_ptr<Texture> &texture, std::shared_ptr<Texture> &specularTexture, std::shared_ptr<Texture> &nightTexture)
    : Sphere(color, texture), specularTexture(specularTexture), nightTexture(nightTexture)
{
    // Custom lights
    float black[3] = {0.0f, 0.0f, 0.0f};
    float white[3] = {1.0f, 1.0f, 1.0f};
    float white2[3] = {1.05f, 1.05f, 1.05f};
    float nightLightBright[3] = {0.3f, 0.3f, 0.3f};
    float nightLightDark[3] = {0.1f, 0.1f, 0.1f};
    float blue[3] = {0.397f, 0.587f, 1.0f};

    // Light 2 is the sun with blue tint
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT2, GL_SPECULAR, black);
    glLightfv(GL_LIGHT2, GL_AMBIENT, black);

    // Light 3 is diffuse light shining in the direction of the camera
    float lightPositionF[4] = {0.0f, 0.0f, 50000.0f, 0.0f};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white2);
    glLightfv(GL_LIGHT3, GL_SPECULAR, black);
    glLightfv(GL_LIGHT3, GL_AMBIENT, black);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPositionF);

    // Light 4 is the night light
    glLightfv(GL_LIGHT4, GL_DIFFUSE, nightLightBright);
    glLightfv(GL_LIGHT4, GL_SPECULAR, black);
    glLightfv(GL_LIGHT4, GL_AMBIENT, nightLightDark);

    // Light 5 is the sun with only diffuse light
    glLightfv(GL_LIGHT5, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT5, GL_SPECULAR, black);
    glLightfv(GL_LIGHT5, GL_AMBIENT, black);

    // Light 6 is the sun with only specular light
    glLightfv(GL_LIGHT6, GL_DIFFUSE, black);
    glLightfv(GL_LIGHT6, GL_SPECULAR, white);
    glLightfv(GL_LIGHT6, GL_AMBIENT, black);
}

void Planet::render() const
{
    Matrix4 worldMatrix = position * rotation * scale;
    float worldMatrixF[16];
    worldMatrix.toColumnMajor(worldMatrixF);

    float lightPositionSun[4] = {0.0f, 0.0f, 50000.0f, 0.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, lightPositionSun);
    glLightfv(GL_LIGHT5, GL_POSITION, lightPositionSun);
    glLightfv(GL_LIGHT6, GL_POSITION, lightPositionSun);
    float lightPositionInverse[4] = {0.0f, 0.0f, -50000.0f, 0.0f};
    glLightfv(GL_LIGHT7, GL_POSITION, lightPositionInverse);

    // Disable default light
    glDisable(GL_LIGHT1);

    // render athmosphere
    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_LIGHT2);
    glBindTexture(GL_TEXTURE_2D, 0);
    renderQuads(worldMatrixF);
    glDisable(GL_LIGHT2);

    // reduce athmosphere to halo
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT3);
    glBindTexture(GL_TEXTURE_2D, 0);
    renderQuads(worldMatrixF);
    glDisable(GL_LIGHT3);

    // render night texture
    glBlendFunc(GL_ONE, GL_ONE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT4);
    glBindTexture(GL_TEXTURE_2D, nightTexture->id);
    renderQuads(worldMatrixF);
    glDisable(GL_LIGHT4);

    // render day texture
    glBlendFunc(GL_ONE, GL_ONE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT5);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    renderQuads(worldMatrixF);
    glDisable(GL_LIGHT5);

    // render specular reflections
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT6);
    glBindTexture(GL_TEXTURE_2D, specularTexture->id);
    renderQuads(worldMatrixF);
    glDisable(GL_LIGHT6);

    // Restore all settings to default
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_LIGHT1);
}

void Planet::renderQuads(const float *worldMatrix) const
{
    glPushMatrix();
    glMultMatrixf(worldMatrix);

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
}