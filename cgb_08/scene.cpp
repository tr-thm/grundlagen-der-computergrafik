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

#include "scene.h"

#include <GLFW/glfw3.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addMesh(const std::shared_ptr<Mesh> &mesh)
{
    meshes.push_back(mesh);
}

void Scene::render(const Camera &camera) const
{
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

    camera.loadViewMatrix();

    for (const std::shared_ptr<Mesh> &mesh : meshes)
    {
        mesh->render();
    }
}

void Scene::setLight(const Vector4 &position, const Color &diffuse, const Color &ambient, const Color &specular)
{
    float noLight[4] = {0.0, 0.0, 0.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, noLight);

    glEnable(GL_LIGHT1);

    lightPosition[0] = static_cast<float>(position.x);
    lightPosition[1] = static_cast<float>(position.y);
    lightPosition[2] = static_cast<float>(position.z);
    lightPosition[3] = static_cast<float>(position.w);

    float diffuseF[3] = {static_cast<float>(diffuse.r), static_cast<float>(diffuse.g), static_cast<float>(diffuse.b)};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseF);

    float ambientF[3] = {static_cast<float>(ambient.r), static_cast<float>(ambient.g), static_cast<float>(ambient.b)};
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientF);

    float specularF[3] = {static_cast<float>(specular.r), static_cast<float>(specular.g), static_cast<float>(specular.b)};
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularF);
}