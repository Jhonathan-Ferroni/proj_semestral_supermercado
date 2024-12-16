#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXTAM 5
#define NUM_GONDOLAS 10

/*struct das gondolas*/

typedef struct
{
	char NOMEPROD[100+1];
	char DATAVENC[10+1];
	char DATAVAL[10+1];
	int preco;
}REGISTRO;

typedef struct
{
	REGISTRO elementos[MAXTAM];
	int topo;
}PILHA;

/*struct do carrinho*/

typedef struct aux
{
	REGISTRO reg;
	struct aux * PROX;
}ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
	PONT topo;
}CARRINHO;


/*----------------------------*/

void inicializarGondolas()
{
    for(i = 0; i< NUM_GONDOLAS; i++)
    {
        inicializarPilha(&gondolas[i]);
    }
}

void inicializarPilha(PILHA *p)
{
    p->topo = -1;
}

/*----------------------------*/

int vertamanho (PILHA * p)
{
	PONT end = p->topo;
	int tam = 0;
	while (end != NULL)
	{
		tam++;
		end = end->PROX;
	}
	return tam;
}

void exibirPilha(PILHA * p)
{
	PONT end = p->topo;
	system("cls");
	printf("Pilha :  \" ");
	while(end != NULL)
	{
		printf("%s - %i - %s - %s", end->NOMEPROD, end->preco, end->DATAVENC, end->DATAVAL);
		end = end->PROX;
	}
	printf("\"\n");
}

bool estaVazia(PILHA* p) 
{
   if (p->topo == NULL) 
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
