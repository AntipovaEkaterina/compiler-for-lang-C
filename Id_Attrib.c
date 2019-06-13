#include "Id_Attrib.h"

struct Id_Attributes *Id_Att(char lexeme, char type, char Data_Type, struct Id_Attributes *next)
{
    struct Id_Attributes* Id_Att;
    Id_Att = (struct Id_Attributes*) calloc(1, sizeof(struct Id_Attributes));
    Id_Att->lexeme = lexeme;
    Id_Att->type = type;
    Id_Att->DataType = Data_Type;
    Id_Att->next = next;

    return Id_Att;
}

char Get_Lex()
{
   // return lexeme;
}
char Get_Type()
{
   // return type;
}
char Get_Data_Type()
{
   // return Data_Type;
}
struct Id_Attributes *Get_Next(){
   // return next;
}
void Set_Lex(char lexeme);
void Set_Type(char type);
void Set_Data_Type(char DataType);
void Set_Next(struct Id_Attributes *next);
