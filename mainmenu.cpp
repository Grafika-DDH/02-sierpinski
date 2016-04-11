#include "GLFW/glfw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

double colors[1000][3] = {0};

typedef struct {
    float x, y, z;
} Vertex3D;

typedef struct {
    float r, g, b;
} Color3;

GLfloat triangle[3][3] =    {{-1.f,-1.f,0.f},
                            {0.f,1.f,0.f},
                            {1.f,-1.f,0.f}};

GLFWwindow* window;

static void errorCallback(int error, const char* description)
{
    fputs(description, stderr);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


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

void generateColors(){
    for(int i = 0; i < 1000; ++i){
        colors[i][0] = rand() / (double) RAND_MAX;
        colors[i][1] = rand() / (double) RAND_MAX;
        colors[i][2] = rand() / (double) RAND_MAX;
    }
}

void drawTriangleFill(GLfloat *a, GLfloat *b, GLfloat *c, int iterasi) {
    glBegin(GL_TRIANGLES);
        glColor3f(colors[iterasi][0], colors[iterasi][1], colors[iterasi][2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(b[0],b[1],b[2]);
        glVertex3f(c[0],c[1],c[2]);
    glEnd();
}

void drawTriangleWireFrame(GLfloat *a, GLfloat *b, GLfloat *c, int iterasi) {
    glBegin(GL_LINE_LOOP);
        glColor3f(colors[iterasi][0], colors[iterasi][1], colors[iterasi][2]);
        glVertex3f(a[0],a[1],a[2]);
        glVertex3f(b[0],b[1],b[2]);
        glVertex3f(c[0],c[1],c[2]);
    glEnd();
}

void drawSierpienski(GLfloat *a, GLfloat *b, GLfloat *c, int iteration, int pilihan) {
     GLfloat **v = new GLfloat*[3];
     v[0] = new GLfloat[3];
     v[1] = new GLfloat[3];
     v[2] = new GLfloat[3];
     int j;
     if (iteration > 0) {
        for (j = 0; j < 2; j++) {
            v[0][j] = (a[j] + b[j]) / 2;
        }
        for (j = 0; j < 2; j++) {
            v[1][j] = (a[j] + c[j]) / 2;
        }
        for (j = 0; j < 2; j++) {
            v[2][j] = (b[j] + c[j]) / 2;
        }
        v[0][2] = 0.f;
        v[1][2] = 0.f;
        v[2][2] = 0.f;

        if(pilihan == 2)drawTriangleFill(v[0],v[1],v[2],iteration);
        else drawTriangleWireFrame(v[0],v[1],v[2],iteration);

        drawSierpienski( a  , v[0], v[1], iteration-1,pilihan);
        drawSierpienski(v[0],  b  , v[2], iteration-1,pilihan);
        drawSierpienski(v[1], v[2],  c  , iteration-1,pilihan);

     } else {
        if(pilihan == 2) drawTriangleFill(a,b,c,iteration);
        //else drawTriangleWireFrame(a,b,c,iteration);
     }
     delete v;
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

void display(int pilihan, int iterasi = 0){
    if(pilihan == 1){
        drawTriangleWireFrame(triangle[0],triangle[1],triangle[2],0);
    }
    if(pilihan != 3) drawSierpienski(triangle[0],triangle[1],triangle[2],iterasi, pilihan);
    else drawRotatingCube(1.f, 1.f);
    
}

int main(void)
{
    int pilihan;
    char * windowName = "Graphics: 3d Cube";

    srand(time(NULL));
    generateColors();

    do{
        printf("Masukan pilihan: \n");
        printf("0. Exit \n");
        printf("1. Sierpinski titik\n");
        printf("2. Sierpinski warna\n");
        printf("3. Cube \n");
        printf("Masukan pilihan : ");
        scanf("%d",&pilihan);
        if(pilihan != 0){
            int iterasi;
            if(pilihan != 3){
                printf("Masukan jumlah iterasi : ");
                scanf("%d",&iterasi);
            }

            init_glfw_window(640, 480, windowName);

            while (!glfwWindowShouldClose(window))
            {
                float ratio;
                int width, height;
                glfwGetFramebufferSize(window, &width, &height);
                ratio = width / (float) height;
                glViewport(0, 0, width, height);
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
                glMatrixMode(GL_MODELVIEW);

                glMatrixMode(GL_MODELVIEW);
                glEnable(GL_DEPTH_TEST);
                
                display(pilihan,iterasi);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            glfwDestroyWindow(window);
            glfwTerminate();
            printf("\n");
        }
    }while(pilihan != 0);
}
