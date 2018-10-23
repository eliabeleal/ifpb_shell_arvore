#include "shell.h"
#include "defines.h"

///ELEMENTOS DO SHELL
struct {
    arvore root, cursor;
    FILE* sv;
    FILE* ld;
}shell;
void initStruct (void){
    inicializaArv(&(shell.cursor));
    inicializaArv(&(shell.root));
    cPilha();
}

///PARSE
int comando (const char cmd[]){

    if (!strcmpi(cmd,"croot"))
        return CROOT;
    else if (!strcmpi(cmd,"addnode"))
        return ADDNODE;
    else if (!strcmpi(cmd,"remove"))
        return REMOVE;
    else if (!strcmpi(cmd,"dleft"))
        return DLEFT;
    else if (!strcmpi(cmd,"dright"))
        return DRIGHT;
    else if (!strcmpi(cmd,"go"))
        return GO;
    else if (!strcmpi(cmd,"back"))
        return BACK;
    else if (!strcmpi(cmd,"goroot"))
        return GOROOT;
    else if (!strcmpi(cmd,"tree"))
        return TREE;
    else if (!strcmpi(cmd,"deltree"))
        return DELTREE;
    else if (!strcmpi(cmd,"height"))
        return HEIGHT;
    else if (strcmpi(cmd,"size") == 0)
        return SIZE;
    else if (!strcmpi(cmd,"leafs"))
        return LEAFS;
    else if (!strcmpi(cmd,"loadtree"))
        return LOADTREE;
    else if (!strcmpi(cmd,"savetree"))
        return SAVETREE ;
    else if (!strcmpi(cmd,"whereami"))
        return WHEREAMI;
    else if (!strcmpi(cmd, "quit"))
        return QUIT;
    else if (!strcmpi(cmd,"help"))
        return HELP;
    else
        return -1;
}

///TRATAMENTO DE ERRO
void erroSintaxe (char* cmd){
    textcolor(12);
    printf("Erro de sintaxe na execução do comando %s\n",cmd);
}
void sintaxe (char* cmd){
    textcolor(10);
    if (!strcmp(cmd, "loadtree") || !strcmp(cmd, "deltree") )
        printf("Sintaxe:\n%s <nome da árvore>\n", cmd);
    else if (!strcmp(cmd, "tree"))
        printf("Sintaxe:\n%s <argumento>\n\nArgumentos\n/pre : caminhamento em pré-ordem\n/pos : caminhamento em pos-ordem\n/in  : caminhamento em in-ordem\n", cmd);
    else if(!strcmp(cmd, "savetree"))
        printf("Sintaxe:\n%s <tipo: [CSV] ou [JSON]> <nome da árvore>\n", cmd);
    else if (!strcmp(cmd, "height"))
        printf("Sintaxe:\n%s\n", cmd);
    else
        printf("Sintaxe:\n%s <valor>\n", cmd);
}

///OPERAÇÕES DE ARVORE
int createRoot (char* param){
    if (criaRaiz(&(shell.root), param)){
        shell.cursor = shell.root;
        return 1;
    }else
        return 0;
}

int insertNo (char* param){
    if (vaziaArv(shell.root))
        return 0;
    else{
        insereArvOrd((shell.root), param);
        return 1;
    }
}

int rmv (char* param){
    if (buscaArvOrd(shell.root, param) != NULL){
        removeNoArv(&(shell.root), param);
        return 1;
    }
    else
        return 0;
}

int dleft (void){
    ifVaziaPilha(shell.cursor);
    if (!vaziaArv(shell.root) && !checkEsq(shell.cursor)){
        shell.cursor = filhoEsq(shell.cursor);
        return 1;
    }else
        return 0;
}

int dright (void){
    ifVaziaPilha(shell.cursor);
    if (!vaziaArv(shell.root) && !checkDir(shell.cursor)){
        shell.cursor = filhoDir(shell.cursor);
        return 1;
    }else
        return 0;

}

int go (char* param){
    shell.cursor = goArv(&shell.cursor, param);
    if (shell.cursor != NULL)
        return 1;
    else
        return 0;
}

int goRoot(void){
    shell.cursor = shell.root;
    zeraPilha();
   if (shell.cursor != NULL)
        return 1;
    else
        return 0;
}


int back (void){
        return parent(&shell.cursor);
}

void printTree (char* param){
    if (!vaziaArv(shell.root)){
            textcolor(10);
        if (!strcmpi(param, "/pre")){
            printf("[ ");
            preOrdem(shell.root);
            printf(" ]\n");
        }else if (!strcmpi(param, "/pos")){
            printf("[ ");
            posOrdem(shell.root);
            printf(" ]\n");
        }else if (!strcmpi(param, "/in")){
            printf("[ ");            inOrdem(shell.root);
            printf(" ]\n");
        }
    }
}

///DELTREE
int deltree(char* param){
    if (!vaziaArv(shell.root)){
        if (!strcmpi(param, "A")){
            freeTree(shell.root);
            parent(&shell.root);
            inicializaArv(&shell.root);
            return 1;
        }else if (!strcmpi(param, "S") && shell.cursor != shell.root){
            freeTree(shell.cursor);
            parent(&shell.cursor);
            filhosNull(&shell.cursor);
            return 1;
        }else if (!strcmpi(param, "S") && shell.cursor == shell.root){
            freeTree(shell.root);
            parent(&shell.root);
            inicializaArv(&shell.root);
            return 1;
        }
        else
            return -1;
    }else
        return 0;
}

int height(void){
    return heightTree(&shell.root);
}

int size(void){
    if (!vaziaArv(shell.root))
        return totalNoTree(&shell.root);
    else
        return 0;
}

int leaf (void){
    return leafs(shell.root);
}


///SAVE
int save (char* param, char* nome){
    if (!vaziaArv(shell.root)){
        if (!strcmpi(param, "CSV") && nome != NULL){
            strcat(nome,".txt");
            shell.sv = fopen(nome, "w");
            if (shell.sv == NULL)
                return 0;
            CSV(shell.root, shell.sv);
            fclose(shell.sv);
            return 1;
        }else if (!strcmpi(param, "JSON") && nome != NULL){
            strcat(nome,".json");
            shell.sv = fopen(nome, "w");
            if (shell.sv == NULL)
                return 0;
            JSON(shell.root, shell.sv);
            return 1;
        }else
            return 0;
    }else
        return 0;
}

///LOADTREE
int loadTree (char* nome){
    if (vaziaArv(shell.root)){
        char no[100];
        char* retok;
        strcat(nome,".txt");
        shell.ld = fopen(nome, "r");
        if (shell.ld == NULL)
            return 0;
        while( (fgets(no, sizeof(no), shell.ld))!=NULL )
        criaRaiz(&(shell.root), strtok(no, ";"));
        do{
            retok = strtok('\0', ";");
            if (retok)
                insereArvOrd(shell.root, retok);
        }while (retok);
        shell.cursor = shell.root;
        fclose(shell.ld);
        return 1;
    }else
        return -1;

}


int wm (void){
    if (!vaziaArv(shell.root)){
        textcolor(10);
        printf("[ ");
        whereami (shell.cursor);
        printf(" ]\n");
        return 1;
    }else
        return 0;
}



void helps(){
    puts("croot\t\tCria raiz da árvore");
    puts("addnode\t\tAdiciona um nó à árvore");
    puts("remove\t\tRemove um determinado nó da árvore");
    puts("dleft\t\tCaminha para o filho esquerdo");
    puts("dright\t\tCaminha para o filho direito");
    puts("go\t\tCaminha para um nó específico");
    puts("back\t\tVolta para o nó ancestral");
    puts("goroot\t\tVolta para a raiz da árvore");
    puts("tree\t\tExibe a sequência de elementos da árvore\n\t\tem pré-ordem, pos-ordem ou in-ordem");
    puts("deltree\t\tRemove todos os nós da árvore ou uma subárvore de um nó");
    puts("height\t\tExibe a altura relativa da árvore");
    puts("size\t\tExibe a quantidade de nós da árvore");
    puts("leafs\t\tExibe a quantidade de nós folhas");
    puts("loadtree\tCarrega uma árvore do disco para a memória");
    puts("savetree\tSalva uma árvore da memória para o disco");
    puts("quit\t\tSair do interpretador de comandos");
    puts("whereami\tExibe o local (conteúdo) onde se encontra o nó relativo");
}



///FUNÇÕES DO LOAD



















