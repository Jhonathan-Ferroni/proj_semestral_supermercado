// utils.h
#ifndef PILHAS_H
#define PILHAS_H

// Declaração das funções
int vertamanho (PILHA * p);
void exibirPilha(PILHA * p);
bool estaVazia(PILHA* p);
bool estaCheia(PILHA* p);
bool inserirElemPilha(PILHA* p, REGISTRO reg);
bool excluirElemPilha(PILHA* p, REGISTRO* reg);
void reinicializarPilha(PILHA* p);
// Funções de inicialização
void inicializarGondolas(PILHA gondolas[]);
void inicializarPilha(PILHA* p);
// Funções utilitárias
void exibirGondolas(PILHA gondolas[], int numGondolas);
void exibirCarrinho(CARRINHO* carrinho);
void menu(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario);

#endif
