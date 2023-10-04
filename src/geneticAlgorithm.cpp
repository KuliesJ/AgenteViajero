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
    
    // Crear un conjunto para rastrear los nodos ya presentes en el hijo
    std::unordered_set<Nodo*> nodosEnHijo(hijo.begin(), hijo.end());
    
    // Rellenar el resto de los elementos del hijo con los elementos del padre2
    int padre2Index = 0;
    for (int i = 0; i < tamano; ++i) {
        // Si el nodo ya está en el hijo, pasa al siguiente nodo en el padre2
        while (nodosEnHijo.count(padre2[padre2Index])) {
            padre2Index++;
        }
        hijo[i] = new Nodo(padre2[padre2Index]->coordenadas.first, padre2[padre2Index]->coordenadas.second);
        nodosEnHijo.insert(hijo[i]); // Agrega el nodo al conjunto
        padre2Index++;
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

double AlgoritmoGenetico::calcularDistanciaTotal(const std::vector<Nodo*>& ruta) {
    double distanciaTotal = 0;

    for (size_t i = 0; i < ruta.size() - 1; ++i) {
        distanciaTotal += grafo->calcularDistancia(*ruta[i], *ruta[i + 1]);
    }

    // Agregar la distancia de regreso al nodo inicial
    distanciaTotal += grafo->calcularDistancia(*ruta.back(), *ruta.front());

    return distanciaTotal;
}

std::vector<std::vector<Nodo*>> AlgoritmoGenetico::ejecutarAlgoritmoGenetico() {
    std::vector<std::vector<Nodo*>> mejoresIndividuos;
    for (int generacion = 0; generacion < generaciones; ++generacion) {
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

        int individuosFaltantes = individuos - nuevaGeneracion.size();
        mejoresIndividuos.push_back(poblacion[aptitudes[0].first]);

        for (int i = 0; i < individuosFaltantes; ++i) {
            double valorEsperado = aptitudes[i].second / mediaDistancias;
            int copias = static_cast<int>(std::round(valorEsperado));

            for (int j = 0; j < copias; ++j) {
                nuevaGeneracion.push_back(poblacion[aptitudes[i].first]); // Agregar copias de los individuos
            }
        }

        // Copiar el mejor individuo de la generación anterior si es necesario
        while (nuevaGeneracion.size() < individuos) {
            nuevaGeneracion.push_back(poblacion[aptitudes.back().first]);
        }

        // Realizar crossover ordenado entre parejas de individuos
        std::vector<std::vector<Nodo*>> descendencia;
        std::cout << "Individuos: " << nuevaGeneracion.size() << std::endl;
        for (int i = 0; i < individuos - 1; i += 2) {
            std::vector<Nodo*> hijo1 = orderedCrossover(nuevaGeneracion[i], nuevaGeneracion[i + 1]);
            std::vector<Nodo*> hijo2 = orderedCrossover(nuevaGeneracion[i + 1], nuevaGeneracion[i]);
            descendencia.push_back(hijo1);
            descendencia.push_back(hijo2);
        }

        // Imprimir el camino total de cada individuo
        for (int i = 0; i < individuos; ++i) {
            int distanciaTotal = calcularDistanciaTotal(descendencia[i]);
            std::cout << "Camino total del individuo " << i << ": " << distanciaTotal << std::endl;
        }

        // Reemplazar la población actual con la nueva generación y aplicar mutación si es necesario
        poblacion = descendencia;
    }
    return mejoresIndividuos;
}
