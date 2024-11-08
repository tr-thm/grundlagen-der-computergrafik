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
#include "sphere.h"

#include <iostream>
#include <stdexcept>

namespace Colors
{
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    Color sunLight = Color(0.9, 0.9, 0.9, 1.0);
    Color ambientLight = Color(0.1, 0.1, 0.1, 1.0);
}

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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

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
    Texture thmTexture = Texture("res/thm2k.png");
    Texture earthTexture = Texture("res/earth8k.jpg");

    Cube *cube1 = new Cube(Colors::white, thmTexture);
    cube1->setPosition(Vector3(3.0, 0.0, 0.0));

    Cube *cube2 = new Cube(Colors::white, thmTexture);
    cube2->setPosition(Vector3(-3.0, 0.0, 0.0));

    Sphere *sphere1 = new Sphere(Colors::white, earthTexture);

    Scene scene1;
    scene1.addMesh(cube1);
    scene1.addMesh(cube2);
    scene1.addMesh(sphere1);

    setViewportSize();
    glClearColor(0.29f, 0.36f, 0.4f, 1.0f);

    Vector4 lightPosition(50000, 20000, 50000, 0);
    scene1.setLight(lightPosition, Colors::sunLight, Colors::ambientLight, Colors::white);

    while (!glfwWindowShouldClose(window))
    {
        renderScene(scene1);
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

void Renderer::renderScene(Scene &scene) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    activeCamera.loadViewMatrix();

    scene.render();
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