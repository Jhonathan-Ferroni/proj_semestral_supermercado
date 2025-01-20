#ifndef PILHAS_H
#define PILHAS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAXTAM 5
#define NUM_GONDOLAS 10


typedef struct
{
    char nome[50];
    char pront[14];
    char user[2];
} reg;

typedef struct
{
    char NOMEPROD[100 + 1];
    char desc[100 + 1];
    float peso, preco;
} REGISTRO;

typedef struct
{
    REGISTRO elementos[MAXTAM];
    int topo;
} PILHA;

/*struct do carrinho*/

typedef struct nodo {
    REGISTRO reg;
    struct nodo* PROX;
} NODO, * PONT;

typedef struct
{
    PONT topo;
} CARRINHO;


// Declaração das funções
bool estaVazioCarrinho(CARRINHO* carrinho); 
int vertamanho(PILHA* p);
void exibirPilha(PILHA* p);
bool estaVazia(PILHA* p);
bool estaCheia(PILHA* p);
bool inserirElemPilha(PILHA* p, REGISTRO reg);
bool excluirElemPilha(PILHA* p, REGISTRO* reg);
void reinicializarPilha(PILHA* p);
void adicionarproduto(PILHA gondolas[]);
void salvarPilhaEmArquivo(PILHA* p, const char* nomeArquivo);
bool carregarPilhaDeArquivo(PILHA* p, const char* nomeArquivo);
void exibirRegistros(reg* registros, int n);
bool moveritemparacarrinho(PILHA* gondola, CARRINHO* carrinho);
// Funções de inicialização
void inicializarGondolas(PILHA gondolas[]);
void inicializarPilha(PILHA* p);
// Funções utilitárias
void exibirGondolas(PILHA gondolas[], int numGondolas);
void exibirCarrinho(CARRINHO* carrinho);
void menupilhas(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario); // Alterado de menu() para menupilhas()

#endif