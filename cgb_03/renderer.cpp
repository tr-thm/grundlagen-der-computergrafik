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
    glfwSetKeyCallback(window, [](GLFWwindow *w, int key, int scancode, int action, int mods)
    {
        auto renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(w));
        renderer->onKeyboardInput(w, key, scancode, action, mods);
    });

    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1);
}

Renderer::~Renderer()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::start()
{
    Scene squareScene;

    while (!glfwWindowShouldClose(window))
    {
        renderScene(squareScene);
        glfwSwapBuffers(window);
        glfwPollEvents();
        printFps();
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

void Renderer::renderScene(const Scene &scene) const
{
    scene.render(window);
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