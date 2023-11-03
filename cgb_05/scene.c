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

#include <stdlib.h>
#include "scene.h"
#include "camera.h"

static const color thmGray = {0.29f, 0.36f, 0.4f, 1.0f};
static const color thmGreen = {0.5f, 0.73f, 0.14f, 1.0f};
static const color thmYellow = {0.96f, 0.67f, 0.0f, 1.0f};
static const color thmRed = {0.61f, 0.07f, 0.18f, 1.0f};

static mesh greenCube;
static mesh yellowCube;
static mesh redSphere;

void loadScene(GLFWwindow* window)
{
    setViewportSize(window);

    glClearColor(thmGray.r, thmGray.g, thmGray.b, thmGray.a);

    greenCube = createCubeMesh(thmGreen);
    yellowCube = createCubeMesh(thmYellow);
    redSphere = createSphereMesh(thmRed);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    loadCameraViewMatrix();

    renderMesh(yellowCube, matrixTranslate(-3,0,0));
    renderMesh(greenCube, matrixTranslate(3,0,0));
    renderMesh(redSphere, matrixTranslate(0,0,0));
}

void unloadScene()
{
    free(greenCube.vertices);
    free(yellowCube.vertices);
    free(redSphere.vertices);
}

void setViewportSize(GLFWwindow* window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    loadCameraProjectionMatrix((float)width / (float) height);
}

static void renderMesh(mesh m, matrix transform)
{
    glPushMatrix();
    glMultMatrixf((float*)&transform);
    glBegin(GL_QUADS);
    for (int i = 0; i < m.vcount; i++)
    {
        glColor3fv((float*)&m.vertices[i].color);
        glVertex3fv((float*)&m.vertices[i].pos);
    }
    glEnd();
    glPopMatrix();
}

static mesh createCubeMesh(color col)
{
    vertex* vertices = (vertex*)calloc(24, sizeof(vertex));
    vertices[0] = (vertex){ { -1, -1,  1 }, col };
    vertices[1] = (vertex){ {  1, -1,  1 }, col };
    vertices[2] = (vertex){ {  1,  1,  1 }, col };
    vertices[3] = (vertex){ { -1,  1,  1 }, col };
    for (int i = 1; i < 6; i++)
    {
        matrix rotationMatrix;
        if (i <= 3) rotationMatrix = matrixRotateY(deg2rad(90.0f * i));
        if (i == 4) rotationMatrix = matrixRotateX(deg2rad(90.0f));
        if (i == 5) rotationMatrix = matrixRotateX(deg2rad(-90.0f));
        vertices[i * 4 + 0] = (vertex){ matrixVector3Multiply(rotationMatrix, vertices[0].pos), col };
        vertices[i * 4 + 1] = (vertex){ matrixVector3Multiply(rotationMatrix, vertices[1].pos), col };
        vertices[i * 4 + 2] = (vertex){ matrixVector3Multiply(rotationMatrix, vertices[2].pos), col };
        vertices[i * 4 + 3] = (vertex){ matrixVector3Multiply(rotationMatrix, vertices[3].pos), col };
    }
    return (mesh) {
        .vcount = 24,
        .vertices = vertices
    };
}

static mesh createSphereMesh(color col)
{
    const int segments = 64;
    const int rings = segments / 2;
    
    int vcount = segments * rings * 4;
    vertex* vertices = (vertex*)calloc(vcount, sizeof(vertex));

    vector3** vectors = (vector3**)calloc(segments+1, sizeof(vector3*));
    for (int i = 0; i <= segments; i++)
    {
        vectors[i] = (vector3*)calloc(rings+1, sizeof(vector3));
    }
    
    for (int y = 0; y <= rings; y++)
    {
        float deg = 180.0f / rings * (y - rings * 0.5f);
        matrix rotationMatrixX = matrixRotateX(deg2rad(deg));
        vector3 startVector = matrixVector3Multiply(rotationMatrixX, (vector3){0,0,1});
        vectors[0][y] = startVector;
        vectors[segments][y] = startVector;
        for (int x = 1; x < segments; x++)
        {
            float deg2 = 360.0f / (float)segments * (float)x;
            matrix rotationMatrixY = matrixRotateY(deg2rad(deg2));
            vectors[x][y] = matrixVector3Multiply(rotationMatrixY, vectors[0][y]);
        }
    }
    int i = 0;
    for (int y = 0; y < rings; y++)
    {
        for (int x = 0; x < segments; x++)
        {
            vertices[i++] = (vertex){ vectors[ x ][y+1], col };
            vertices[i++] = (vertex){ vectors[x+1][y+1], col };
            vertices[i++] = (vertex){ vectors[x+1][ y ], col };
            vertices[i++] = (vertex){ vectors[ x ][ y ], col };
        }
    }
    for (int i = 0; i <= segments; i++)
    {
        free(vectors[i]);
    }
    free(vectors);
    return (mesh) {
        .vcount = vcount,
        .vertices = vertices
    };
}