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

#include "renderer.h"

#include "cube.h"
#include "scene.h"
#include "sphere.h"

#include <iostream>

Renderer::Renderer(const std::string &title, uint32_t width, uint32_t height)
{
    glfwSetErrorCallback([](int error, const char *description)
    {
        std::cerr << "GLFW Error: " << description << std::endl;
    });

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to open window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Renderer *self = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
        self->onKeyboardInput(window, key, scancode, action, mods);
    });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *w, int width, int height)
    {
        Renderer *self = static_cast<Renderer *>(glfwGetWindowUserPointer(w));
        self->resized = true;
    });

    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1);
    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    double mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    activeCamera.changePosition(mousePositionX, mousePositionY);
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
    {
        Renderer *self = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
        self->activeCamera.changePosition(x, y);
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset)
    {
        Renderer *self = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
        self->activeCamera.changeDistance(yOffset);
    });
}

Renderer::~Renderer()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::start()
{
    auto cube1 = std::make_shared<Cube>(Color(0.5f, 0.73f, 0.14f, 1.0f));
    cube1->setPosition(Vector3(3.0, 0.0, 0.0));

    auto cube2 = std::make_shared<Cube>(Color(0.96f, 0.67f, 0.0f, 1.0f));
    cube2->setPosition(Vector3(-3.0, 0.0, 0.0));

    auto sphere = std::make_shared<Sphere>(Color(0.61f, 0.07f, 0.18f, 1.0f));

    Scene foreground;
    foreground.addMesh(cube1);
    foreground.addMesh(cube2);
    foreground.addMesh(sphere);

    setViewportSize();
    glClearColor(0.29f, 0.36f, 0.4f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        activeCamera.loadViewMatrix();
        foreground.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
        printFps();
        if (resized)
        {
            resized = false;
            setViewportSize();
        }
    }
}

void Renderer::onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods)
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

void Renderer::printFps()
{
    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        uint32_t fps = frameCount;
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }

    frameCount++;
}

void Renderer::setViewportSize()
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    activeCamera.loadProjectionMatrix(width / static_cast<float>(height));
}