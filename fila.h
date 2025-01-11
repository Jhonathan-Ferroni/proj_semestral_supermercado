#ifndef FILA_H
#define FILA_H

#include "main.h"

typedef struct nodoFila {
    REGISTRO regf; // Alterado de reg para regf
    struct nodoFila* prox;
} NODOFILA;

typedef struct {
    NODOFILA* inicio;
    NODOFILA* fim;
} FILA;

void inicializarFila(FILA* f);
bool estaVaziaFila(FILA* f);
bool inserirNaFila(FILA* f, REGISTRO reg);
bool removerDaFila(FILA* f, REGISTRO* reg);
void caixaEletronico(CARRINHO* carrinho, PILHA gondolas[]);

#endif // FILA_H
