#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListTokens.h"
//#include "ListChildren.h"
#include "lexer.h"
#include "AST.h"

typedef struct Parser
{
    ListTokens* Tokens; 
    ListTokens* knots; //lookahead
    int count;
    struct AST *root;
}Parser;

Parser* parser;

struct AST* Init_Par(ListTokens* Tokens);
void eating(char* x);
void spend();
void Print_Er_Message(int row, int column, char *x);

ListTokens* nextToken();

void S(Parser* parser);
void Func_call();
void ReturnType(struct AST* StartNode);
void Ad_Type();
void ArgList();
void Head_Arg_List();
void Tail_Arg_List();
void Arg();
void StatemenList();
void Anuthing();
void Scanf();
void Printf();
void Lit_or_id();
void If();
void Else();
void Else_T();
void While();
void Expr();
void Compar();
void Comparison();
void Or_And();
void Announcement();
void Ident();
void Mas();
void Prod_mas();
void Equal();
void Arithmetic();
void Oror();
void Vot();
void Top();
void Id_or_Num();
void Mult_Oper();
void Add_Oper();
void Mult_or_Add();
void Return();
void Return_Value();
void Neg_Sings();


#endif