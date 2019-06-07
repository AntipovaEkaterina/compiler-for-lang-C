#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListTokens.h"
#include "lexer.h"
#include "AST.h"

typedef struct Parser
{
    ListTokens* Tokens; 
    ListTokens* knots; 
    int count;
    struct AST *root;
}Parser;

Parser* parser;

struct AST* Init_Par(ListTokens* Tokens);
void eating(char* x);
void spend();
void Print_Er_Message(int row, int column, char *x);

ListTokens* nextToken();
ListTokens* Get_knots();

void S(Parser* parser);
void Func_call(struct AST* StartNode);
void ReturnType(struct AST* StartNode);
void Ad_Type();
void ArgList(struct AST* ArgListNode);
void Head_Arg_List(struct AST* ArgListNode);
void Tail_Arg_List(struct AST* ArgListNode);
void Arg(struct AST* ArgListNode);
void StatemenList(struct AST* StetementNode);
void Anuthing(struct AST* StetementNode);
void Scanf(struct AST* StetementNode);
void Printf(struct AST* StetementNode);
void Lit_or_id(struct AST* LiteralNode);
void If(struct AST* StetementNode);
void Else(struct AST* IfNode);
void Else_T(struct AST* IfNode);
void While(struct AST* StetementNode);
void Expr(struct AST* Node);
void Compar(struct AST* IdNode);
void Comparison(struct AST* IdNode);
void Or_And();
void Announcement(struct AST* StetementNode);
void Ident(struct AST* IdNode);
void Mas(struct AST* IdNode);
void Prod_mas(struct AST* IdNode);
void Equal(struct AST* EquallyNode);
void Arithmetic(struct AST* StetementNode);
void Oror(struct AST* IdNode);
void Vot(struct AST* IdNode);
void Top(struct AST* IdNode);
void Id_or_Num(struct AST* IdNode);
void Mult_Oper(struct AST* EquallyNode);
void Add_Oper(struct AST* EquallyNode);
void Mult_or_Add(struct AST* EquallyNode);
void Return(struct AST* StetementNode);
void Return_Value();
void Neg_Sings();


#endif