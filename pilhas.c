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
void adicionarproduto();
void salvarPilhaEmArquivo(PILHA* p, const char* nomeArquivo);
bool carregarPilhaDeArquivo(PILHA* p, const char* nomeArquivo);

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

void inicializarGondolas(PILHA gondolas[]) {
    char nomeArquivo[20];
    for (int i = 0; i < NUM_GONDOLAS; i++) {
        sprintf(nomeArquivo, "gondola%d.dat", i + 1);
        if (!carregarPilhaDeArquivo(&gondolas[i], nomeArquivo)) {
            inicializarPilha(&gondolas[i]);
        }
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
                adicionarproduto();
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

void adicionarproduto(PILHA gondolas[]) {
	printf("Escolha a gôndola para abastecer: ");
	int gondola;
	scanf("%d", &gondola);
	if (gondola < 1 || gondola > NUM_GONDOLAS) {
		printf("Gôndola inválida.\n");
		return;
	}
	gondola--; // Ajusta o índice para o vetor
	if (estaCheia(&gondolas[gondola])) {
		printf("A gôndola está cheia.\n");
		return;
	}
	REGISTRO produto;
    fflush(stdin);
	printf("Nome do produto: ");
	scanf("%s", produto.NOMEPROD);
    fflush(stdin);
	printf("Descrição do produto: ");
	scanf("%s", produto.desc);
    fflush(stdin);
	printf("Peso do produto: ");
	scanf("%d", &produto.peso);
    fflush(stdin);
	printf("Preço do produto: ");
	scanf("%d", &produto.preco);
	inserirElemPilha(&gondolas[gondola], produto);
	printf("Produto adicionado à gôndola %d.\n", gondola + 1);
	char nomeArquivo[20];
	sprintf(nomeArquivo, "gondola%d.dat", gondola + 1);
    salvarPilhaEmArquivo(&gondolas[gondola], nomeArquivo);
	getchar();
}

void exibirGondolas(PILHA gondolas[], int numGondolas) {
    system("cls");
    printf("\nProdutos nas gondolas:\n");
    for (int i = 0; i < numGondolas; i++) {
        printf("\nGondola %d:\n", i + 1);
        for (int j = 0; j <= gondolas[i].topo; j++) {
            REGISTRO produto = gondolas[i].elementos[j];
            printf("Produto: %s | Preço: %d | Peso: %d | Descricao: %s\n",
                produto.NOMEPROD, produto.preco, produto.peso, produto.desc);
        }
    }
}

void exibirCarrinho(CARRINHO* carrinho) {
    printf("\nItens no carrinho:\n");
    PONT atual = carrinho->topo;
    while (atual != NULL) {
        printf("Produto: %s | Preço: %d | Peso: %d | Descricao: %s\n",
            atual->reg.NOMEPROD, atual->reg.preco, atual->reg.peso, atual->reg.desc);
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
        printf("Nome: %s, Preço: %d, Peso: %d, Descricao: %s\n",
            p->elementos[i].NOMEPROD, p->elementos[i].preco,
            p->elementos[i].peso, p->elementos[i].desc);
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

void salvarPilhaEmArquivo(PILHA* p, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o número de elementos na pilha
    int tamanho = vertamanho(p);
    fwrite(&tamanho, sizeof(int), 1, arquivo);

    // Escreve os elementos da pilha no arquivo
    for (int i = 0; i <= p->topo; i++) {
        fwrite(&p->elementos[i], sizeof(REGISTRO), 1, arquivo);
    }

    fclose(arquivo);
}

bool carregarPilhaDeArquivo(PILHA* p, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        // Arquivo não existe ou não pode ser aberto
        return false;
    }
    // Lê o número de elementos na pilha
    int tamanho;
    if (fread(&tamanho, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return false;
    }

    // Lê os elementos da pilha do arquivo
    for (int i = 0; i < tamanho; i++) {
        if (fread(&p->elementos[i], sizeof(REGISTRO), 1, arquivo) != 1) {
            fclose(arquivo);
            return false;
        }
    }
    p->topo = tamanho - 1;

    fclose(arquivo);
    return true;
}
