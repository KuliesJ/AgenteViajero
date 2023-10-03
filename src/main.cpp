//HolaMundo
#include "graph.h"
#include "OpenGLRenderer.h"
#include "geneticAlgorithm.h"

int main() {
    Grafo grafo;
    Nodo* ptrNodo;
    for(int i = 0; i<10; i++){
        ptrNodo = new Nodo(i,i+3);
        grafo.agregarNodo(ptrNodo);
    }
    std::cout << "Test2";

    int individuos = 100;
    int generaciones = 100;
    
    AlgoritmoGenetico algoritmoGenetico(individuos, generaciones, &grafo);
    std::cout << "Test3";
    // Inicializar la población inicial
    std::vector<Nodo*> nodos; // Rellenar con los nodos necesarios
    algoritmoGenetico.inicializarPoblacion(grafo.nodos);
    std::cout << "Test4";
    // Ejecutar el algoritmo genético
    algoritmoGenetico.ejecutarAlgoritmoGenetico();
    std::cout << "Test5";
}
