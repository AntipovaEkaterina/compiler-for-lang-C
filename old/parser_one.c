#include "parser.h"

void Init_Par(ListTokens* Tokens)
{
    parser = calloc(1, sizeof(Parser*));
    parser->Tokens = Tokens;
    parser->count = 0;
    parser->knots = Tokens;

    S();
    printf("End parsing\n");
}
/*
S -> <returnType> id (<argList>) { <statementList> }
*/
void S(){
    
    ReturnType();
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
    }
        eating("l_paren");
    ArgList();
        eating("r_paren");
        eating("l_brace");
    StatemenList();
        eating("r_brace");
}
/*
<returnType> -> <ad_Type>| void
*/
void ReturnType()
{
    if(strcmp(parser->knots->token, "int")  == 0)
    {
        eating("int");
    }else if (strcmp(parser->knots->token,"void") == 0)
    {
        eating("void");
    }

}
/*
<ad_Type> -> int | char
*/
void Ad_Type()
{
    if(strcmp(parser->knots->token, "int") == 0)
    {
        eating("int");
    }else if (strcmp(parser->knots->token, "char") == 0)
    {
       eating("char");
    }
}
/*
<argList> -> <head_Arg_List><tail_Arg_List> | E
*/
void ArgList()
{
    if (strcmp(parser->knots->token, "int") == 0 || 
        strcmp(parser->knots->token, "char") == 0)
    {
        Head_Arg_List();
        Tail_Arg_List();
    }   
}
/*
<arg> -> <ad_Type> id
*/
void Arg()
{
        Ad_Type();
        eating("id");
        
}
/*
<statementList> -> <anuthing><statementList>  | E
*/
void StatemenList()
{
    if (strcmp(parser->knots->token, "scanf") == 0 || 
        strcmp(parser->knots->token, "printf")  == 0||
        strcmp(parser->knots->token, "if") == 0 ||
        strcmp(parser->knots->token, "while") == 0 ||
        strcmp(parser->knots->token, "int") == 0 ||
        strcmp(parser->knots->token, "char") == 0 ||
        strcmp(parser->knots->token, "id =") == 0 ||
        strcmp(parser->knots->token, "return") == 0)
    {
        Anuthing();
        StatemenList();
    }
}
/*
<head_Arg_List> -> <arg>
*/
void Head_Arg_List()
{
    Arg();
}
/*
<tail_Arg_List> -> ,<arg><tail_Arg_List> | E
*/
void Tail_Arg_List()
{
    if (strcmp(parser->knots->token, "comma" ) == 0)
    {
        eating("comma");
        Arg();
        Tail_Arg_List();
    }
}

/*
<anuthing> -> <scanf> | <printf> | <if> | <while> | 
                <announcement> | <arithmetic> | <return>
*/
void Anuthing()
{
    if (strcmp(parser->knots->token, "scanf") == 0)
    {
        Scanf();
    }else if (strcmp(parser->knots->token, "printf") == 0)
    {
        Printf();
    } else if (strcmp(parser->knots->token, "while") == 0)
    {
        While();
    }else if (strcmp(parser->knots->token, "if") == 0)
    {
        If();
    }else if (strcmp(parser->knots->token, "int") == 0 ||
        strcmp(parser->knots->token, "char") == 0)
    {
        Announcement();
    }else if (strcmp(parser->knots->token, "id") == 0)
    {
        Arithmetic();
    }else if (strcmp(parser->knots->token, "return") == 0)
    {
        Return();
    }
}
/*
<scanf> -> scanf (literal, id);
*/
void Scanf()
{
        eating("scanf");
        eating("l_paren");
        eating("literal");
        eating("comma");
        eating("id");
        eating("r_paren");
        eating("semicolon");
}
/*
<printf> -> printf (literal <lit_or_id>);
*/
void Printf()
{
        eating("printf");
        eating("l_paren");
        eating("literal");
    Lit_or_id();
        eating("r_paren");
        eating("semicolon");
}
/*
<if> -> if (<expression>) {	<statementList>;} <else>
*/
void If()
{
        eating("if");
        eating("l_paren");
    Expression();
        eating("r_paren");
        eating("l_brace");
    StatemenList(); 
    //    Anuthing();
        eating("r_brace");
    Else();
}
/*
<while> -> while (<expression>) { <statementList>; }
*/
void While()
{
        eating("while");
        eating("l_paren");
 //   Expression();
 //     eating("numeric");
        Arithmetic();
        eating("r_paren");
        eating("l_brace");
    StatemenList();
        eating("r_brace");
}
/*
<announcement> -> <ad_Type> id<ident> ;
*/
void Announcement()
{
    Ad_Type();
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
    }
    Ident();
    if (strcmp(parser->knots->token, "semicolon") == 0)
    {
        eating("semicolon");
    }
}
/*
<arithmetic> -> id = <terminal>; 
<arithmetic> -> id = <ter_or_num>; 
*/
void Arithmetic()
{
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
    }
        eating("equally");
    Ter_or_Num();
        eating("semicolon");
}
/*
<ter_or_num>-> <terminal> | numeric
*/
void Ter_or_Num(){
    if (strcmp(parser->knots->token, "comma") == 0)
    {
        eating("comma");
        Terminal();
    }else if (strcmp(parser->knots->token, "numeric") == 0)
    {
        eating("numeric");
    } 
}
/*
<return> -> return <return_Value>;
*/
void Return()
{
    if (strcmp(parser->knots->token, "return") == 0)
    {
        eating("return");
    }
    Return_Value();
    if (strcmp(parser->knots->token, "semicolon") == 0)
    {
        eating("semicolon");
    }
}
/*
<return_Value> -> <value_For_Var> | E
*/
void Return_Value()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        eating("l_paren");
        Value_For_Var();
    }
}
/*
<value_For_Var> -> <terminal> | oneChar
*/
void Value_For_Var()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        eating("l_paren");
        Terminal();
    }else if (strcmp(parser->knots->token, "OneChar") == 0)
    {
        eating("OneChar");
    }
}
/*
<terminal> -> <Priority>
*/
void Terminal()
{
    Priority();
}
/*
<lit_or_id> -> , id | E 
*/
void Lit_or_id()
{
        eating("comma");
        eating("id"); 
}
/*
<expression> -> <terminal><expression`>
*/
void Expression()
{
    Terminal();
    Expression_T();
}
/*
<expression_t> -> <comparison><terminal> | E
*/
void Expression_T()
{
    if (strcmp(parser->knots->token, "d_equally") == 0 || 
        strcmp(parser->knots->token, "not_equal") == 0 ||
        strcmp(parser->knots->token, "less") == 0 ||
        strcmp(parser->knots->token, "more") == 0 ||
        strcmp(parser->knots->token, "l_eq") == 0 || 
        strcmp(parser->knots->token, "m_eq") == 0)
    {
        Comparison();
        Terminal();
    }
}
/*
<else> -> else <else`> | E
*/
void Else()
{
    if (strcmp(parser->knots->token, "else") == 0)
    {
        eating("else");
        Else_T();
    }
}
/*
<else`> -> { <statementList>; } | <if> 
*/
void Else_T()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        eating("l_paren");
        StatemenList();
            eating("semicolon");
            eating("r_paren");
    } else if (strcmp(parser->knots->token, "if") == 0)
    {
        If();
    }
}
/*
<ident> -> [<mas>] | = <equal>
*/
void Ident()
{
    if (strcmp(parser->knots->token, "l_square") == 0)
    {
        eating("l_square");
        Mas();
            eating("r_square");
    } else if (strcmp(parser->knots->token, "equally") == 0)
    {
        eating("equally");
        Equal();
    }
}
/*
<mas> -> numeric | E
*/
void Mas()
{
    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        eating("numeric");
    }
}
/*
<equal> -> id | <neg_sings>numeric | literal
*/
void Equal()
{
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
    }else if (strcmp(parser->knots->token, "minus") == 0 ||
            strcmp(parser->knots->token, "plus") == 0)
    {
        Neg_Sings();
        if (strcmp(parser->knots->token, "numeric") == 0)
        {
            eating("numeric");
        }
    } else if (strcmp(parser->knots->token, "literal") == 0)
    {
        eating("literal");
    }    
}
/*
<comparison> -> == | != | < | <= | > | >=
*/
void Comparison()
{
    if (strcmp(parser->knots->token, "d_equally") == 0)
    {
        eating("d_equally");
    } else if (strcmp(parser->knots->token, "not_equal") == 0)
    {
        eating("not_equal");
    } else if (strcmp(parser->knots->token, "less") == 0)
    {
        eating("less");
    } else if (strcmp(parser->knots->token, "more") == 0)
    {
        eating("more");
    } else if (strcmp(parser->knots->token, "l_eq") == 0)
    {
        eating("l_eq");
    }else if (strcmp(parser->knots->token, "m_eq") == 0)
    {
        eating("m_eq");
    }
}
/*
<Priority> -> <multPriority><Priority`>
*/
void Priority()
{
    MultPriority();
    Priority_T();
}
/*
<Priority`> -> <addPriorityOper><multPriority><Priority`> | E
*/
void Priority_T()
{
    if (strcmp(parser->knots->token, "plus") == 0 || 
        strcmp(parser->knots->token, "minus") == 0)
    {
        AddPriorityOper();
        MultPriority();
        Priority_T();
    }
}
/*
<multPriority> -> <group><multPriority`>
*/
void MultPriority()
{
    Group();
    MultPriority_T();
}
/*
<multPriority`> -> <multPriorityOper><group><multPriority`> | E
*/
void MultPriority_T()
{
    if (strcmp(parser->knots->token, "star") == 0 || 
        strcmp(parser->knots->token, "division") == 0)
    {
        MultPriorityOper();
        Group();
        MultPriority_T();
    }    
}
/*
<multPriorityOper> -> * | /
*/
void MultPriorityOper()
{
    if (strcmp(parser->knots->token, "star") == 0)
    {
        eating("star");
    }else if (strcmp(parser->knots->token, "division") == 0)
    {
        eating("division");
    }
}
/*
<addPriorityOper> -> + | -
*/
void AddPriorityOper()
{
    if (strcmp(parser->knots->token, "plus") == 0)
    {
        eating("plus");
    }else if (strcmp(parser->knots->token, "minus") == 0)
    {
        eating("minus");
    }
}
/*
<group> -> (<terminal>) | <id_SignNumber>
*/
void Group()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        eating("l_paren");
        Terminal();
        if (strcmp(parser->knots->token, "r_paren") == 0)
        {
            eating("r_paren");
        }
    }else if (strcmp(parser->knots->token, "id")  == 0||
              strcmp(parser->knots->token, "minus") == 0 ||
              strcmp(parser->knots->token, "plus") == 0  )
    {
        Id_SignNumber();
    }
}
/*
<method_Array> -> <callMethod> | <elOfArr> | E
*/
void Method_Array()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        CallMethod();
    }else if (strcmp(parser->knots->token, "l_square") == 0)
    {
        ElOfArr();
    }
}
/*
<callMethod> -> (<passArg>)
*/
void CallMethod()
{
        eating("l_paren");
    PassArg();
        eating("r_paren");
}
/*
<neg_sings> -> - | + 
*/
void Neg_Sings()
{
    if (strcmp(parser->knots->token, "plus") == 0)
    {
        eating("plus");
    }else if (strcmp(parser->knots->token, "minus") == 0)
    {
        eating("minus");
    }
}
/*
<id_SignNumber> -> id<method_Array> | <neg_sings>numeric
*/
void Id_SignNumber()
{
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
        Method_Array();
    }else if (strcmp(parser->knots->token, "minus") == 0 ||
              strcmp(parser->knots->token, "plus") == 0)
    {
        Neg_Sings();
        if (strcmp(parser->knots->token, "numeric") == 0)
        {
            eating("numeric");
        }
    }
}
/*
<elOfArr> -> [numeric]
*/
void ElOfArr()
{
    eating("l_square");
    eating("numeric");
    eating("r_square");
}
/*
<passArg> -> <terminal><tailPassArg> | E
*/
void PassArg()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        Terminal();
        Tail_Arg_List();
    }
}
/*
<tailPassArg> -> ,<terminal><tailPassArg> | E
*/
void TailPassArg()
{
    if (strcmp(parser->knots->token, "comma") == 0)
    {
        eating("comma");
        Terminal();
        TailPassArg();
    }
}
/*
<or_and> -> || | && 
*/
void Or_And()
{
    if (strcmp(parser->knots->token, "or") == 0)
    {
        eating("or");
    }else if (strcmp(parser->knots->token, "and") == 0)
    {
        eating("and");
    }
}

void eating(char* x) //void match
{
    if (strcmp(parser->knots->token, x) == 0){
        spend();//consume
    } else
    {
        Print_Er_Message(parser->knots->row, parser->knots->column, x);
        exit(1);
    } 
}

void spend()
{
    parser->knots = nextToken();
}

ListTokens* nextToken()
{
    parser->count++;
    return parser->knots->next;
}

void Print_Er_Message(int row, int column, char *x)
{
    printf("%d:%d - ERROR: expecting %s; find %s\n", row, column, x, parser->knots->token);
}

