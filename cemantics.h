#ifndef CEMANTICS_H
#define CEMANTICS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AST.h"
#include "tabl.h"

int Count_Error;

void Init_semantic(struct AST *root);
void Tree_traversal(struct Id_Table *table, struct AST *node);
void print_table(struct AST *node);
void Redecl_Message(struct AST *node);

#endif