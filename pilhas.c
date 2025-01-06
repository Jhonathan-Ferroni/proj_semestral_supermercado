#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "pilhas.h"

int vertamanho(PILHA* p);
void exibirPilha(PILHA* p);
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
void menupilhas(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario); // Alterado de menuprincipal() para menupilhas()

// Funções principais
int pilha(char usuario) {
    PILHA gondolas[NUM_GONDOLAS];
    CARRINHO carrinho;
    carrinho.topo = NULL;

    inicializarGondolas(gondolas);

    printf("Menu de opções\n");
    menupilhas(gondolas, NUM_GONDOLAS, &carrinho, usuario); // Alterado de menuprincipal() para menupilhas()

    return 0;
}

/*----------------------------*/

void inicializarGondolas(PILHA gondolas[])
{
    int i;
    for (i = 0; i < NUM_GONDOLAS; i++)
    {
        inicializarPilha(&gondolas[i]);
    }
}

void inicializarPilha(PILHA* p)
{
    p->topo = -1;
}

void menupilhas(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario) { // Alterado de menuprincipal() para menupilhas()
    int opcao;
    if (usuario == 'u')
        do {
            printf("\nEscolha uma opção:\n");
            printf("1. Visualizar gôndolas\n");
            printf("2. Visualizar carrinho\n");
            printf("3. Caixa\n");
            printf("0. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                exibirGondolas(gondolas, numGondolas);
                break;
            case 2:
                exibirCarrinho(carrinho);
                break;
            case 3:
                ////////FUNCAO CAIXA((((((((((((())))))))))))) 
                break;
            case 0:
                printf("\nSaindo\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
            }
        } while (opcao != 0);
    if (usuario == 'r')
        do {
            printf("\nEscolha uma opção:\n");
            printf("1. Abastecer gôndolas\n");
            printf("2. Gerenciar usuários\n");
            printf("0. Sair\n");
            printf("Opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                exibirGondolas(gondolas, numGondolas);
                break;
            case 2: {
                reg* registros;
                int n = carregavetor("USUARIOS.DAT", &registros);
                if (n > 0) {
                    exibirRegistros(registros, n);
                    free(registros);
                }
                else {
                    printf("Erro ao carregar registros.\n");
                }
                break;
            }
            case 0:
                printf("\nSaindo\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
            }
        } while (opcao != 0);
}

void exibirGondolas(PILHA gondolas[], int numGondolas) {
    printf("\nProdutos nas gôndolas:\n");
    for (int i = 0; i < numGondolas; i++) {
        printf("\nGôndola %d:\n", i + 1);
        for (int j = 0; j <= gondolas[i].topo; j++) {
            REGISTRO produto = gondolas[i].elementos[j];
            printf("Produto: %s | Preço: %d | Vencimento: %s | Validade: %s\n",
                produto.NOMEPROD, produto.preco, produto.DATAVENC, produto.DATAVAL);
        }
    }
}

void exibirCarrinho(CARRINHO* carrinho) {
    printf("\nItens no carrinho:\n");
    PONT atual = carrinho->topo;
    while (atual != NULL) {
        printf("Produto: %s | Preço: %d | Vencimento: %s | Validade: %s\n",
            atual->reg.NOMEPROD, atual->reg.preco, atual->reg.DATAVENC, atual->reg.DATAVAL);
        atual = atual->PROX;
    }
    if (carrinho->topo == NULL) {
        printf("O carrinho está vazio.\n");
    }
}

/*----------------------------*/

int vertamanho(PILHA* p) {
    return p->topo + 1; // O topo indica o índice do último elemento. +1 dá o número de elementos.
}

void exibirPilha(PILHA* p) {
    if (p->topo == -1) {
        printf("A pilha está vazia.\n");
        return;
    }
    printf("Itens na pilha:\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("Nome: %s, Preço: %d, Data de Vencimento: %s, Data de Validade: %s\n",
            p->elementos[i].NOMEPROD, p->elementos[i].preco,
            p->elementos[i].DATAVENC, p->elementos[i].DATAVAL);
    }
}

bool estaVazia(PILHA* p)
{
    if (p->topo == -1)
        return true;
    return false;
}

bool estaCheia(PILHA* p) {
    if (p->topo == MAXTAM - 1) {
        return true;  // A pilha está cheia
    }
    return false;  // A pilha não está cheia
}

bool inserirElemPilha(PILHA* p, REGISTRO reg)
{
    if (p->topo == MAXTAM - 1)  // Verifica se a pilha está cheia
        return false;
    // Insere o item no topo da pilha
    p->topo++;
    p->elementos[p->topo] = reg;  // Atribui o registro à posição indicada por topo
    return true;
}

bool excluirElemPilha(PILHA* p, REGISTRO* reg)
{
    if (p->topo == -1)  // Verifica se a pilha está vazia
        return false;

    *reg = p->elementos[p->topo];  // Atribui o elemento do topo à variável reg
    p->topo--;  // Decrementa o topo para "remover" o elemento

    return true;
}

void reinicializarPilha(PILHA* p)
{
    p->topo = -1;  // Reseta o topo para -1, indicando que a pilha está vazia
}                                               
