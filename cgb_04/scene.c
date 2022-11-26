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