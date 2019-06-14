#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "AST.h"
#include "tabl.h"

FILE *asmb;

int regValAri[6];
int regValArg[6];

struct Id_Table *currTable;

void code_gen(struct AST *root);
void treversal(struct AST *node);
char* rightPart(struct AST *node);

void genFunc(struct AST *node);

int getRegForAri();
void setRegForAri(int numReg, int value);
char* regAriNumToStr(int numReg);
int regAriStrToReg(char* strReg);
void freeRegValAri(char* strReg);
int getValRegAri(int numReg);

int getSizeNumber(int num);

void Mov(char *str1, char *str2);


#endif