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

#include "camera.h"

Camera::Camera()
    : pitch(0.0), yaw(0.0), cameraDistance(0.0), mouseLastX(0.0), mouseLastY(0.0), scrollSpeed(0.1), mouseSpeed(0.05)
{
}

Camera::Camera(double pitch, double yaw, double cameraDistance)
    : pitch(pitch), yaw(yaw), cameraDistance(cameraDistance), mouseLastX(0.0), mouseLastY(0.0), scrollSpeed(0.1), mouseSpeed(0.05)
{
}

Camera::~Camera()
{
}

void Camera::loadProjectionMatrix(float aspectRatio) const
{
    float zNear = 0.1f;
    float zFar = 100.0f;
    float fov = deg2rad(45.0f);

    float h = zNear * tanf(fov * 0.5f);
    float w = h * aspectRatio;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, zNear, zFar);
}

void Camera::loadViewMatrix() const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Matrix4 translation = Matrix4::translate(0.0, 0.0, -cameraDistance);
    glMultMatrixf(translation.toFloat());

    Matrix4 pitchRotation = Matrix4::rotateX(deg2rad(-pitch));
    glMultMatrixf(pitchRotation.toFloat());

    Matrix4 yawRotation = Matrix4::rotateY(deg2rad(-yaw));
    glMultMatrixf(yawRotation.toFloat());
}

void Camera::enableCameraMouseControl(GLFWwindow *window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwGetCursorPos(window, &mouseLastX, &mouseLastY);
    glfwSetWindowUserPointer(window, this);
}

void Camera::cursorPositionCallback(GLFWwindow *window, double x, double y)
{
    Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    camera->changePosition(x, y);
}

void Camera::scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    camera->changeDistance(xOffset, yOffset);
}

void Camera::changePosition(double x, double y)
{
    double deltaX = x - mouseLastX;
    mouseLastX = x;

    double yaw = this->yaw - deltaX * mouseSpeed;

    while (yaw < 0)
    {
        yaw += 360;
    }
    while (yaw > 360)
    {
        yaw -= 360;
    }

    this->yaw = yaw;

    double deltaY = y - mouseLastY;
    mouseLastY = y;

    double pitch = this->pitch - deltaY * mouseSpeed;

    if (pitch < -90) pitch = -90;
    if (pitch > 90) pitch = 90;

    this->pitch = pitch;
}

void Camera::changeDistance(double xOffset, double yOffset)
{
    double distance = cameraDistance - yOffset * scrollSpeed;

    if (distance < 1.4) distance = 1.4;
    if (distance > 20.0) distance = 20.0;

    cameraDistance = distance;
}