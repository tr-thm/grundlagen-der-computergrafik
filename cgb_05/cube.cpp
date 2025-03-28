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

#include "cube.h"

Cube::Cube(const Color &color)
{
    Vector3 p1(-1, -1, 1);
    Vector3 p2( 1, -1, 1);
    Vector3 p3( 1,  1, 1);
    Vector3 p4(-1,  1, 1);

    vertices.emplace_back(p1, color);
    vertices.emplace_back(p2, color);
    vertices.emplace_back(p3, color);
    vertices.emplace_back(p4, color);
    for (int i = 1; i < 6; i++)
    {
        Matrix4 rotationMatrix;
        if (i <= 3) rotationMatrix = Matrix4::rotateY(deg2rad(90.0 * i));
        if (i == 4) rotationMatrix = Matrix4::rotateX(deg2rad(90.0));
        if (i == 5) rotationMatrix = Matrix4::rotateX(deg2rad(-90.0));

        Vector4 result = rotationMatrix * Vector4(p1, 1.0);
        vertices.emplace_back(result.xyz(), color);

        result = rotationMatrix * Vector4(p2, 1.0);
        vertices.emplace_back(result.xyz(), color);

        result = rotationMatrix * Vector4(p3, 1.0);
        vertices.emplace_back(result.xyz(), color);

        result = rotationMatrix * Vector4(p4, 1.0);
        vertices.emplace_back(result.xyz(), color);
    }
}