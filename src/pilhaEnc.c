#include "pilhaEnc.h"
//OPERAÇÕES

struct no{
    arvore dado;         ///CAMPO DA INFORMAÇÃO
    struct no* prox;    ///PONTEIRO PARA O PRÓXIMO NÓ
};

    ///CRIAR
void criarPilha (tpilha *P){
    *P = NULL;
}

    ///VERIFICAR
int vaziaPilha (tpilha P){
    return (P == NULL);
}

    ///ELEMENTO DO TOPO
int elemtopo (tpilha P, arvore *dado){
    if (vaziaPilha(P)) return 0;
    *dado = P->dado;
    return 1;
}

    ///EMPILHA
int push (tpilha *P, arvore dado){
    tpilha novo;

    novo = (tno*) malloc(sizeof(tno));

    if (novo == NULL) return 0;

    novo->dado = dado;
    novo->prox = *P;
    *P = novo;
    return 1;
}

    ///REMOVE O TOPO
int pop (tpilha *P){
    tpilha aux;
    if (vaziaPilha(*P)) return 0;

    aux = *P;
    *P = aux->prox;
    free(aux);
    return 1;
}

    ///IMPRIMIR
void printPilha (tpilha P){
    while (P != NULL){
        printf("%p ", P->dado);
        P = P->prox;
    }

}

