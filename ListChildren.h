#ifndef LISTCHILDREN_H
#define LISTCHILDREN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "AST.h"

struct ListChild 
{
    struct AST *Node;
    struct ListChild *next;
};

struct ListChild *init_ch();
struct ListChild *addChild(struct ListChild *List,struct AST *Node);


#endif
