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
    camera.loadViewMatrix();

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);

    for (const std::shared_ptr<Mesh> &mesh : meshes)
    {
        mesh->render();
    }

    glDisable(GL_LIGHT1);
}

void Scene::setLight(const Vector4 &position, const Color &diffuse, const Color &ambient, const Color &specular)
{
    lightPosition[0] = static_cast<float>(position.x);
    lightPosition[1] = static_cast<float>(position.y);
    lightPosition[2] = static_cast<float>(position.z);
    lightPosition[3] = static_cast<float>(position.w);

    lightAmbient[0] = static_cast<float>(ambient.r);
    lightAmbient[1] = static_cast<float>(ambient.g);
    lightAmbient[2] = static_cast<float>(ambient.b);

    lightDiffuse[0] = static_cast<float>(diffuse.r);
    lightDiffuse[1] = static_cast<float>(diffuse.g);
    lightDiffuse[2] = static_cast<float>(diffuse.b);

    lightSpecular[0] = static_cast<float>(specular.r);
    lightSpecular[1] = static_cast<float>(specular.g);
    lightSpecular[2] = static_cast<float>(specular.b);
}