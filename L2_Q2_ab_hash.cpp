#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Hash {
private:
    struct HashNode {
        std::string key;
        T value;
        HashNode* next;

        HashNode(const std::string& k, const T& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<HashNode*> table;
    size_t tableSize;

    size_t hash(const std::string& key) {
        size_t hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % tableSize;
        }
        return hashValue;
    }

public:
    Hash(size_t size) : tableSize(size) {
        table.resize(tableSize, nullptr);
    }

    void insert(const std::string& key, const T& value) {
        size_t index = hash(key);
        HashNode* newNode = new HashNode(key, value);
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            HashNode* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool find(const std::string& key, T& result) {
        size_t index = hash(key);
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                result = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(const std::string& key) {
        size_t index = hash(key);
        HashNode* current = table[index];
        HashNode* previous = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    table[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
};

int main() {
    Hash<int> hashTable(20);

    while (true) {
        int choice;
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Inserir chave-valor" << std::endl;
        std::cout << "2. Consultar valor por chave" << std::endl;
        std::cout << "3. Remover chave" << std::endl;
        std::cout << "4. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string key;
            int value;
            std::cout << "Insira a chave: ";
            std::cin >> key;
            std::cout << "Insira o valor: ";
            std::cin >> value;
            hashTable.insert(key, value);
        } else if (choice == 2) {
            std::string key;
            int value;
            std::cout << "Insira a chave para consulta: ";
            std::cin >> key;
            if (hashTable.find(key, value)) {
                std::cout << "Valor para a chave '" << key << "': " << value << std::endl;
            } else {
                std::cout << "Chave '" << key << "' nao encontrada." << std::endl;
            }
        } else if (choice == 3) {
            std::string key;
            std::cout << "Insira a chave para remover: ";
            std::cin >> key;
            hashTable.remove(key);
            std::cout << "Chave '" << key << "' removida." << std::endl;
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    }

    return 0;
}
