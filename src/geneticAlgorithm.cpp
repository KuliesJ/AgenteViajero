#include "geneticAlgorithm.h"

std::vector<Nodo*> orderedCrossover(const std::vector<Nodo*>& padre1, const std::vector<Nodo*>& padre2) {
    int tamano = padre1.size();
    std::vector<Nodo*> hijo(tamano, nullptr);
    // Generar un punto de corte aleatorio
    int puntoCorte = rand() % tamano;
    
    // Copiar los elementos antes del punto de corte del padre1 al hijo
    for (int i = 0; i <= puntoCorte; ++i) {
        hijo[i] = new Nodo(padre1[i]->coordenadas.first, padre1[i]->coordenadas.second);
    }
    
    // Rellenar el resto de los elementos del hijo con los elementos del padre2
    int padre2Index = 0;
    for (int i = 0; i < tamano; ++i) {
        if (hijo[i] == nullptr) {
            while (std::find(hijo.begin(), hijo.end(), padre2[padre2Index]) != hijo.end()) {
                padre2Index++;
            }
            hijo[i] = new Nodo(padre2[padre2Index]->coordenadas.first, padre2[padre2Index]->coordenadas.second);
            padre2Index++;
        }
    }
    
    return hijo;
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
    for(int generacion = 0; generacion < generaciones; generacion++){
        printf("%d", generacion);
        std::vector<Nodo*> NuevaGeneracion;
        // Calcular la aptitud de cada individuo
        std::vector<std::pair<int, double>> aptitudes; // Parejas (índice de individuo, valor de aptitud)
        double sumaDistancias = 0.0;

        for (int i = 0; i < individuos; ++i) {
            int distancia = calcularDistanciaTotal(poblacion[i]);
            aptitudes.push_back(std::make_pair(i, distancia));
            sumaDistancias += distancia;
        }

        // Calcular el promedio de las distancias de esta generación
        double mediaDistancias = sumaDistancias / individuos;

        // Imprimir el promedio de distancias de esta generación
        std::cout << std::endl << "Promedio de distancias en la generación " << generacion << ": " << mediaDistancias << std::endl;

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
                std::cout << "Distancia de agregado: " << aptitudes[i].second << std::endl;
            }
        }
        // Realizar crossover ordenado entre parejas de individuos
        std::vector<std::vector<Nodo*>> descendencia;

        for (int i = 0; i < individuos - 1; i += 2) {
            //El error está aqui abajo
            std::vector<Nodo*> hijo1 = orderedCrossover(nuevaGeneracion[i], nuevaGeneracion[i + 1]);
            std::vector<Nodo*> hijo2 = orderedCrossover(nuevaGeneracion[i + 1], nuevaGeneracion[i]);
            //No tan abajo
            descendencia.push_back(hijo1);
            descendencia.push_back(hijo2);
        }

        // Reemplazar la población actual con la nueva generación y aplicar mutación si es necesario
        poblacion = descendencia;
    }
}
