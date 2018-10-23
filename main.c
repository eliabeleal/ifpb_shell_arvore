#include "shell.h"
#include <locale.h>
#include "defines.h"



///INTERE��O COM O USU�RIO
int main()
{
    setlocale(LC_ALL, "Portuguese");
    initStruct();
    for (;;){
        char in[100];
        textcolor(7);
        putchar('>');
        gets(in);


        char* cmd = strtok(in, " ");
        char* parametro = strtok('\0', " ");
        char* nome = strtok('\0', " ");
        if (strtok('\0', " ") != NULL)
            parametro = NULL;
        switch (comando(cmd)){

            case CROOT:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Cria raiz da �rvore");
                    sintaxe(cmd);
                }else{
                    if (createRoot(parametro)){
                        textcolor(9);
                        printf("[msg] raiz com valor \"%s\" criado com sucesso\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] a arvore j� possuiu uma raiz. Opera��o invalida!");
                        }
                    }
                break;
            case ADDNODE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Adiciona um n� � �rvore");
                    sintaxe(cmd);
                }else{
                    if (insertNo(parametro)){
                        textcolor(9);
                        printf("[msg] n� \"%s\" criado com sucesso\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] n�o � poss�vel criar n� se n�o houver ra�z");
                    }
                }
                break;
            case REMOVE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Remove um determinado n� da �rvore");
                    sintaxe(cmd);
                }else if (rmv(parametro)){
                    textcolor(9);
                    printf("[msg] n� \"%s\" removido com sucesso\n", parametro);
                }else{
                    textcolor(12);
                    puts("[msg] n� n�o existe");
                    textcolor(12);
                    puts("[IMPORTANTE!]\nInforme corretamente o valor do n�");
                }

                break;
            case DLEFT:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Caminha para o filho esquerdo");
                }else{
                    if (!dleft()){
                        textcolor(12);
                        puts("[msg] n� n�o tem filho esquerdo");
                    }
                }
                wm();
                break;
            case DRIGHT:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Caminha para o filho direito");
                }else{
                    if (!dright()){
                        textcolor(12);
                        puts("[msg] n� n�o tem filho direito");
                    }
                }
                wm();
                break;
            case GO:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Posiciona-se em um determinado n� da �rvore");
                    sintaxe(cmd);
                    textcolor(12);
                    puts("[IMPORTANTE!]\nInforme corretamente o valor do n�");
                }else{
                    if (go(parametro)){
                        textcolor(9);
                        printf("[msg] voc� est� posicionado no n� \"%s\"\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] n� n�o existe");
                        textcolor(12);
                        puts("[IMPORTANTE!]\nInforme corretamente o valor do n�");
                    }
                }
                break;
            case BACK:
                 if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Volta para o n� ancestral");
                }else{
                    if (!back()){
                        textcolor(12);
                        puts("[msg] n� ra�z ou ra�z vazia");
                    }
                }
                wm();
                break;
            case GOROOT:
                 if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Volta para a raiz da �rvore");
                }else{
                    if (goRoot()){
                        wm();
                        textcolor(12);
                        puts("[msg] ra�z");
                    }else{
                        textcolor(12);
                        puts("[msg] ra�z vazia");
                    }
                }
                break;
            case TREE:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a sequ�ncia de elementos da �rvore em pr�-ordem, pos-ordem ou in-ordem");
                    sintaxe(cmd);
                }else if (!strcmpi(parametro, "/pre") || !strcmpi(parametro, "/pos")|| !strcmpi(parametro, "/in")){
                    textcolor(10);
                    printTree(parametro);
                }else{
                    erroSintaxe(cmd);
                    textcolor(10);
                    puts("Exibe a sequ�ncia de elementos da �rvore em pr�-ordem, pos-ordem ou in-ordem");
                    sintaxe(cmd);
                }
                break;
            case DELTREE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                    puts("Remove todos os n�s da �rvore ou uma sub-�rvore de um n�\nParamentro\nSub-�rvore[S] ou �rvore[A]");
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Remove todos os n�s da �rvore ou uma sub-�rvore de um n�\nParamentro\nSub-�rvore[S] ou �rvore[A]");
                    sintaxe(cmd);
                }else{
                    int ret = deltree(parametro);
                    if (ret){
                        textcolor(9);
                        printf("[msg] �rvore \"%s\" deletada com sucesso\n", parametro);
                    }
                    else if (ret < 0){
                        erroSintaxe(cmd);
                        sintaxe(cmd);
                    }else{
                        textcolor(12);
                        puts("[msg] �rvore vazia");
                    }
                }
                break;
            case HEIGHT:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a altura relativa da �rvore");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] altura da �rvore \"%d\"\n", height());
                }
                break;
            case SIZE:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a quantidade de n�s da �rvore");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] quantidade de n�s da �rvore � \"%d\"\n", size());
                }
                break;
            case LEAFS:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a quantidade de n�s folhas");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] quantidade de n�s folhas da �rvore � \"%d\"\n", leaf());
                }
                break;
            case LOADTREE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Carrega uma �rvore do disco para a mem�ria");
                    sintaxe(cmd);
                }else{
                    int ret = loadTree(parametro);
                    if (ret > 0){
                        textcolor(9);
                        printf("[msg] �rvore \"%s\" carregada com sucesso\n", parametro);
                    }else if (ret < 0){
                        textcolor(12);
                        puts("[msg] use savetree e deltree na �rvore atual antes de do loadtree");
                    }else{
                        textcolor(12);
                        puts("[msg] n�o � poss�vel carregar �rvore");
                    }
                }
                break;
            case SAVETREE:
                 if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Salva uma �rvore da mem�ria para o disco");
                    sintaxe(cmd);
                }else{
                    if (nome == NULL){
                        erroSintaxe(cmd);
                        sintaxe(cmd);
                    }else if (save(parametro, nome)){
                        textcolor(9);
                        printf("[msg] �rvore \"%s\" salva com sucesso\n", nome);
                    }else{
                        textcolor(12);
                        puts("[msg] n�o � poss�vel salvar �rvore");
                    }
                }

                break;
            case WHEREAMI:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe o local (conte�do) onde se encontra o n� relativo");
                }else if (!wm()){
                    textcolor(12);
                    puts("[msg] �rvore vazia");
                }



                break;
            case QUIT:
                goto sair;
                break;
            case HELP:
                helps();
                break;

            default:
                textcolor(12);
                puts("comando desconhecido");
                break;
        }
    }///end infinite for
    sair:
        return 0;
}


