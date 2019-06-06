#include "parser.h"

void Init_Par(ListTokens* Tokens)
{
    parser = calloc(1, sizeof(Parser*));  //конструктор, создаем элемент листтокенс 1 кол-во структур 
    parser->Tokens = Tokens;                //указатель на первый токен
    parser->count = 0;                      //счетчик узлов
    parser->knots = Tokens;                 //указатель на текущий токен

    S();
    printf("End parsing\n");
}
/*
S -> <returnType> id (<argList>) { <statementList> }
*/
void S(){
    struct AST* StartNode = Init_Node_AST();           //создали структуру (эл-т) узла аст
    Set_Line(StartNode, "start");
    ReturnType(StartNode);
        eating("id");
        eating("l_paren");
    ArgList();
        eating("r_paren");
        eating("l_brace");
    StatemenList();
        eating("r_brace");
}
/*
<func_call> -> id (<argList>);
*/
void Func_call(){
    eating("id");
    eating("l_paren");
    ArgList();
    eating("r_paren");
    eating("semicolon");
}
/*
<returnType> -> int | void
*/
void ReturnType(struct AST* StartNode)
{
    if(strcmp(parser->knots->token, "int")  == 0)
    {
        struct AST* ReturnTypeNode = Init_Node_AST();  
        Set_Line(ReturnTypeNode, "Return type");
        Add_Child(ReturnTypeNode, StartNode);

        eating("int");
    }else if (strcmp(parser->knots->token,"void") == 0)
    {
        eating("void");
    }else{
        printf("ERROR: %d:%d: EXPECTING int OR void, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
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
    }else{
        printf("ERROR: %d:%d: EXPECTING int OR char, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
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
       /* AST* ArgListNode = Init_Node_AST(); 
        ArgListNode->Line = calloc(6, sizeof(char*));
        ArgListNode->Line = "Head arg list";
        Add_Child(reb, )*/

        Head_Arg_List();
        Tail_Arg_List();
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
        strcmp(parser->knots->token, "id") == 0 ||
        strcmp(parser->knots->token, "return") == 0)
    {
        Anuthing();
        StatemenList();
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
    }else{
        printf("ERROR: %d:%d: EXPECTING scanf OR printf OR while OR if OR int OR char OR id OR return, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
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
<lit_or_id> -> , id | E
*/
void Lit_or_id()
{
    if (strcmp(parser->knots->token, "comma") == 0)
    {
        eating("comma");
        eating("id"); 
    }
        
}
/*
<if> -> if (<expr>) { <statementList>} <else>
*/
void If()
{
        eating("if");
        eating("l_paren");
    Expr();
        eating("r_paren");
        eating("l_brace");
    StatemenList(); 
        eating("r_brace");
    Else();
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
<else_t> -> { <statementList> } | <if> 
*/
void Else_T()
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        eating("l_paren");
    StatemenList();
        eating("r_paren");
    } else if (strcmp(parser->knots->token, "if") == 0)
    {
        If();
    }else{
        printf("ERROR: %d:%d: EXPECTING l_paren OR if, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<while> -> while (<expr>) { <statementList> }
*/
void While()
{
        eating("while");
        eating("l_paren");
    Expr();
        eating("r_paren");
        eating("l_brace");
    StatemenList();
        eating("r_brace");
}
/*
<expr> -> numeric | id <compar>
*/
void Expr()
{
    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        eating("numeric");
    }else if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
        Compar();
    }else{
        printf("ERROR: %d:%d: EXPECTING numeric OR id, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<copmar> -> <comparison> <id_or_num> | E
*/
void Compar(){
    if (strcmp(parser->knots->token, "d_equally") == 0 || 
        strcmp(parser->knots->token, "not_equal") == 0 ||
        strcmp(parser->knots->token, "less") == 0 ||
        strcmp(parser->knots->token, "more") == 0 ||
        strcmp(parser->knots->token, "l_eq") == 0 || 
        strcmp(parser->knots->token, "m_eq") == 0)
    {
        Comparison();
        Id_or_Num();
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
    }else{
        printf("ERROR: %d:%d: EXPECTING == OR != OR < OR <= OR > OR >= , FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
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
    }else{
        printf("ERROR: %d:%d: EXPECTING or OR and, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<announcement> -> <ad_Type> id<ident> ;
*/
void Announcement()
{
    Ad_Type();
        eating("id");
    Ident();
        eating("semicolon");
}
/*
<ident> -> [<mas>]<prod_mas> | = numeric
*/
void Ident()
{
    if (strcmp(parser->knots->token, "l_square") == 0)
    {
        eating("l_square");
        Mas();
            eating("r_square");
        Prod_mas();
    } else if (strcmp(parser->knots->token, "equally") == 0)
    {
        eating("equally");
        Id_or_Num();
        Mult_or_Add();
        Id_or_Num();
        //eating("numeric");
    }else{
        printf("ERROR: %d:%d: EXPECTING l_square OR equally, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
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
<prod_mas> -> = <equal> | E
*/
void Prod_mas()
{
    if (strcmp(parser->knots->token, "equally") == 0)
    {
        eating("equally");
        Equal();
    }
}
/*
<equal> -> numeric | literal   
*/
void Equal()
{
    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        eating("numeric");
    }else if (strcmp(parser->knots->token, "literal") == 0)
    {
       eating("literal");
    }else{
        printf("ERROR: %d:%d: EXPECTING numeric OR literal, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<arithmetic> -> id = <oror>;
*/
void Arithmetic()
{
        eating("id");
        eating("equally");
    Oror();
        eating("semicolon");
}
/*
<oror> -> <vot> 
*/
void Oror()
{
    Vot();
}
/*
<vot> -> <id_or_num> <top>
*/
void Vot()
{
    Id_or_Num();
    Top();
}
/*
<top> -> <mult_or_add> <id_or_num> | E 
*/
void Top()
{
    if (strcmp(parser->knots->token, "star") == 0 ||
        strcmp(parser->knots->token, "division") == 0||
        strcmp(parser->knots->token, "plus") == 0 || 
        strcmp(parser->knots->token, "minus") == 0)
    {
        Mult_or_Add();
        Id_or_Num();
    }
}
/*
<id_or_num> -> id | <neg_sings>numeric
*/
void Id_or_Num()
{
    if (strcmp(parser->knots->token, "id") == 0)
    {
        eating("id");
    } else if (strcmp(parser->knots->token, "minus") == 0 ||
                strcmp(parser->knots->token, "plus") == 0 ||
                strcmp(parser->knots->token, "numeric") == 0)
    {
        Neg_Sings();
        eating("numeric");
    }else{
        printf("ERROR: %d:%d: EXPECTING id OR minus OR plus, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<mult_Oper> -> * | /
*/
void Mult_Oper()
{
    if (strcmp(parser->knots->token, "star") == 0)
    {
        eating("star");
    }else if (strcmp(parser->knots->token, "division") == 0)
    {
        eating("division");
    }else{
        printf("ERROR: %d:%d: EXPECTING star OR division, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<add_Oper> -> + | -
*/
void Add_Oper()
{
    if (strcmp(parser->knots->token, "plus") == 0)
    {
        eating("plus");
    }else if (strcmp(parser->knots->token, "minus") == 0)
    {
        eating("minus");
    }else{
        printf("ERROR: %d:%d: EXPECTING plus OR minus, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<mult_or_add> -> <mult_Oper> | <add_Oper>
*/
void Mult_or_Add()
{
    if (strcmp(parser->knots->token, "plus") == 0 ||
        strcmp(parser->knots->token, "minus") == 0)
    {
        Add_Oper();
    }else if (strcmp(parser->knots->token, "division") == 0 ||
                strcmp(parser->knots->token, "star") == 0)
    {
        Mult_Oper();
    }else{
        printf("ERROR: %d:%d: EXPECTING plus OR minus OR division OR star, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<return> -> return <return_Value>;
*/
void Return()
{
        eating("return");
    Return_Value();
        eating("semicolon");
}
/*
<return_Value> -> <neg_sings>numeric | E
*/
void Return_Value()
{
    if (strcmp(parser->knots->token, "minus") == 0 ||
                strcmp(parser->knots->token, "plus") == 0 ||
                strcmp(parser->knots->token, "numeric") == 0)
    {
        Neg_Sings();
        eating("numeric");
    }
}
/*
<neg_sings> -> - | + | E
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