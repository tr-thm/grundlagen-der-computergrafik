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

#include <stdio.h>
#include "graphics.h"
#include "scene.h"
#include "camera.h"

static GLFWwindow* window;
static int resized = 0;

int startGraphics(int width, int height)
{
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit())
    {
        printf("Error initilizing graphics.");
        return 1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Error opening window.");
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    enableCameraMouseControl(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    loadScene(window);
    while (!glfwWindowShouldClose(window))
    {
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
        printFps();
        if (resized)
        {
            resized = 0;
            setViewportSize(window);
        }
    }
    unloadScene();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

static void errorCallback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
        {
            glfwRestoreWindow(window);
        }
        else
        {
            glfwMaximizeWindow(window);
        }
    }
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    resized = 1;
}

static void printFps()
{
    static double previousTime = 0;
    static int frameCount = 0;

    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        printf("FPS: %i\n", frameCount);

        frameCount = 0;
        previousTime = currentTime;
    }
    frameCount++;
}