#ifndef _PIL_ENC_
#define _PIL_ENC_

#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinariaStr.h"

typedef struct no tno;
typedef tno* tpilha;

//OPERAÇÕES
///CRIAR
void criarPilha (tpilha *P);

///VERIFICAR
int vaziaPilha (tpilha P);

///ELEMENTO DO TOPO
int elemtopo (tpilha P, arvore* dado);

///EMPILHA
int push (tpilha *P, arvore dado);

///REMOVE O TOPO
int pop (tpilha *P);

///IMPRIMIR
void printPilha (tpilha P);

#endif
