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

#include "camera.h"

#include "cgmath.h"

#include <GLFW/glfw3.h>

Camera::Camera(double pitch, double yaw, double cameraDistance)
    : pitch(pitch), yaw(yaw), cameraDistance(cameraDistance)
{
}

Camera::~Camera()
{
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

void Camera::changeDistance(double deltaZ)
{
    double distance = cameraDistance - deltaZ * scrollSpeed;

    if (distance < 1.4) distance = 1.4;
    if (distance > 20.0) distance = 20.0;

    cameraDistance = distance;
}

void Camera::loadProjectionMatrix(double aspectRatio) const
{
    double zNear = 0.1;
    double zFar = 100.0;
    double fov = deg2rad(45.0);

    double h = zNear * tanf(fov * 0.5);
    double w = h * aspectRatio;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-w, w, -h, h, zNear, zFar);
}

void Camera::loadViewMatrix() const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Matrix4 translation = Matrix4::translate(0.0, 0.0, -cameraDistance);
    float translationF[16];
    translation.toColumnMajor(translationF);
    glMultMatrixf(translationF);

    Matrix4 pitchRotation = Matrix4::rotateX(deg2rad(-pitch));
    float pitchRotationF[16];
    pitchRotation.toColumnMajor(pitchRotationF);
    glMultMatrixf(pitchRotationF);

    Matrix4 yawRotation = Matrix4::rotateY(deg2rad(-yaw));
    float yawRotationF[16];
    yawRotation.toColumnMajor(yawRotationF);
    glMultMatrixf(yawRotationF);
}

void Camera::loadFixedViewMatrix() const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Matrix4 pitchRotation = Matrix4::rotateX(deg2rad(-pitch));
    float pitchRotationF[16];
    pitchRotation.toColumnMajor(pitchRotationF);
    glMultMatrixf(pitchRotationF);

    Matrix4 yawRotation = Matrix4::rotateY(deg2rad(-yaw));
    float yawRotationF[16];
    yawRotation.toColumnMajor(yawRotationF);
    glMultMatrixf(yawRotationF);
}