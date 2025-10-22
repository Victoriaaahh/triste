#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    int topo;
    int capacidade;
} Pilha;

void init(Pilha *pilha, int cap) {
    pilha->data = (char *)malloc(cap* sizeof(char)); //pode dar erro - se der, tira esse (char *)
    pilha->capacidade = cap;
    pilha->topo = -1;
}

void add(Pilha *pilha, char c) {
    if (pilha->topo > pilha->capacidade) {
        pilha->capacidade += 5;
        pilha->data = realloc(pilha->data, pilha->capacidade* sizeof(char));
    }
    pilha->data[++pilha->topo] = c;
}

char remover(Pilha *pilha) {
    if (pilha->topo < 0) {
        return '\0';
    }
    return pilha->data[pilha->topo--];
}

int Open(char c) {
    return (c == '(' || c == '[' || c == '{');
}

int Par(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

int main() {
    char c;
    Pilha pilha;
    int ruim = 0; 
    
    init(&pilha, 20);
    
    while (1) { 
        if (scanf(" %c", &c) != 1) 
            break; 
        if (c == '!') 
            break; 
        
        if (!Open(c) && !Par('(', c) && !Par('[', c) && !Par('{', c))
            continue;
        if (Open(c))
            add(&pilha, c);
        else {
            if (pilha.topo < 0)  
                ruim = 1;
            if (ruim == 0) {
                char topostr = remover(&pilha);
                if (!Par(topostr, c)) 
                    ruim = 1; 
            }
        }
    }
    if (ruim == 0 && pilha.topo == -1)
        printf("bem formada\n");
    else
        printf("mal formada\n");

    free(pilha.data);

    return 0;
}
