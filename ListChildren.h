/*#ifndef LISTCHILDREN_H
#define LISTCHILDREN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "AST.h"

typedef struct ListChild {
    AST *Node;
    struct ListChild *next;
} ListChild;

ListChild *init_ch();
ListChild *addChild(ListChild *List, AST *Node);


#endif
*/