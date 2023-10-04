#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <vector>
#include <GLFW/glfw3.h> // Asegúrate de tener GLFW configurado correctamente
#include "graph.h"       // Asegúrate de incluir la definición de la clase Nodo

class OpenGLRenderer {
private:
    GLFWwindow* window;
    float screenWidth;
    float screenHeight;
    std::vector<std::vector<Nodo*>> caminos;

public:
    OpenGLRenderer(std::vector<std::vector<Nodo*>> m, float screenWidth = 800.0f, float screenHeight = 800.0f);
    ~OpenGLRenderer();

    void initialize();
    void run();

private:
    void dibujarNodo(const Nodo* nodo);
    void dibujarCamino(const std::vector<Nodo*>& camino);
};

#endif // OPENGL_RENDERER_H
