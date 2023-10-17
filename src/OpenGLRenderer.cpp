#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(std::vector<std::vector<Nodo*>> m, float w, float h) : caminos(m), caminoActual(0), screenWidth(w), screenHeight(h) {
    int argc = 1;
    char *argv[1] = {(char*)"Traveller"};
    glutInit(&argc, argv);
    // Inicializa la ventana y configura OpenGL
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Traveller");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);  // Establece una proyección ortográfica
    glutDisplayFunc(displayCallback);
    glutSetWindowData(this);

    // Configura una función de temporizador para avanzar al siguiente camino
    glutTimerFunc(1000, updateCallback, 0);
}

void OpenGLRenderer::displayCallback() {
    OpenGLRenderer *visualizer = static_cast<OpenGLRenderer *>(glutGetWindowData());
    visualizer->draw();
    glutSwapBuffers();
}

void OpenGLRenderer::updateCallback(int value) {
    OpenGLRenderer *visualizer = static_cast<OpenGLRenderer *>(glutGetWindowData());
    visualizer->update();

    // Establece el próximo temporizador
    glutTimerFunc(1000, updateCallback, 0);
}

void OpenGLRenderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Tamaño de los puntos
    glPointSize(10.0);

    // Dibuja puntitos y líneas del camino actual
    if (caminoActual < caminos.size()) {
        const std::vector<Nodo*>& camino = caminos[caminoActual];

        // Dibuja líneas entre nodos consecutivos
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        for (size_t j = 0; j < camino.size() - 1; j++) {
            glVertex2f(camino[j]->coordenadas.first, camino[j]->coordenadas.second);
            glVertex2f(camino[j + 1]->coordenadas.first, camino[j + 1]->coordenadas.second);
        }
        glEnd();

        // Dibuja puntitos
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for (const Nodo* nodo : camino) {
            glVertex2f(nodo->coordenadas.first, nodo->coordenadas.second);
        }
        glEnd();
        //printf("Done %d\n",caminoActual);

        //¿?
        // Dibuja el número de camino actual en la parte superior derecha
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, screenWidth, 0, screenHeight);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(1.0, 1.0, 1.0);  // Color de texto
        glRasterPos2f(screenWidth - 75, screenHeight - 20);  // Posición de texto
        std::string caminoStr = "Camino " + std::to_string(caminoActual);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)caminoStr.c_str());

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
}

void OpenGLRenderer::update() {
    if (caminoActual < caminos.size()) {
        caminoActual++;  // Avanzar al próximo camino
        glutPostRedisplay();  // Solicitar un nuevo dibujo
    }
}

void OpenGLRenderer::run() {
    glutMainLoop();
}
