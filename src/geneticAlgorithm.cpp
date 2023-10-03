#include "geneticAlgorithm.h"

std::vector<Nodo*> crossoverSimple(const std::vector<Nodo*>& padre1, const std::vector<Nodo*>& padre2) {
    return padre1;
}


AlgoritmoGenetico::AlgoritmoGenetico(int individuos, int generaciones, Grafo* grafo)
    : individuos(individuos), generaciones(generaciones), grafo(grafo) {}

void AlgoritmoGenetico::inicializarPoblacion(const std::vector<Nodo*>& nodos) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < individuos; ++i) {
        std::vector<Nodo*> ruta = nodos;
        std::random_shuffle(ruta.begin(), ruta.end());
        poblacion.push_back(ruta);
    }
}

int AlgoritmoGenetico::calcularDistanciaTotal(const std::vector<Nodo*>& ruta) {
    int distanciaTotal = 0;

    for (size_t i = 0; i < ruta.size() - 1; ++i) {
        distanciaTotal += grafo->calcularDistancia(*ruta[i], *ruta[i + 1]);
    }

    // Agregar la distancia de regreso al nodo inicial
    distanciaTotal += grafo->calcularDistancia(*ruta.back(), *ruta.front());

    return distanciaTotal;
}

void AlgoritmoGenetico::ejecutarAlgoritmoGenetico() {
    for (int generacion = 0; generacion < generaciones; ++generacion) {
        // Calcular la aptitud de cada individuo
        std::vector<std::pair<int, double>> aptitudes; // Parejas (índice de individuo, valor de aptitud)
        double sumaDistancias = 0.0;

        for (int i = 0; i < individuos; ++i) {
            int distancia = calcularDistanciaTotal(poblacion[i]);
            aptitudes.push_back(std::make_pair(i, distancia));
            sumaDistancias += distancia;
        }

        // Calcular la media de las distancias
        double mediaDistancias = sumaDistancias / individuos;

        // Seleccionar individuos para la siguiente generación mediante selección por ranking
        std::vector<std::vector<Nodo*>> nuevaGeneracion;

        std::sort(aptitudes.begin(), aptitudes.end(), [](const auto& a, const auto& b) {
            return a.second < b.second; // Ordenar por distancia ascendente
        });

        for (int i = 0; i < individuos; ++i) {
            double valorEsperado = aptitudes[i].second / mediaDistancias;
            int copias = static_cast<int>(std::round(valorEsperado));

            for (int j = 0; j < copias; ++j) {
                nuevaGeneracion.push_back(poblacion[aptitudes[i].first]); // Agregar copias de los individuos
            }
        }

        // Realizar crossover de orden entre parejas de individuos
        std::vector<std::vector<Nodo*>> descendencia;

        for (int i = 0; i < individuos - 1; i += 2) {
            std::vector<Nodo*> hijo1 = crossoverSimple(nuevaGeneracion[i], nuevaGeneracion[i + 1]);
            std::vector<Nodo*> hijo2 = crossoverSimple(nuevaGeneracion[i + 1], nuevaGeneracion[i]);

            descendencia.push_back(hijo1);
            descendencia.push_back(hijo2);
        }

        // Reemplazar la población actual con la nueva generación y aplicar mutación si es necesario
        poblacion = descendencia;
    }
}