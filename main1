#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} FilaCircular;

void inicializarFila(FilaCircular *f, int capacidade) {
    f->data = (int *)malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}
void increase(FilaCircular *f, int k) {
    int novaCap = f->capacidade + k;
    int *novo = (int *)malloc(novaCap * sizeof(int));

    // copiar dados atuais na ordem correta
    for (int i = 0; i < f->tamanho; i++) {
        novo[i] = f->data[(f->inicio + i) % f->capacidade];
    }

    free(f->data);
    f->data = novo;
    f->capacidade = novaCap;
    f->inicio = 0;
    f->fim = f->tamanho;
}


void add(FilaCircular *f, int valor) {
    if (f->tamanho == f->capacidade) {
        increase(f,5);
    }
    
    f->data[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

void remover(FilaCircular *f) {
    if (f->tamanho == 0) {
        printf("fila vazia\n");
        return;
    }
    printf("%d\n", f->data[f->inicio]);
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
}

void list(FilaCircular *f) {
    if (f->tamanho == 0) {
        printf("\n");
        return;
    }
    int i = f->inicio;
    for (int count = 0; count < f->tamanho; count++) {
        printf("%d", f->data[i]);
        if (count < f->tamanho - 1)
            printf(" ");
        i = (i + 1) % f->capacidade;
    }
    printf("\n");
}

void printFila(FilaCircular *f) {
    for (int i = 0; i < f->capacidade; i++) {
        int pos = (f->inicio + i) % f->capacidade;
        if (i < f->tamanho)
            printf("%d ", f->data[pos]);
        else
            printf("- ");
    }
    printf("\n");
}


int main() {
    FilaCircular fila;
    int k;
    char comando[20];

    scanf("%d", &k);
    inicializarFila(&fila, k);

    while (1) {
        scanf("%s", comando);

        if (strcmp(comando, "ADD") == 0) {
            int n;
            scanf("%d", &n);
            add(&fila, n);
        } 
        else if (strcmp(comando, "REMOVE") == 0) {
            remover(&fila);
        } 
        else if (strcmp(comando, "LIST") == 0) {
            list(&fila);
        } 
        else if (strcmp(comando, "PRINT") == 0) {
            printFila(&fila);
        } 
        else if (strcmp(comando, "INCREASE") == 0) {
            int k;
            scanf("%d", &k);
            increase(&fila, k);
        } 
        else if (strcmp(comando, "END") == 0) {
            break;
        }
    }

    free(fila.data);
    return 0;
}
