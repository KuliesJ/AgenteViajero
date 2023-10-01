#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(Grafo& m, float w, float h)
    : window(nullptr), grafo(m), screenWidth(w), screenHeight(h) {
}

OpenGLRenderer::~OpenGLRenderer() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        OpenGLRenderer* renderer = static_cast<OpenGLRenderer*>(glfwGetWindowUserPointer(window));
        glfwGetCursorPos(window, &x, &y);
        std::cout << "Click en: " << x << " " << y << std::endl;
    }
}

void OpenGLRenderer::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetWindowUserPointer(window, this);
}