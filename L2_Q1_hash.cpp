#include <iostream>
#include <vector>
#include <string>

int main() {
    // Definindo a palavra "PESQUISA"
    std::string palavra = "PESQUISA";
    
    // Criando uma tabela de dispersão com 7 listas encadeadas
    std::vector<char> tabela[7];
    
    // Inserindo os caracteres na tabela de dispersão
    for (char c : palavra) {
        int indice = (c - 'A') % 7;
        tabela[indice].push_back(c);
    }
    
    // Exibindo a tabela de dispersão e as listas encadeadas
    for (int i = 0; i < 7; i++) {
        std::cout << "Tabela[" << i << "]: ";
        for (char c : tabela[i]) {
            std::cout << c << " -> ";
        }
        // Usamos nullptr para representar o final da lista encadeada
        std::cout << "null" << std::endl;
    }
    
    return 0;
}
