//HolaMundo
#include "graph.h"
#include "OpenGLRenderer.h"
#include "geneticAlgorithm.h"

int main() {
    Grafo grafo;
    Nodo* ptrNodo;
    int datos[3];
    //[0]Numero de ciudades
    //[1]Numero de individuos
    //[2]NUmero de generaciones
    std::cout << "Ingresar número de: ciudades individuos y generaciones"<<std::endl;
    for(int i=0; i<3; i++){
        std::cin>>datos[i];
    }
    
    // Inicializa la semilla de rand() con la hora actual
    srand(static_cast<unsigned>(time(nullptr)));
    // Genera puntos en el mapa
    for(int i=0;i<datos[0];i++){
        int xAleatorio = 10 + rand() % 480;
        int yAleatorio = 10 + rand() % 480;
        ptrNodo = new Nodo(xAleatorio, yAleatorio);
        grafo.agregarNodo(ptrNodo);
        printf("Coords %d: (%d,%d)\n", i, xAleatorio, yAleatorio);
    };

    AlgoritmoGenetico algoritmoGenetico(datos[1], datos[2], &grafo);
    algoritmoGenetico.inicializarPoblacion(grafo.nodos);
    
    // Ejecutar el algoritmo genético
    std::vector<std::vector<Nodo*>> resultados = algoritmoGenetico.ejecutarAlgoritmoGenetico();
    
    OpenGLRenderer renderer(resultados,500,500);
    renderer.run();
}
