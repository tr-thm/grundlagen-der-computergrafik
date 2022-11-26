#include <stdio.h>
#include "graphics.h"

static GLFWwindow* window;

int startGraphics(int width, int height)
{
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit())
    {
        printf("Error initilizing graphics.");
        return 1;
    }
    
    window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Error opening window.");
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
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