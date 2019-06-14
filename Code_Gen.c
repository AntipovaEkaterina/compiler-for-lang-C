#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "AST.h"
#include "tabl.h"

FILE *asmb;

void code_gen(struct AST *root);

#endif