#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "graph.h" // Asegúrate de incluir el archivo que contiene las clases Nodo y Grafo
#include <unordered_set>
class AlgoritmoGenetico {
private:
    int individuos;
    int generaciones;
    std::vector<std::vector<Nodo*>> poblacion;
    Grafo* grafo;

public:
    AlgoritmoGenetico(int individuos, int generaciones, Grafo* grafo);
    void inicializarPoblacion(const std::vector<Nodo*>& nodos);
    double calcularDistanciaTotal(const std::vector<Nodo*>& ruta);
    std::vector<std::vector<Nodo*>> ejecutarAlgoritmoGenetico();
};

std::vector<Nodo*> orderedCrossover(const std::vector<Nodo*>& padre1, const std::vector<Nodo*>& padre2);
