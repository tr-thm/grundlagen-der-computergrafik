#include <stdio.h>
#include "graphics.h"
#include "scene.h"
#include "camera.h"

static GLFWwindow* window;

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
    enableCameraMouseControl(window);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        renderScene(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        printFps();
    }
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