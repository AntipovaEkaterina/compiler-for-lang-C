#ifndef CEMANTICS_H
#define CEMANTICS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AST.h"
#include "tabl.h"

void Init_semantic(struct AST *root);
void Tree_traversal(struct Id_Table *table, struct AST *node);

#endif