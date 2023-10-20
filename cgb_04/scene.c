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

#include "scene.h"
#include "camera.h"

void renderScene(GLFWwindow* window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glClearColor(0.29f,0.36f,0.4f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    loadCameraProjectionMatrix(width / (float) height);
    loadCameraViewMatrix();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.73f, 0.14f);
    glVertex3f(-0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.6f, 0.0f);
    glVertex3f(0.6f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.6f, 0.0f);
    glEnd();
}