/*#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ListTokens.h"
#include "ListChildren.h"

int countNode;

typedef struct AST
{
    ListTokens* Token;
    ListChild* ListChildren;
    int Node_id;  //idNoge
}AST;

AST* Init_Node_AST(ListTokens* Token);

void Add_Child(AST* Node, AST* Parent);


#endif
*/