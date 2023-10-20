/**
 * Grundlagen der Computergrafik
 * Copyright (C) 2023 Tobias Reimann
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

#include <math.h>
#include "camera.h"
#include "cgmath.h"

static double cameraPitch = 0.0;
static double cameraYaw = 0.0;
static double cameraDistance = 3.0;

static double mouseLastX = 0.0;
static double mouseLastY = 0.0;

static double scrollSpeed = 0.1;
static double mouseSpeed = 0.05;

void enableCameraMouseControl(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwGetCursorPos(window, &mouseLastX, &mouseLastY);
}

void loadCameraProjectionMatrix(float aspect)
{
    float zNear = 0.1f;
    float zFar = 100.0f;
    float fov = deg2rad(45.0f);

    float h = zNear * tanf(fov * 0.5f);
    float w = h * aspect;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, zNear, zFar);
}

void loadCameraViewMatrix()
{
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    matrix translationMatrix = matrixTranslate(0.0f, 0.0f, -cameraDistance);
    glMultMatrixf((float*)&translationMatrix);
    matrix pitchRotationMatrix = matrixRotateX(deg2rad(-cameraPitch));
    glMultMatrixf((float*)&pitchRotationMatrix);
    matrix yawRotationMatrix = matrixRotateY(deg2rad(-cameraYaw));
    glMultMatrixf((float*)&yawRotationMatrix);
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    double deltaX = xpos - mouseLastX;
    mouseLastX = xpos;

    double yaw = cameraYaw - deltaX * mouseSpeed;
    
    while (yaw < 0) yaw += 360;
    while (yaw > 360) yaw -= 360;

    cameraYaw = yaw;

    double deltaY = ypos - mouseLastY;
    mouseLastY = ypos;

    double pitch = cameraPitch - deltaY * mouseSpeed;
    
    if (pitch < -90) pitch = -90;
    if (pitch > 90) pitch = 90;

    cameraPitch = pitch;
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    double distance = cameraDistance - yoffset * scrollSpeed;

    if (distance < 1.4) distance = 1.4;
    if (distance > 20.0) distance = 20.0;

    cameraDistance = distance;
}