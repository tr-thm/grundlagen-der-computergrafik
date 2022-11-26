#include <GLFW/glfw3.h>
#include "cgmath.h"

void loadScene(GLFWwindow* window);
void renderScene();
void setViewportSize(GLFWwindow* window);
void unloadScene();

static void renderMesh(mesh m, matrix transform, GLuint texture);

static mesh createCubeMesh(color col);
static mesh createSphereMesh(color col);
static mesh createCubeMap(color col);

static matrix calculateEarthRotation(float multiplier);
static matrix calculateSatellitePosition();