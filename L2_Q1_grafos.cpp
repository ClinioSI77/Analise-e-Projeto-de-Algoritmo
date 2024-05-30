#include <iostream>
#include <vector>
#include <unordered_map>

// Define a estrutura do grafo
struct Graph {
    std::vector<int> vertices;
    std::unordered_map<std::string, std::pair<int, int>> edges;
};

int main() {
    Graph grafo;

    // Adiciona vértices ao grafo
    for (int i = 1; i <= 5; i++) {
        grafo.vertices.push_back(i);
    }

    // Mapeia as arestas para os vértices
    grafo.edges["a1"] = std::make_pair(1, 2);
    grafo.edges["a2"] = std::make_pair(1, 3);
    grafo.edges["a3"] = std::make_pair(3, 4);
    grafo.edges["a4"] = std::make_pair(3, 4); // A4 é uma aresta paralela a A3
    grafo.edges["a5"] = std::make_pair(4, 5);
    grafo.edges["a6"] = std::make_pair(5, 5); // A6 é um loop no vértice 5

    // Exibe os vértices e as arestas
    std::cout << "Vértices: ";
    for (int v : grafo.vertices) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Arestas:" << std::endl;
    for (const auto& edge : grafo.edges) {
        std::string nomeAresta = edge.first;
        int verticeOrigem = edge.second.first;
        int verticeDestino = edge.second.second;
        std::cout << nomeAresta << ": V" << verticeOrigem << " -> V" << verticeDestino << std::endl;
    }

    return 0;
}
	