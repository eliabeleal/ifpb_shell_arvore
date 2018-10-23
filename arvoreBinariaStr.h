#ifndef _BIN_TREE_
#define _BIN_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _no noArv;
typedef noArv* arvore;


/*  Operacoes basicas */
///INICIALIZA A ARVORE
void inicializaArv(arvore *arv);
void cPilha (void);

///CHECA SE A ARVORE EST� VAZIA
int vaziaArv(arvore arv);

///RECEBE A ARVORE E A STRING
int criaRaiz(arvore *arv, char* info);

///RECEBE A ARVORE E A STRING; RETORNA A RA�Z SE SUCESSO; NULL, SIGNIFICA QUE N�O FOI POSS�VEL ALOCAR
noArv* insereArvOrd(arvore arv, char* info);
noArv* goArv (arvore *cursor, char* param);

///RECEBE A ARVORE E A STRING PARA BUSCA; RETORNA O N� DA BUSCA OU NULL;
void zeraPilha (void);
noArv* buscaArvOrd( arvore arv, char* info );

///RECEBE UM N�;
void printNo(arvore arv);
void inOrdem(arvore arv);
void inOrdemDecrescente(arvore arv);
void preOrdem(arvore arv);
void posOrdem(arvore arv);
void whereami (arvore arv);
void printEndPilha(void);
void ifVaziaPilha(arvore cursor);
int checkEsq(arvore no);
int checkDir(arvore no);
noArv* filhoEsq(arvore no);
noArv* filhoDir(arvore no);
int parent (arvore *cursor);
noArv* minimo(arvore arv);
noArv* maximo(arvore arv);

///REMOVE O N� INFORMADO PELA STRING
void removeNoArv(arvore *raiz, char* info);

///TAMANHO DA �RVORE
int heightTree (arvore *arv);

///DELETA A ARVORE
void freeTree(arvore arv);

///COLOCA NULL NOS FILHOS
void filhosNull (arvore *arv);

///CONTA OS N�S FOLHA
int leafs(arvore arv);

///TOTAL DE N�S
int totalNoTree(arvore *raiz);

///SALVAR COM CSV
void CSV (arvore arv, FILE* arqv);

///SALVA COMO JSON
int JSON(arvore a, FILE* arqv);

#endif
