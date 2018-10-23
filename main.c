#include "shell.h"
#include <locale.h>
#include "defines.h"



///INTEREÇÃO COM O USUÁRIO
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
                    puts("Cria raiz da árvore");
                    sintaxe(cmd);
                }else{
                    if (createRoot(parametro)){
                        textcolor(9);
                        printf("[msg] raiz com valor \"%s\" criado com sucesso\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] a arvore já possuiu uma raiz. Operação invalida!");
                        }
                    }
                break;
            case ADDNODE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Adiciona um nó à árvore");
                    sintaxe(cmd);
                }else{
                    if (insertNo(parametro)){
                        textcolor(9);
                        printf("[msg] nó \"%s\" criado com sucesso\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] não é possível criar nó se não houver raíz");
                    }
                }
                break;
            case REMOVE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Remove um determinado nó da árvore");
                    sintaxe(cmd);
                }else if (rmv(parametro)){
                    textcolor(9);
                    printf("[msg] nó \"%s\" removido com sucesso\n", parametro);
                }else{
                    textcolor(12);
                    puts("[msg] nó não existe");
                    textcolor(12);
                    puts("[IMPORTANTE!]\nInforme corretamente o valor do nó");
                }

                break;
            case DLEFT:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Caminha para o filho esquerdo");
                }else{
                    if (!dleft()){
                        textcolor(12);
                        puts("[msg] nó não tem filho esquerdo");
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
                        puts("[msg] nó não tem filho direito");
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
                    puts("Posiciona-se em um determinado nó da árvore");
                    sintaxe(cmd);
                    textcolor(12);
                    puts("[IMPORTANTE!]\nInforme corretamente o valor do nó");
                }else{
                    if (go(parametro)){
                        textcolor(9);
                        printf("[msg] você está posicionado no nó \"%s\"\n", parametro);
                    }
                    else{
                        textcolor(12);
                        puts("[msg] nó não existe");
                        textcolor(12);
                        puts("[IMPORTANTE!]\nInforme corretamente o valor do nó");
                    }
                }
                break;
            case BACK:
                 if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Volta para o nó ancestral");
                }else{
                    if (!back()){
                        textcolor(12);
                        puts("[msg] nó raíz ou raíz vazia");
                    }
                }
                wm();
                break;
            case GOROOT:
                 if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Volta para a raiz da árvore");
                }else{
                    if (goRoot()){
                        wm();
                        textcolor(12);
                        puts("[msg] raíz");
                    }else{
                        textcolor(12);
                        puts("[msg] raíz vazia");
                    }
                }
                break;
            case TREE:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a sequência de elementos da árvore em pré-ordem, pos-ordem ou in-ordem");
                    sintaxe(cmd);
                }else if (!strcmpi(parametro, "/pre") || !strcmpi(parametro, "/pos")|| !strcmpi(parametro, "/in")){
                    textcolor(10);
                    printTree(parametro);
                }else{
                    erroSintaxe(cmd);
                    textcolor(10);
                    puts("Exibe a sequência de elementos da árvore em pré-ordem, pos-ordem ou in-ordem");
                    sintaxe(cmd);
                }
                break;
            case DELTREE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                    puts("Remove todos os nós da árvore ou uma sub-árvore de um nó\nParamentro\nSub-árvore[S] ou Árvore[A]");
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Remove todos os nós da árvore ou uma sub-árvore de um nó\nParamentro\nSub-árvore[S] ou Árvore[A]");
                    sintaxe(cmd);
                }else{
                    int ret = deltree(parametro);
                    if (ret){
                        textcolor(9);
                        printf("[msg] árvore \"%s\" deletada com sucesso\n", parametro);
                    }
                    else if (ret < 0){
                        erroSintaxe(cmd);
                        sintaxe(cmd);
                    }else{
                        textcolor(12);
                        puts("[msg] árvore vazia");
                    }
                }
                break;
            case HEIGHT:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a altura relativa da árvore");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] altura da árvore \"%d\"\n", height());
                }
                break;
            case SIZE:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a quantidade de nós da árvore");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] quantidade de nós da árvore é \"%d\"\n", size());
                }
                break;
            case LEAFS:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe a quantidade de nós folhas");
                    sintaxe(cmd);
                }else{
                    textcolor(9);
                    printf("[msg] quantidade de nós folhas da árvore é \"%d\"\n", leaf());
                }
                break;
            case LOADTREE:
                if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Carrega uma árvore do disco para a memória");
                    sintaxe(cmd);
                }else{
                    int ret = loadTree(parametro);
                    if (ret > 0){
                        textcolor(9);
                        printf("[msg] árvore \"%s\" carregada com sucesso\n", parametro);
                    }else if (ret < 0){
                        textcolor(12);
                        puts("[msg] use savetree e deltree na àrvore atual antes de do loadtree");
                    }else{
                        textcolor(12);
                        puts("[msg] não é possível carregar árvore");
                    }
                }
                break;
            case SAVETREE:
                 if (parametro == NULL){
                    erroSintaxe(cmd);
                    sintaxe(cmd);
                }else if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Salva uma árvore da memória para o disco");
                    sintaxe(cmd);
                }else{
                    if (nome == NULL){
                        erroSintaxe(cmd);
                        sintaxe(cmd);
                    }else if (save(parametro, nome)){
                        textcolor(9);
                        printf("[msg] árvore \"%s\" salva com sucesso\n", nome);
                    }else{
                        textcolor(12);
                        puts("[msg] não é possível salvar árvore");
                    }
                }

                break;
            case WHEREAMI:
                if (!(strcmpi(parametro, "/?"))){
                    textcolor(10);
                    puts("Exibe o local (conteúdo) onde se encontra o nó relativo");
                }else if (!wm()){
                    textcolor(12);
                    puts("[msg] árvore vazia");
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


