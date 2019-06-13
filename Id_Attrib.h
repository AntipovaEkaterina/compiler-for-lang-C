#ifndef ID_ATTRIB_H
#define ID_ATTRIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Id_Attributes 
{
    char lexeme;
    char type;
    char DataType;
    struct Id_Attributes *next;

};

struct Id_Attributes *Id_Att(char lexeme, char type, char Data_Type, struct Id_Attributes *next);

void Set_Lex(char lexeme);
void Set_Type(char type);
void Set_Data_Type(char DataType);
void Set_Next(struct Id_Attributes *next);

char Get_Lex();
char Get_Type();
char Get_Data_Type();

struct Id_Attributes *Get_Next();



#endif