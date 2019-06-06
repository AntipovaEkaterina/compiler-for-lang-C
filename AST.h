#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ListTokens.h"
#include "ListChildren.h"

struct AST
{
    char *Line; //Stroka
    ListTokens* Token;
    struct ListChild* ListChildren;
    int Node_id;  //idNode
    int type;
};

struct AST* Init_Node_AST(); 

void Add_Child(struct AST* Node, struct AST* Parent);
void Set_Line(struct AST* node, char *str);

#endif
