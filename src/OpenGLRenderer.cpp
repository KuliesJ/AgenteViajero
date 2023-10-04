#include "OpenGLRenderer.h"

#include <GLFW/glfw3.h>
#include "graph.h" // Asegúrate de incluir la definición de la clase Nodo
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(std::vector<std::vector<Nodo*>> m, float w, float h)
    : window(nullptr), screenWidth(w), screenHeight(h), caminos(m) {
}

OpenGLRenderer::~OpenGLRenderer() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void OpenGLRenderer::initialize() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        exit(-1);
    }

    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear ventana" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
}

void OpenGLRenderer::dibujarNodo(const Nodo* nodo) {
    // Configura el color y el tamaño del nodo
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    glPointSize(20.0f); // Tamaño del punto

    glBegin(GL_POINTS);
    glVertex2f(nodo->coordenadas.first, nodo->coordenadas.second); // Dibuja el nodo como un punto
    glEnd();
}


void OpenGLRenderer::dibujarCamino(const std::vector<Nodo*>& camino) {
    // Configura el color del camino
    glColor3f(0.0f, 0.0f, 1.0f); // Color azul

    glBegin(GL_LINE_STRIP); // Dibuja el camino como una serie de segmentos de línea
    for (const Nodo* nodo : camino) {
        glVertex2f(nodo->coordenadas.first, nodo->coordenadas.second); // Dibuja una línea al siguiente nodo en el camino
    }
    glEnd();
}

void OpenGLRenderer::run() {
    while (!glfwWindowShouldClose(window)) {
        // Configura el color y el tamaño del nodo
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        glPointSize(20.0f); // Tamaño del punto

        glBegin(GL_POINTS);
        glVertex2f(0.2, 0.2); // Dibuja el nodo como un punto
        glEnd();
        /*// Dibuja los nodos
        for (const auto& camino : caminos) {
            for (const Nodo* nodo : camino) {
                dibujarNodo(nodo);
            }
        }

        // Dibuja los caminos
        for (const auto& camino : caminos) {
            dibujarCamino(camino);
        }
        int wait = 0;
        std::cin >> wait;*/
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

