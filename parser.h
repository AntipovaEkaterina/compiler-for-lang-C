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

void S(struct AST* StartNode);
void Func_call(struct AST* StetementNode);
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
void Compar(struct AST* ExprNode);
void Comparison(struct AST* ExprNode);
void Or_And();
void Announcement(struct AST* StetementNode);
void Ident(struct AST* AnnouncementNode);
void Mas(struct AST* AnnouncementNode);
void Prod_mas(struct AST* AnnouncementNodeIdNode);
void Equal(struct AST* AnnouncementNode);
void Tat(struct AST* StetementNode);
void Arith_or_func(struct AST* StetementNode);
void Arithmetic(struct AST* StetementNode);
void Oror(struct AST* EquallyNode);
void Vot(struct AST* EquallyNode);
void Top(struct AST* EquallyNode);
void Id_or_Num(struct AST* ComparNode);
void Mult_Oper(struct AST* AnnouncementNode);
void Add_Oper(struct AST* AnnouncementNode);
void Mult_or_Add(struct AST* AnnouncementNode);
void Return(struct AST* StetementNode);
void Return_Value(struct AST* ReturnNode);
void Neg_Sings();


#endif