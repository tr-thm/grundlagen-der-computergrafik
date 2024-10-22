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

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

class Camera
{
  public:
    Camera();
    Camera(double pitch, double yaw, double cameraDistance);
    ~Camera();
    void loadProjectionMatrix(float aspectRatio) const;
    void loadViewMatrix() const;
    void enableCameraMouseControl(GLFWwindow *window);

  private:
    double pitch;
    double yaw;

    // replace with vec3 as camera position?
    double cameraDistance;

    double mouseLastX;
    double mouseLastY;
    double scrollSpeed;
    double mouseSpeed;

    static void cursorPositionCallback(GLFWwindow *window, double x, double y);
    static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

    void changePosition(double x, double y);
    void changeDistance(double xOffset, double yOffset);
};