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
    ListTokens* knots; //lookahead
    int count;
   // AST *root;
}Parser;

Parser* parser;

void Init_Par(ListTokens* Toens);
void eating(char* x);
void spend();
void Print_Er_Message(int row, int column, char *x);

ListTokens* nextToken();

void S();
void ReturnType();
void Data_Type();
void Ad_Type();
void ArgList();
void Arg();
void StatemenList();
void Head_Arg_List();
void Tail_Arg_List();
void Anuthing();
void Scanf();
void Printf();
void If();
void While();
void Announcement();
void Arithmetic();
void Return();
void Return_Value();
void Value_For_Var();
void Terminal();
void Lit_or_id();
void Expression();
void Expression_T();
void Else();
void Else_T();
void Ident();
void Mas();
void Equal();
void Comparison();
void Priority();
void Priority_T();
void MultPriority();
void MultPriority_T();
void MultPriorityOper();
void AddPriorityOper();
void Group();
void Method_Array();
void CallMethod();
void Neg_Sings();
void Id_SignNumber();
void ElOfArr();
void PassArg();
void TailPassArg();
void Ter_or_Num();
void Or_And();


#endif