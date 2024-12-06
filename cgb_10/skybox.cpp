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

#include "skybox.h"

Skybox::Skybox(const Color &color, std::shared_ptr<Texture> &texture)
    : Mesh(texture)
{
    vertices.reserve(24);

    // +y
    vertices.push_back(Vertex({1, 1, -1}, {0, -1, 0}, color, {2 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({1, 1, 1}, {0, -1, 0}, color, {2 / 3.f, 2 / 2.f}));
    vertices.push_back(Vertex({-1, 1, 1}, {0, -1, 0}, color, {1 / 3.f, 2 / 2.f}));
    vertices.push_back(Vertex({-1, 1, -1}, {0, -1, 0}, color, {1 / 3.f, 1 / 2.f}));

    // +z
    vertices.push_back(Vertex({1, -1, 1}, {0, 0, -1}, color, {2 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({-1, -1, 1}, {0, 0, -1}, color, {3 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({-1, 1, 1}, {0, 0, -1}, color, {3 / 3.f, 2 / 2.f}));
    vertices.push_back(Vertex({1, 1, 1}, {0, 0, -1}, color, {2 / 3.f, 2 / 2.f}));

    // -x
    vertices.push_back(Vertex({-1, -1, 1}, {1, 0, 0}, color, {0 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({-1, -1, -1}, {1, 0, 0}, color, {1 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({-1, 1, -1}, {1, 0, 0}, color, {1 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({-1, 1, 1}, {1, 0, 0}, color, {0 / 3.f, 1 / 2.f}));

    // -y
    vertices.push_back(Vertex({-1, -1, -1}, {0, 1, 0}, color, {1 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({-1, -1, 1}, {0, 1, 0}, color, {1 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({1, -1, 1}, {0, 1, 0}, color, {2 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({1, -1, -1}, {0, 1, 0}, color, {2 / 3.f, 1 / 2.f}));

    // +x
    vertices.push_back(Vertex({1, -1, -1}, {-1, 0, 0}, color, {0 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({1, -1, 1}, {-1, 0, 0}, color, {1 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({1, 1, 1}, {-1, 0, 0}, color, {1 / 3.f, 2 / 2.f}));
    vertices.push_back(Vertex({1, 1, -1}, {-1, 0, 0}, color, {0 / 3.f, 2 / 2.f}));

    // -z
    vertices.push_back(Vertex({-1, -1, -1}, {0, 0, 1}, color, {2 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({1, -1, -1}, {0, 0, 1}, color, {3 / 3.f, 0 / 2.f}));
    vertices.push_back(Vertex({1, 1, -1}, {0, 0, 1}, color, {3 / 3.f, 1 / 2.f}));
    vertices.push_back(Vertex({-1, 1, -1}, {0, 0, 1}, color, {2 / 3.f, 1 / 2.f}));
}