#include "geneticAlgorithm.h"

std::vector<Nodo*> orderedCrossover(const std::vector<Nodo*>& padre1, const std::vector<Nodo*>& padre2) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int tamanoRuta = padre1.size();
    std::vector<Nodo*> hijo(tamanoRuta, nullptr);

    int puntoCorte1 = std::rand() % tamanoRuta;
    int puntoCorte2 = (puntoCorte1 + (tamanoRuta / 2)) % tamanoRuta;

    if (puntoCorte1 > puntoCorte2) {
        std::swap(puntoCorte1, puntoCorte2);
    }

    // Copia la sección entre los puntos de corte del padre 1 al hijo
    for (int i = puntoCorte1; i <= puntoCorte2; i++) {
        hijo[i] = padre1[i];
    }

    // Copia los elementos del padre 2 al hijo en el orden en que aparecen,
    // omitiendo aquellos que ya están en el hijo
    int indexPadre2 = 0;
    for (int i = 0; i < tamanoRuta; i++) {
        if (hijo[i] == nullptr) {
            while (std::find(hijo.begin(), hijo.end(), padre2[indexPadre2]) != hijo.end()) {
                indexPadre2 = (indexPadre2 + 1) % tamanoRuta;
            }
            hijo[i] = padre2[indexPadre2];
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

double distanciaEntreNodos(const Nodo* nodo1, const Nodo* nodo2) {
    // Obtiene las coordenadas de ambos nodos
    int x1 = nodo1->coordenadas.first;
    int y1 = nodo1->coordenadas.second;
    int x2 = nodo2->coordenadas.first;
    int y2 = nodo2->coordenadas.second;

    // Calcula la distancia euclidiana entre los dos puntos
    double distancia = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distancia;
}

double calcularDistanciaTotal(const std::vector<Nodo*>& ruta) {
    double distanciaTotal = 0.0;
    
    for (size_t i = 0; i < ruta.size() - 1; i++) {
        distanciaTotal += distanciaEntreNodos(ruta[i], ruta[i + 1]);
    }
    
    distanciaTotal += distanciaEntreNodos(ruta[ruta.size()-1],ruta[0]);

    return distanciaTotal;
}

void imprimirNodos(const std::vector<Nodo*>& nodos) {
    for (const Nodo* nodo : nodos) {
        std::cout << "(" << nodo->coordenadas.first << ", " << nodo->coordenadas.second << "), ";
    }
    std::cout << std::endl;
}

void mutarPeorIndividuo(std::vector<Nodo*>& individuo) {
    int tamanoRuta = individuo.size();
    
    if (tamanoRuta < 2) {
        return; // No se puede realizar un swap con menos de dos nodos
    }

    // Elegir dos índices diferentes aleatoriamente
    int indice1 = std::rand() % tamanoRuta;
    int indice2 = std::rand() % tamanoRuta;
    
    while (indice1 == indice2) {
        indice2 = std::rand() % tamanoRuta;
    }

    // Realizar el swap entre los nodos en los índices seleccionados
    std::swap(individuo[indice1], individuo[indice2]);
}

// Llamada a la mutación en el peor individuo de la generación
void mutarPeorIndividuoDeGeneracion(std::vector<std::vector<Nodo*>>& generacion) {
    double peorDistancia = calcularDistanciaTotal(generacion[0]);
    int indicePeor = 0;

    // Encontrar el peor individuo en términos de distancia
    for (size_t i = 1; i < generacion.size(); i++) {
        double distancia = calcularDistanciaTotal(generacion[i]);
        if (distancia > peorDistancia) {
            peorDistancia = distancia;
            indicePeor = i;
        }
    }

    // Realizar la mutación en el peor individuo
    mutarPeorIndividuo(generacion[indicePeor]);
}

std::vector<std::vector<Nodo*>> AlgoritmoGenetico::ejecutarAlgoritmoGenetico() {
    std::vector<std::vector<Nodo*>> mejoresIndividuos;
    for (int generacion = 0; generacion < generaciones; generacion++) {
        printf("Generación %d:\n", generacion);

        double sumaDistancias = 0.0;
        std::vector<std::pair<int, double>> aptitudes; // Parejas (sujeto, distancia)

        for (int i = 0; i < individuos; ++i) {
            double distancia = calcularDistanciaTotal(poblacion[i]);
            aptitudes.push_back(std::make_pair(i, distancia));
            sumaDistancias += distancia;
            //printf("Distancia de individuo %d: %f\n", i, distancia);
        }

        // Calcular el promedio de las distancias de esta generación
        double mediaDistancias = sumaDistancias / individuos;
        printf("Promedio: %f\n", mediaDistancias);

        // Ordenar de mejor a no tan mejor
        std::sort(aptitudes.begin(), aptitudes.end(), [](const auto& a, const auto& b) {
            return a.second < b.second; // Ordenar por distancia ascendente
        });

        std::vector<std::vector<Nodo*>> nuevaGeneracion;
        nuevaGeneracion.reserve(individuos); // Reservar espacio para la nueva generación

        for (int i = 0; i < individuos; i++) {
            double valorEsperado = aptitudes[i].second / mediaDistancias;
            int copias = static_cast<int>(std::round(valorEsperado));

            for (int j = 0; j < copias; j++) {
                nuevaGeneracion.push_back(poblacion[aptitudes[i].first]); // Agregar copias de los individuos
            }
        }

        // Realizar crossover ordenado entre parejas de individuos
        std::vector<std::vector<Nodo*>> descendencia;
        for (int i = 0; i < individuos - 1; i += 2) {
            std::vector<Nodo*> hijo1 = orderedCrossover(nuevaGeneracion[i], nuevaGeneracion[i + 1]);
            std::vector<Nodo*> hijo2 = orderedCrossover(nuevaGeneracion[i + 1], nuevaGeneracion[i]);
            descendencia.push_back(hijo1);
            descendencia.push_back(hijo2);
        }

        // Mutar al peor individuo de la generación
        mutarPeorIndividuoDeGeneracion(descendencia);

        // Evaluar y mantener un registro de los mejores individuos en la nueva generación
        double mejorDistancia = calcularDistanciaTotal(descendencia[0]);
        std::vector<Nodo*> mejorIndividuo = descendencia[0];

        for (int i = 1; i < individuos; i++) {
            double distancia = calcularDistanciaTotal(descendencia[i]);
            if (distancia < mejorDistancia) {
                mejorDistancia = distancia;
                mejorIndividuo = descendencia[i];
            }
        }

        // Realizar la selección elitista para conservar una parte de los mejores individuos
        std::sort(poblacion.begin(), poblacion.end(), [this](const std::vector<Nodo*>& a, const std::vector<Nodo*>& b) {
            return calcularDistanciaTotal(a) < calcularDistanciaTotal(b);
        });

        for (int i = 0; i < poblacion.size(); i++) {
            if (i < descendencia.size()) {
                poblacion[i] = descendencia[i];
            }
        }

        mejoresIndividuos.push_back(mejorIndividuo);
    }

    return mejoresIndividuos;
}
