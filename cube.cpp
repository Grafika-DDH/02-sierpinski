#include "GLFW/glfw3.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

typedef struct {
    float x, y, z;
} Vertex3D;

typedef struct {
    float r, g, b;
} Color3;

GLFWwindow* window;

static void errorCallback(int error, const char* description)
{
    fputs(description, stderr);
}

/**
 * Defining our key callback for the windows
 * @param window   [description]
 * @param key      [description]
 * @param scancode [description]
 * @param action   [description]
 * @param mods     [description]
 */
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

/**
 * Initialize GLFW window, to show our lovely OpenGL project
 * @param width      [description]
 * @param height     [description]
 * @param windowName [description]
 */
void init_glfw_window(int width, int height, const char * windowName) {

    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyCallback);
}

void drawSquare3d(Vertex3D vertex[4], Color3 color) {
    glBegin(GL_TRIANGLE_STRIP);
 
    glColor3f(color.r, color.g, color.b);

    for(int i = 0; i < 4; ++i)
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
     
    glEnd();
}

void drawRotatingCube(float edgeLength, float speed) {
    float max = edgeLength / 2;
    float min = -max;

    glRotatef(speed, 1.f, 0.f, 0.f);
    glRotatef(speed, 0.f, 1.f, 0.f);
    glRotatef(speed, 0.f, 0.f, 1.f);

    Vertex3D vertexSide1[4] = {
        { min, min, max },
        { max, min, max },
        { min, max, max },
        { max, max, max }
    };

    Vertex3D vertexSide2[4] = {
        { min, min, min },
        { max, min, min },
        { min, max, min },
        { max, max, min }
    };

    Vertex3D vertexSide3[4] = {
        { min, min, min },
        { min, max, min },
        { min, min, max },
        { min, max, max }
    };

    Vertex3D vertexSide4[4] = {
        { max, min, min },
        { max, max, min },
        { max, min, max },
        { max, max, max }
    };

    Vertex3D vertexSide5[4] = {
        { min, min, min },
        { min, min, max },
        { max, min, min },
        { max, min, max }
    };

    Vertex3D vertexSide6[4] = {
        { min, max, min },
        { min, max, max },
        { max, max, min },
        { max, max, max }
    };

    Color3 color1 = {0.5, 0, 0};
    Color3 color2 = {0, 0.5, 0};
    Color3 color3 = {0, 0, 0.5};

    drawSquare3d(vertexSide1, color1);
    drawSquare3d(vertexSide2, color1);
    drawSquare3d(vertexSide3, color2);
    drawSquare3d(vertexSide4, color2);
    drawSquare3d(vertexSide5, color3);
    drawSquare3d(vertexSide6, color3);
 
}

int main(void)
{
    char * windowName = "Graphics: 3d Cube";
    init_glfw_window(640, 480, windowName);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        drawRotatingCube(1.f, 1.f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
}
