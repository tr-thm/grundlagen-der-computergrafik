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

#pragma once

#include "cgmath.h"
#include "texture.h"

#include <memory>
#include <vector>

class Mesh
{
  public:
    Mesh(std::shared_ptr<Texture> &texture);
    virtual ~Mesh() = default;
    virtual void render() const;
    void setPosition(const Vector3 &position);
    void setRotation(const Vector3 &rotation);
    void setScale(const double scale);

  protected:
    Matrix4 position = Matrix4::translate(0, 0,0);
    Matrix4 rotation = Matrix4::rotateX(0.0);
    Matrix4 scale = Matrix4::scale(1.0);
    std::vector<Vertex> vertices = {};
    std::shared_ptr<Texture> texture = nullptr;
};