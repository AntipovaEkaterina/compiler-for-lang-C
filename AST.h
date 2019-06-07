#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ListTokens.h"
#include "ListChildren.h"

struct AST
{
    char *Line;
    ListTokens* Token;
    struct ListChild* ListChildren;
    int Node_id;
    int type;
};

struct AST* Init_Node_AST(); 

void Add_Child(struct AST* Node, struct AST* Parent);
void Set_Line(struct AST* node, char *str);
void Set_Token(struct AST* node, char *str);
void Construc_Tree(struct AST* Node);
void Construc_Connect(FILE *graph, struct AST* Node);
void Create_Box(FILE *graph, struct AST* Node);
void Line_Output(FILE *graph, struct AST* Node);

struct ListChild* searchLastChild(struct AST* node);
struct AST* getLastChilde(struct AST* node);
void deleteLastChild(struct AST *node);
void swapChild(struct AST *parent, struct AST *newChild);
void addNewChild(struct AST *parent, struct AST *newChild);

#endif
