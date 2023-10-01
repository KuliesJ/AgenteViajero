//HolaMundo
#include "graph.h"
#include "OpenGLRenderer.h"

int main() {
    //Solo estoy probando que todo funcione xd después el main desaparecerá
    Grafo grafo;

    Nodo* nodoA = new Nodo(0, 0);
    Nodo* nodoB = new Nodo(1, 1);
    Nodo* nodoC = new Nodo(2, 2);

    grafo.agregarNodo(nodoA);
    grafo.agregarNodo(nodoB);
    grafo.agregarNodo(nodoC);

    /*for (const Nodo* nodo : grafo.nodos) {
        std::cout << "Nodo " << nodo->etiqueta << " - Coordenadas: (" << nodo->coordenadas.first << ", " << nodo->coordenadas.second << ")" << std::endl;
        for (const Nodo* otroNodo : grafo.nodos) {
            if (nodo != otroNodo) {
                double distancia = grafo.calcularDistancia(*nodo, *otroNodo);
                std::cout << "  Distancia a Nodo " << otroNodo->etiqueta << ": " << distancia << std::endl;
            }
        }
    }*/

    OpenGLRenderer peanut(grafo);
    peanut.initialize();
    while(true){
        peanut.run();
    }

    // Liberar memoria de los nodos cuando ya no sean necesarios
    delete nodoA;
    delete nodoB;
    delete nodoC;


    return 0;
}
