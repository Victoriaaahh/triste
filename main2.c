#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    int topo;
    int capacidade;
} Pilha;

// Função auxiliar para liberar a memória de uma pilha
void liberar(Pilha *pilha) {
    if (pilha && pilha->data) {
        free(pilha->data);
        pilha->data = NULL;
    }
    pilha->capacidade = 0;
    pilha->topo = -1;
}

void init(Pilha *pilha, int cap) {
    if (cap <= 0) cap = 20;
    pilha->data = (char *)malloc(cap * sizeof(char));
    if (pilha->data == NULL) {
        fprintf(stderr, "Erro de alocação inicial de memória.\n");
        exit(EXIT_FAILURE);
    }
    pilha->capacidade = cap;
    pilha->topo = -1;
}

// Empilhar (PUSH)
void add(Pilha *pilha, char c) { 
    if (pilha->topo >= pilha->capacidade - 1) { 
        pilha->capacidade += 5;
        char *novo_data = (char *)realloc(pilha->data, pilha->capacidade * sizeof(char));
        
        if (novo_data == NULL) {
            fprintf(stderr, "Erro ao realocar memória. Falha no push.\n");
            exit(EXIT_FAILURE); 
        }
        pilha->data = novo_data;
    }
    pilha->data[++pilha->topo] = c;
}

// Desempilhar (POP)
char remover(Pilha *pilha) {
    if (pilha->topo < 0) {
        return '\0';
    }
    return pilha->data[pilha->topo--];
}

// Retorna 1 se for abertura, 0 caso contrário.
int ehAbertura(char c) {
    return (c == '(' || c == '[' || c == '{');
}

// Retorna 1 se os caracteres forem pares, 0 caso contrário.
int ehParCorrespondente(char abertura, char fechamento) {
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

int main() {
    char c;
    Pilha pilha;
    // Usando 0 para Falso e 1 para Verdadeiro
    int mal_formada = 0; 
    
    init(&pilha, 20);
    
    // Loop principal: processa a entrada caractere por caractere
    while (1) { // Usa 1 para loop infinito (TRUE)
        // Lê um caractere, ignorando espaços em branco e ENTERs
        if (scanf(" %c", &c) != 1) {
            // Se o scanf falhar (EOF), sai
            break; 
        }

        // Condição de parada: se encontrar '!', sai do loop
        if (c == '!') {
            break; 
        }
        
        // --- Algoritmo de Validação ---
        
        // Ignora caracteres que não são delimitadores
        if (!ehAbertura(c) && !ehParCorrespondente('(', c) && !ehParCorrespondente('[', c) && !ehParCorrespondente('{', c)) {
            continue;
        }
        
        if (ehAbertura(c)) {
            add(&pilha, c);
        } else {
            // Se for fechamento:
            
            if (pilha.topo < 0) { // Pilha vazia
                mal_formada = 1; // 1 = Verdadeiro
            }

            // Apenas tenta remover e verificar se 'mal_formada' ainda é FALSO (0)
            if (mal_formada == 0) {
                char topo_removido = remover(&pilha);

                if (!ehParCorrespondente(topo_removido, c)) {
                    mal_formada = 1; // 1 = Verdadeiro
                }
            }
        }
    }
    
    // --- Verificação Final e Impressão do Resultado ---
    
    // A pilha só está 'bem formada' se mal_formada for FALSO (0) E a pilha estiver vazia
    if (mal_formada == 0 && pilha.topo == -1) {
        printf("bem formada\n");
    } else {
        printf("mal formada\n");
    }

    liberar(&pilha);

    return 0;
}
