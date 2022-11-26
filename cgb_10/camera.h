#include <GLFW/glfw3.h>

void loadCameraProjectionMatrix(float ratio);
void loadCameraViewMatrix(int layer);
void enableCameraMouseControl(GLFWwindow* window);

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);