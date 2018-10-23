#include "arvoreBinariaStr.h"
#include "pilhaEnc.h"

struct _no {
	char* info;
	struct _no *esq;
	struct _no *dir;
};

struct{
    tpilha pbusc, parent;
    int nivel;
}global;


/* 	Implementacao das operacoes com arvore */

///INICIALIZA��O E CHECAGEM
void inicializaArv(arvore *arv) {
	*arv = NULL;
}
void cPilha (void){
    criarPilha(&global.pbusc);
}

int vaziaArv(arvore arv) {
	return (arv == NULL);
}

///INSER��O
int criaRaiz(arvore *arv, char* info){
    noArv* novo;
    if( !vaziaArv(*arv) )
        return 0;

    if ( (novo = (noArv*)malloc(sizeof(noArv))) == NULL )
        return 0;
    if ( (novo->info = (char*) malloc(sizeof(strlen(info))+1)) == NULL )
        return 0;
    strcpy(novo->info,info);
    novo->esq = novo->dir = NULL;
    *arv = novo;
    return 1;
}

noArv* insereArvOrd(arvore arv, char* info) {
	if ( vaziaArv(arv) ) {
        if ( (arv = (noArv*) malloc(sizeof(noArv))) == NULL )
            return NULL;
        if ( (arv->info = (char*) malloc(sizeof(strlen(info))+1)) == NULL )
            return NULL;
		strcpy( arv->info, info );
		arv->esq = arv->dir = NULL;
	} else if ( strcmp(info, (arv->info)) < 0 ){
		arv->esq = insereArvOrd( arv->esq, info );
	}else {
		arv->dir = insereArvOrd( arv->dir, info );
	}
	return arv;
}



///CONSULTA
void zeraPilha (void){
    do{
        pop(&global.pbusc);
    }while (!vaziaPilha(global.pbusc));
}

noArv* buscaArvOrd( arvore arv, char* info ){
    if ( arv == NULL )
		return NULL;
	else if ( strcmp(info, (arv->info)) < 0 ){
                push(&global.pbusc, arv->esq);
		return buscaArvOrd( arv->esq, info );
	}else if ( strcmp(info, (arv->info)) > 0 ){
                push(&global.pbusc, arv->dir);
        return buscaArvOrd( arv->dir, info );
	}else
	   // Se cair aqui, o n� foi encontrado
		return arv;
}

noArv* goArv (arvore *cursor, char* param){
    zeraPilha();
    push(&global.pbusc, *cursor);
    *cursor = buscaArvOrd(*cursor, param);
    return *cursor;
}

void ifVaziaPilha(arvore cursor){
    if (vaziaPilha(global.pbusc))
        push(&global.pbusc, cursor);
}

int checkEsq(arvore sonRg){
    return vaziaArv(sonRg->esq);
}
int checkDir(arvore sonRg){
    return vaziaArv(sonRg->dir);
}

noArv* filhoEsq(arvore no){
    if (!vaziaArv(no)){
        push(&global.pbusc, no->esq);
        return no->esq;
    }else
        return NULL;
}



noArv* filhoDir(arvore no){
    if (!vaziaArv(no)){
        push(&global.pbusc, no->dir);
        return no->dir;
    }else
        return NULL;
}

///recebe o cursor e retorna o endere�o do n� ancestral
int parent (arvore *cursor){
    pop(&global.pbusc);
    return elemtopo(global.pbusc, &(*cursor));
}

noArv* minimo(arvore arv){// procura o n� com valor m�nimo
    if(vaziaArv(arv)){
       return NULL;
    }else{
          if( vaziaArv(arv->esq) )
              return arv;
          else
              return minimo(arv->esq);
    }
}

noArv* maximo(arvore arv){// procura o n� com valor maximo
    if(vaziaArv(arv)){
       return NULL;
    }else{
          if( vaziaArv(arv->dir) )
              return arv;
          else
              return maximo(arv->dir);

    }
}

///IMPRESS�O
void printNo(arvore arv){
    if (!vaziaArv(arv)){
        printf("%s ", arv->info);
    }

}

void inOrdem(arvore arv) {
	if (!vaziaArv(arv)) {
		inOrdem(arv->esq);
		printf("%s ", arv->info);
		inOrdem(arv->dir);
	}
}

void inOrdemDecrescente(arvore arv) {
	if (!vaziaArv(arv)) {
		inOrdem(arv->dir);
		printf("%s ", arv->info);
		inOrdem(arv->esq);
	}
}

void preOrdem(arvore arv){
    if(!vaziaArv(arv)){
        printf("%s ", arv->info);
        preOrdem(arv->esq);
        preOrdem(arv->dir);
    }
}

void posOrdem(arvore arv){
    if(!vaziaArv(arv)){
        posOrdem(arv->esq);
        posOrdem(arv->dir);
        printf("%s ", arv->info);
    }
}

void whereami (arvore arv){
    if (!vaziaArv(arv))
    printf("%s", arv->info);
}

void printEndPilha(void){
    printPilha(global.pbusc);
}

///REMO��O
/*
Para a remo��o de um n� de uma �rvore deve-se levar em considera��o que seus filhos devem
continuar na �rvore e esta dever� continuar ordenada (menor � esquerda, maior � direita).
E ent�o ca�mos em tr�s possibilidades que devem ser tratadas separadamente, a fim de manter
a estrutura da �rvore bin�ria. Sendo elas:
a) Quando o n� a ser exclu�do n�o contenha filhos:
   O n� simplesmente � removido.
b) Quando o n� a ser exclu�do contenha somente um dos filhos:
   O pai do n� a ser exclu�do passa a apontar para este filho e o n� � removido.
c) Quando o n� a ser exclu�do contenha os dois filhos:
   Busca-se o maior elemento da sub-�rvore da esquerda (a partir da raiz da sub-�rvore
   esquerda caminha-se sempre para a direita at� achar um n� cujo filho � direita � nulo).
   Transfere-se a informa��o deste n� para o n� a ser removido e remove-se este novo n�, que cair� no caso (a) ou (b)
*/
void removeNoArv(arvore *raiz, char* info){
    arvore aux;
    if(!vaziaArv(*raiz)){
       // se o valor que ser� removido for menor que o n� atual,
       if( strcmp( info, (*raiz)->info ) < 0 ){
           removeNoArv( &((*raiz)->esq), info ); // faz recursividade � esquerda
       }else if( strcmp( info, (*raiz)->info ) > 0 ){ // se o valor que ser� removido for maior que o n� atual,
            removeNoArv( &((*raiz)->dir), info); // faz recursividade � direita.
       }else{ // encontrou o n�.
            // quando o n� a ser removido for encontrado e ele possuir filho esq e dir
            if( !vaziaArv((*raiz)->esq) && !vaziaArv((*raiz)->dir) ){
                // caso (c)
                // verificamos se os n�s filhos da esquerda e direita n�o s�o null.
                // se n�o forem null, buscamos o menor n� a partir do n� da direita.
                aux = minimo((*raiz)->dir);
                // aux = maximo((*raiz)->esq);  // ou entao usa este
                strcpy( (*raiz)->info, (aux->info) );
                removeNoArv( &(*raiz)->dir, (*raiz)->info);
            } else {
                // caso os n� da direita e da esqueda, ou somente o da direita for null,
                // precisamos apenas remover o n� atual e fazer ajustar os ponteiros
                aux = *raiz;

                if(vaziaArv((*raiz)->esq)){
                   // se o n� da esquerda for vazio
                   // o n� pai do atual, apontar� para o filho da direita do n� atual.
                   *raiz = (*raiz)->dir;
                }  else {
                   // se o n� da esquerda n�o for vazio.
                   // o n� pai do atual, apontar� para o filho da esquerda do n� atual.
                   *raiz = (*raiz)->esq;
                }
                free(aux);
            }
       }
    } // if-raiz-vazia
}

///TAMANHO DA �RVORE
int heightTree (arvore *arv){
    if (*arv == NULL) return 0;
    int alt_esq = heightTree(&((*arv)->esq));
    int alt_dir = heightTree(&((*arv)->dir));
    if (alt_esq > alt_dir) return (alt_esq + 1);
    else return (alt_dir + 1);
}

///TOTAL DE N�S
int totalNoTree (arvore *raiz){
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNoTree(&((*raiz)->esq));
    int alt_dir = totalNoTree(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

///LIBERA N�
void freeNo(noArv* no){
    if (no == NULL) return;
    freeNo(no->esq);
    freeNo(no->dir);
    free(no);
    no = NULL;
}

///LIBERA �RVORE
void freeTree(arvore arv){
    if (arv ==  NULL) return;
    freeNo(arv);
    free(arv);
}

///FILHOS NULL
void filhosNull (arvore *arv){
    if (!vaziaArv(*arv))
        (*arv)->dir = (*arv)->esq = NULL;
}

///N�S FOLHAS
int leafs(arvore arv){
    if(arv == NULL)
        return 0;
    if(arv->esq == NULL && arv->dir == NULL)
        return 1;
    else
        return leafs(arv->esq)+leafs(arv->dir);
}

///SALVANDO
void CSV (arvore arv, FILE* arqv){
    if(!vaziaArv(arv)){
        fprintf(arqv, "%s;", arv->info);
        CSV(arv->esq, arqv);
        CSV(arv->dir, arqv);
    }
}



void getEspaco(FILE* arqv)
{
    int i;
    for(i=0; i<(global.nivel*2)-1; i++)
        fprintf(arqv, "  ");

}

void getEspacoDouble(FILE* arqv)
{
    int i;
    for(i=0; i<global.nivel*2; i++)
    fprintf(arqv, "  ");

}

void createJSON (arvore a, FILE* arqv)
{
    arvore temp;
    if(!vaziaArv(a)) {
    //se tem filho direito
    getEspacoDouble(arqv);
    fprintf(arqv, "\"name\": \"%s\",\n", a->info);
    getEspacoDouble(arqv);
    fprintf(arqv, "\"parent\": ");
    if(elemtopo(global.parent, &temp))
        fprintf(arqv, " \"%s\",\n", temp->info);
    else
        fprintf(arqv, " \"null\",\n");

    if(a->esq != NULL || a->dir != NULL)
        {
            push(&global.parent, a);
            getEspacoDouble(arqv);
            fprintf(arqv, "\"children\": [\n");
            global.nivel++;
            if(a->esq != NULL){
                getEspaco(arqv);
                fprintf(arqv, "{\n");
                createJSON(a->esq, arqv);
                getEspaco(arqv);
                fprintf(arqv, "}%c\n", (a->dir != NULL) ? ',' : ' ');
            }

            if(a->dir != NULL){
                getEspaco(arqv);
                fprintf(arqv, "{\n");
                createJSON(a->dir, arqv);
                getEspaco(arqv);
                fprintf(arqv, "}\n");
            }

            pop(&global.parent);
            global.nivel--;
            getEspacoDouble(arqv);
            fprintf(arqv, "]\n");
        }

    }
}

int JSON(arvore a, FILE* arqv){
    fprintf(arqv,"var treeData = [\n  {\n");
    criarPilha(&global.parent);
    global.nivel = 1;
    createJSON(a, arqv);
    fprintf(arqv, "  }\n];");
    fclose(arqv);
    return 1;
}








