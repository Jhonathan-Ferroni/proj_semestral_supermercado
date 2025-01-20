#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"


void criadat();
int comparalogin(char nome[50], char pront[10]);
void bubblesort(reg* registros, int n);
int carregavetor(const char* Arq, reg** registros);
void salvadat(const char* Arq, reg* registros, int n);
void menuprincipal(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario); // Alterado para corresponder à definição no pilhas.h
void exibirRegistros(reg* registros, int n);
int adicionarusuario();
int excluirusuarios();


#endif