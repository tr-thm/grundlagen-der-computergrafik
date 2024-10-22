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
#include "cgmath.h"
#include "scene.h"

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <string>

class Renderer
{
  public:
    Renderer(const std::string &title, uint32_t width, uint32_t height);
    ~Renderer();
    void start();
    void printFps();
    void onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);

  private:
    GLFWwindow *window = nullptr;
    Camera activeCamera = Camera(0.0, 0.0, 3.0);
    double previousTime = 0.0;
    uint32_t frameCount = 0;
    uint32_t fps = 0;

    void renderScene(const Scene &scene) const;
};