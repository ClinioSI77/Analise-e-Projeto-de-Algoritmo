#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

// Estrutura de um nó da Árvore Binária de Pesquisa
struct TreeNode {
    string word;
    int frequency;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string w) : word(w), frequency(1), left(nullptr), right(nullptr) {}
};

// Estrutura de um nó da Árvore AVL
struct AVLNode {
    string word;
    int frequency;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(string w) : word(w), frequency(1), height(1), left(nullptr), right(nullptr) {}
};

// Função para pré-processar o texto
string preprocessText(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower); // Converte para minúsculas
    text.erase(remove_if(text.begin(), text.end(), ::ispunct), text.end()); // Remove pontuações
    return text;
}

// Função para inserir uma palavra na Árvore Binária de Pesquisa
int binaryTreeInsert(TreeNode*& root, string word) {
    if (!root) {
        root = new TreeNode(word);
        return 1; // Primeira comparação
    }
    int comparisons = 0;
    if (word == root->word) {
        root->frequency++;
    } else if (word < root->word) {
        comparisons++;
        comparisons += binaryTreeInsert(root->left, word);
    } else {
        comparisons++;
        comparisons += binaryTreeInsert(root->right, word);
    }
    return comparisons;
}

// Função para calcular o tempo decorrido
double elapsedTime(clock_t start, clock_t end) {
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

// Função para obter a altura de um nó na Árvore AVL
int getHeight(AVLNode* node) {
    return (node != nullptr) ? node->height : 0;
}

// Função para calcular o fator de balanceamento de um nó
int getBalanceFactor(AVLNode* node) {
    return (node != nullptr) ? (getHeight(node->left) - getHeight(node->right)) : 0;
}

// Função para atualizar a altura de um nó na Árvore AVL
void updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

// Função para realizar uma rotação simples à direita na Árvore AVL
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Função para realizar uma rotação simples à esquerda na Árvore AVL
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Função para inserir uma palavra na Árvore AVL
int avlTreeInsert(AVLNode*& root, string word) {
    if (!root) {
        root = new AVLNode(word);
        return 1; // Primeira comparação
    }
    int comparisons = 0;
    if (word == root->word) {
        root->frequency++;
    } else if (word < root->word) {
        comparisons++;
        comparisons += avlTreeInsert(root->left, word);
    } else {
        comparisons++;
        comparisons += avlTreeInsert(root->right, word);
    }
    updateHeight(root);
    int balanceFactor = getBalanceFactor(root);
    // Verifica se é necessário reequilibrar a árvore
    if (balanceFactor > 1) {
        if (word < root->left->word) {
            // Rotação simples à direita
            root = rotateRight(root);
        } else {
            // Rotação dupla esquerda-direita
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    } else if (balanceFactor < -1) {
        if (word > root->right->word) {
            // Rotação simples à esquerda
            root = rotateLeft(root);
        } else {
            // Rotação dupla direita-esquerda
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return comparisons;
}

int main() {
    string filename = "edu.txt";  // Nome do arquivo de texto

    string text;
    vector<string> words;

    ifstream file(filename);
    if (!file) {
        cout << "Arquivo " << filename << " nao encontrado." << endl;
        return 1;
    }

    getline(file, text, '\0'); // Lê o conteúdo do arquivo como uma única string
    file.close();

    text = preprocessText(text);

    set<string> uniqueWords;  // Usado para pesquisa binária
    TreeNode* binaryRoot = nullptr;  // Árvore Binária de Pesquisa
    AVLNode* avlRoot = nullptr;  // Árvore AVL

    int binaryComparisons = 0;
    int avlComparisons = 0;

    size_t pos = 0;
    while ((pos = text.find_first_of(" ")) != string::npos) {
        string word = text.substr(0, pos);
        words.push_back(word);

        // Inserção na Árvore Binária de Pesquisa
        binaryComparisons += binaryTreeInsert(binaryRoot, word);

        // Inserção na Árvore AVL
        avlComparisons += avlTreeInsert(avlRoot, word);

        uniqueWords.insert(word);
        text.erase(0, pos + 1);
    }
    if (!text.empty()) {
        words.push_back(text);

        // Inserção na Árvore Binária de Pesquisa
        binaryComparisons += binaryTreeInsert(binaryRoot, text);

        // Inserção na Árvore AVL
        avlComparisons += avlTreeInsert(avlRoot, text);

        uniqueWords.insert(text);
    }

    // Ordena o vetor de palavras para pesquisa binária
    sort(words.begin(), words.end());

    cout << fixed << setprecision(2);

    cout << "Arvore_AVL:" << endl;
    cout << avlComparisons << " comparacoes" << endl;
    cout << elapsedTime(clock(), clock()) << " segundos" << endl;
    cout << "Arvore_Binaria:" << endl;
    cout << binaryComparisons << " comparacoes" << endl;
    cout << elapsedTime(clock(), clock()) << " segundos" << endl;
    cout << "Pesquisa_Binaria:" << endl;
    cout << uniqueWords.size() << " comparacoes" << endl;
    cout << elapsedTime(clock(), clock()) << " segundos" << endl;
    
    cout << "frequencia das palavras:" << endl;
    map<string, int> frequencyMap;
    for (const string& word : words) {
        frequencyMap[word]++;
    }
    for (const auto& entry : frequencyMap) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}
