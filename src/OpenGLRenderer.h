#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GLFW/glfw3.h>
#include "graph.h"

class OpenGLRenderer {
private:
    GLFWwindow* window;
    Grafo& grafo;
    float screenWidth;
    float screenHeight;
public:
    OpenGLRenderer(Grafo& m, float screenWidth = 800.0f, float screenHeight = 800.0f);
    ~OpenGLRenderer();

    void initialize();
    void run();
};

#endif