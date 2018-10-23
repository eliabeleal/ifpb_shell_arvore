#ifndef _SHELL_H_
#define _SHELL_H_

#include "arvoreBinariaStr.h"
#include "pilhaEnc.h"
#include <string.h>
#include <ctype.h>
#include <conio2.h>
void initStruct (void);
int comando (const char cmd[]);
void erroSintaxe (char* cmd);
void sintaxe (char* cmd);
int createRoot (char* param);
int insertNo (char* param);
int rmv (char* param);
int dleft (void);
int dright (void);
void printTree (char* param);
int loadTree (char* nome);
int wm (void);
void helps();
void treeDiagram ();
int go (char* param);
int back (void);
int goRoot(void);
int deltree(char* param);
int height(void);
int size(void);
int leaf (void);
int save (char* param, char* nome);



#endif // _SHELL_H_
