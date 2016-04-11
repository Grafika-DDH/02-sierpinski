#include "GLFW/glfw3.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

/* initial triangle */
GLfloat v[3][2] = {
	{-0.6f, -0.4f},   // kiri
    {0.6f, -0.4f},    // kanan
    {0.f, 0.6f}       // atas 
};
int n; /* number of recursive steps */

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

void triangle(GLfloat *a, GLfloat *b, GLfloat *c, float color){
    glColor3f(color, color, color);
	glVertex2f(a[0], a[1]);
	glVertex2f(b[0], b[1]);
	glVertex2f(c[0], c[1]);
}

void insideTriangle(GLfloat *a, GLfloat *b, GLfloat *c, int m, float color){
    GLfloat *v0 = new GLfloat[3]; 
    GLfloat *v1 = new GLfloat[3]; 
    GLfloat *v2 = new GLfloat[3];
    int i;

    /*cout << color << endl;*/
    triangle(a, b, c, color);

    if(m > 0){
        for(i = 0; i < 2; i++) v0[i] = (a[i] + b[i]) / 2; // bawah
        for(i = 0; i < 2; i++) v1[i] = (a[i] + c[i]) / 2; // kiri
        for(i = 0; i < 2; i++) v2[i] = (b[i] + c[i]) / 2; // kanan

        insideTriangle(a, v0, v1, m-1, color+0.1); // segitiga dalam kiri
        insideTriangle(v0, b, v2, m-1, color+0.1); // segitiga dalam kanan
        insideTriangle(v1, v2, c, m-1, color+0.1); // segitiga dalam atas
    }

    delete v0;
    delete v1;
    delete v2;
}

int main(int argc, char **argv){
	char * windowName = "Graphics: 3d Cube";
    init_glfw_window(640, 480, windowName);
    int m = atoi(argv[1]);
    float color = 0.1;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBegin(GL_TRIANGLES);
        insideTriangle(v[0], v[1], v[2], m, color);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}
