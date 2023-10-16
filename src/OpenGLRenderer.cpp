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

void OpenGLRenderer::dibujarCamino(const std::vector<Nodo*>& camino) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f); // Color azul para el camino

    // Dibuja el camino como líneas entre nodos consecutivos
    glBegin(GL_LINES);
    for (size_t i = 0; i < camino.size() - 1; i++) {
        glVertex2f(camino[i]->coordenadas.first, camino[i]->coordenadas.second);
        glVertex2f(camino[i + 1]->coordenadas.first, camino[i + 1]->coordenadas.second);
    }
    glEnd();
}

void OpenGLRenderer::dibujarNodos(const std::vector<Nodo*>& nodos) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo para los nodos

    // Dibuja cada nodo como un punto
    glBegin(GL_POINTS);
    for (const Nodo* nodo : nodos) {
        glVertex2f(nodo->coordenadas.first, nodo->coordenadas.second);
    }
    glEnd();
}
#include <unistd.h>

void OpenGLRenderer::run() {
    // Configura la cámara y otras inicializaciones
    printf("Generaciones a dibujar: %d\n", caminos.size());
    int generacionActual = 0;

    while (!glfwWindowShouldClose(window)) {
        // Limpia el búfer de pantalla
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibuja el camino y los nodos de la generación actual
        if (generacionActual < caminos.size()) {
            //dibujarCamino(caminos[generacionActual]);
            //dibujarNodos(caminos[generacionActual]);
            drawPoints();
            sleep(1);
        }
        
        // Intercambia los buffers (doble búfer)
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Avanza a la siguiente generación (si corresponde)
        generacionActual++;
        
        // Puedes agregar una pausa o control de velocidad aquí si es necesario
        // Ejemplo: usleep(100000); // Pausa de 100 milisegundos
    }
}

void OpenGLRenderer::drawPoints() {
    // Dibuja un punto en el centro y uno en cada esquina de la ventana
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco

    glPointSize(5.0f); // Tamaño del punto

    glBegin(GL_POINTS);

    // Punto en el centro (ajustado al centro de la ventana)
    glVertex2f(screenWidth / 2, screenHeight / 2);

    // Puntos en las esquinas (ajustados a las esquinas de la ventana)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(screenWidth, 0.0f);
    glVertex2f(0.0f, screenHeight);
    glVertex2f(screenWidth, screenHeight);

    glEnd();
}

