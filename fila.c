#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "pilhas.h"

typedef struct nodoFila {
    REGISTRO regf; // Alterado de reg para regf
    struct nodoFila* prox;
} NODOFILA;

typedef struct {
    NODOFILA* inicio;
    NODOFILA* fim;
} FILA;

void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

bool estaVaziaFila(FILA* f) {
    return (f->inicio == NULL);
}

bool inserirNaFila(FILA* f, REGISTRO reg) {
    NODOFILA* novo = (NODOFILA*)malloc(sizeof(NODOFILA));
    if (novo == NULL) return false;
    novo->regf = reg; // Alterado de novo->reg para novo->regf
    novo->prox = NULL;
    if (f->fim == NULL) {
        f->inicio = novo;
    }
    else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    return true;
}

bool removerDaFila(FILA* f, REGISTRO* reg) {
    if (estaVaziaFila(f)) return false;
    NODOFILA* temp = f->inicio;
    *reg = temp->regf; // Alterado de *reg = temp->reg para *reg = temp->regf
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
    return true;
}

void caixaEletronico(CARRINHO* carrinho, PILHA gondolas[]) {
    FILA fila;
    inicializarFila(&fila);
	float preco_total = 0;
    REGISTRO reg;
    FILE* notaFiscal = fopen("nota_fiscal.txt", "w");
    if (notaFiscal == NULL) {
        printf("Erro ao criar a nota fiscal.\n");
        return;
    }

    fprintf(notaFiscal, "Nota Fiscal\n");
    fprintf(notaFiscal, "----------------------------\n");

    // Passar produtos do carrinho para a fila
    while (carrinho->topo != NULL) {
        PONT temp = carrinho->topo;
        carrinho->topo = carrinho->topo->PROX;
        inserirNaFila(&fila, temp->reg);
        free(temp);
    }

    // Processar produtos na fila e gerar nota fiscal
    while (!estaVaziaFila(&fila)) {
        removerDaFila(&fila, &reg);
        fprintf(notaFiscal, "Produto: %s | Preco: %.2f | Peso: %.2f | Descricao: %s\n",
            reg.NOMEPROD, reg.preco, reg.peso, reg.desc);
        preco_total += reg.preco;
    }

    fprintf(notaFiscal, "----------------------------\n");
	fprintf(notaFiscal, "Total: R$ %.2f\n", preco_total);
    fclose(notaFiscal);

    // Salvar o estoque atualizado
    for (int i = 0; i < NUM_GONDOLAS; i++) {
        char nomeArquivo[20];
        sprintf(nomeArquivo, "gondola%d.dat", i + 1);
        salvarPilhaEmArquivo(&gondolas[i], nomeArquivo);
    }

    printf("Compra finalizada. Nota fiscal gerada e estoque atualizado.\n");
}
