#include <iostream>
#include <vector>
#include <list>

using namespace std;

class GrafoMatriz {
public:
    int V; // Número de vértices
    vector<vector<int>> matriz;

    GrafoMatriz(int vertices) : V(vertices) {
        matriz.resize(V, vector<int>(V, 0));
    }

    void adicionarAresta(int v1, int v2) {
        matriz[v1][v2] = 1;
        matriz[v2][v1] = 1;
    }

    void vizinhos(int vertice) {
        cout << "Vizinhos do vertice " << vertice << ": ";
        for (int i = 0; i < V; i++) {
            if (matriz[vertice][i] == 1) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    bool saoVizinhos(int v1, int v2) {
        return matriz[v1][v2] == 1;
    }

    void removerAresta(int v1, int v2) {
        matriz[v1][v2] = 0;
        matriz[v2][v1] = 0;
    }

    void imprimirMatrizAdjacencias() {
        cout << "Matriz de Adjacencias:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class GrafoLista {
public:
    int V; // Número de vértices
    list<int>* lista;

    GrafoLista(int vertices) : V(vertices) {
        lista = new list<int>[V];
    }

    void adicionarAresta(int v1, int v2) {
        lista[v1].push_back(v2);
        lista[v2].push_back(v1);
    }

    void vizinhos(int vertice) {
        cout << "Vizinhos do vertice " << vertice << ": ";
        for (int v : lista[vertice]) {
            cout << v << " ";
        }
        cout << endl;
    }

    bool saoVizinhos(int v1, int v2) {
        for (int v : lista[v1]) {
            if (v == v2) {
                return true;
            }
        }
        return false;
    }

    void removerAresta(int v1, int v2) {
        lista[v1].remove(v2);
        lista[v2].remove(v1);
    }

    void imprimirListaAdjacencias() {
        cout << "Lista de Adjacencias:" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Vertice " << i << ": ";
            for (int v : lista[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices;
    GrafoMatriz grafoMatriz(0); // Inicialização com 0 vértices
    GrafoLista grafoLista(0);   // Inicialização com 0 vértices

    int escolha;

    do {
        cout << "Escolha uma operacao basica para o grafo:" << endl;
        cout << "1. Definicao do Grafo" << endl;
        cout << "2. Adicao de Arestas" << endl;
        cout << "3. Determinacao de vizinhos de um dado vertice" << endl;
        cout << "4. Teste de vizinhanca entre par de vertices" << endl;
        cout << "5. Remocao de Arestas" << endl;
        cout << "0. Sair" << endl;
        cout << "Digite sua escolha: ";
        cin >> escolha;

        int v1, v2;

        switch (escolha) {
            case 1:
                cout << "Digite o numero de vertices: ";
                cin >> vertices;
                grafoMatriz = GrafoMatriz(vertices);
                grafoLista = GrafoLista(vertices);
                break;

            case 2:
                cout << "Digite os vertices a serem conectados: ";
                cin >> v1 >> v2;
                grafoMatriz.adicionarAresta(v1, v2);
                grafoLista.adicionarAresta(v1, v2);
                break;

            case 3:
                cout << "Digite o vertice para encontrar os vizinhos: ";
                cin >> v1;
                cout << "Vizinhos em GrafoMatriz: ";
                grafoMatriz.vizinhos(v1);
                cout << "Vizinhos em GrafoLista: ";
                grafoLista.vizinhos(v1);
                break;

            case 4:
                cout << "Digite dois vertices para verificar a vizinhanca: ";
                cin >> v1 >> v2;
                cout << "Sao vizinhos em GrafoMatriz? " << grafoMatriz.saoVizinhos(v1, v2) << endl;
                cout << "Sao vizinhos em GrafoLista? " << grafoLista.saoVizinhos(v1, v2) << endl;
                break;

            case 5:
                cout << "Digite os vertices para remover a aresta: ";
                cin >> v1 >> v2;
                grafoMatriz.removerAresta(v1, v2);
                grafoLista.removerAresta(v1, v2);
                break;

            case 0:
                cout << "Encerrando o programa." << endl;
                break;

            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (escolha != 0);

    grafoMatriz.imprimirMatrizAdjacencias();
    grafoLista.imprimirListaAdjacencias();

    return 0;
}
