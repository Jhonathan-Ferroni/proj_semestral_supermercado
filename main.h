// utils.h
#ifndef MAIN_H
#define MAIN_H


void criadat();
int comparalogin(char nome[50], char pront[10]);
void bubblesort(reg *registros, int n);
int carregavetor(const char *Arq, reg**registros);
void salvadat(const char *Arq, reg *registros, int n);
void menu();

#endif
