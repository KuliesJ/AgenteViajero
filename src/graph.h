#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    std::pair<int, int> coordenadas;
    Nodo(int x, int y);
};

#endif

#ifndef GRAFO_H
#define GRAFO_H

class Grafo {
public:
    std::vector<Nodo*> nodos;  // Cambiamos a un vector de punteros a Nodo

    void agregarNodo(Nodo* nuevoNodo);  // Ahora recibe un puntero a Nodo

    double calcularDistancia(const Nodo& nodoA, const Nodo& nodoB);

private:
    
};

#endif
