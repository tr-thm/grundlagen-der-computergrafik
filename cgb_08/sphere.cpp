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

Sphere::Sphere(const Color &color, std::shared_ptr<Texture> &texture)
    : Mesh(texture)
{
    const int segments = 64;
    const int rings = segments / 2;
    const int vcount = segments * rings * 4;

    std::vector<std::vector<Vector3>> vectors(segments + 1, std::vector<Vector3>(rings + 1, Vector3(0.0, 0.0, 0.0)));

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
            double tw = 1.0 / segments;
            double th = 1.0 / rings;
            double ty = rings - y;
            vertices.emplace_back(vectors[x][y + 1], vectors[x][y + 1], color, Vector2(x * tw, (ty - 1) * th));
            vertices.emplace_back(vectors[x + 1][y + 1], vectors[x + 1][y + 1], color, Vector2((x + 1) * tw, (ty - 1) * th));
            vertices.emplace_back(vectors[x + 1][y], vectors[x + 1][y], color, Vector2((x + 1) * tw, (ty)*th));
            vertices.emplace_back(vectors[x][y], vectors[x][y], color, Vector2(x * tw, (ty)*th));
        }
    }
}