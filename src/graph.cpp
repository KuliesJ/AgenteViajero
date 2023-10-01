#include "graph.h"

Nodo::Nodo(int x, int y) : coordenadas(std::make_pair(x, y)) {}

void Grafo::agregarNodo(Nodo* nuevoNodo) {
    nodos.push_back(nuevoNodo);
}

double Grafo::calcularDistancia(const Nodo& nodoA, const Nodo& nodoB) {
    double dx = nodoA.coordenadas.first - nodoB.coordenadas.first;
    double dy = nodoA.coordenadas.second - nodoB.coordenadas.second;
    return std::sqrt(dx * dx + dy * dy);
}