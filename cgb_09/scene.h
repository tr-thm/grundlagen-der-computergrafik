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

#include "camera.h"
#include "mesh.h"

#include <memory>
#include <vector>

class Scene
{
  public:
    Scene();
    ~Scene();
    void addMesh(const std::shared_ptr<Mesh> &mesh);
    void render(const Camera &camera) const;
    void setLight(const Vector4 &position, const Color &diffuse, const Color &ambient, const Color &specular);
    void enableDepthIsolation();
    void enableFixedPosition();

  private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    float lightPosition[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float lightAmbient[3] = {0.0f, 0.0f, 0.0f};
    float lightDiffuse[3] = {0.0f, 0.0f, 0.0f};
    float lightSpecular[3] = {0.0f, 0.0f, 0.0f};
    bool depthIsolation = false;
    bool fixedPosition = false;
};