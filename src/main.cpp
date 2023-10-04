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

    int individuos = 4;
    int generaciones = 100;
    
    AlgoritmoGenetico algoritmoGenetico(individuos, generaciones, &grafo);
    // Inicializar la población inicial
    std::vector<Nodo*> nodos; // Rellenar con los nodos necesarios
    algoritmoGenetico.inicializarPoblacion(grafo.nodos);
    // Ejecutar el algoritmo genético
    std::vector<std::vector<Nodo*>> resultados = algoritmoGenetico.ejecutarAlgoritmoGenetico();
}
