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

#include "sphere.h"

class Planet : public Sphere
{
  public:
    Planet(const Color &color, std::shared_ptr<Texture> &texture, std::shared_ptr<Texture> &specularTexture, std::shared_ptr<Texture> &nightTexture);
    void render() const override;

  private:
    void renderQuads(const float *worldMatrix) const;
    std::shared_ptr<Texture> specularTexture = nullptr;
    std::shared_ptr<Texture> nightTexture = nullptr;
};