#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <vector>
#include <GL/freeglut.h>  // Asegúrate de que la biblioteca GLUT esté instalada y configurada en tu sistema
#include "graph.h"
class OpenGLRenderer {
public:
    OpenGLRenderer(std::vector<std::vector<Nodo*>> m, float w, float h);
    void run();

private:
    std::vector<std::vector<Nodo*>> caminos;
    int caminoActual;
    float screenWidth;
    float screenHeight;

    void draw();
    void update();

    static void displayCallback();
    static void updateCallback(int value);
};

#endif  // OPENGL_RENDERER_H

