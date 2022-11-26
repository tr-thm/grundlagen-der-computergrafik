#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

static void errorCallback(int error, const char* description);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void printFps();

int startGraphics(int, int);