#include "parser.h"

struct AST* Init_Par(ListTokens* Tokens)
{
    parser = calloc(1, sizeof(Parser*));  //конструктор, создаем элемент листтокенс 1 кол-во структур 
    parser->Tokens = Tokens;                //указатель на первый токен
    parser->count = 0;                      //счетчик узлов
    parser->knots = Tokens;                 //указатель на текущий токен
    parser->root = NULL;

    S(parser);
    printf("End parsing\n");
    return parser->root;
}
/*
S -> <returnType> id (<argList>) { <statementList> }
*/
void S(Parser* parser){
    struct AST* StartNode = Init_Node_AST();           //создали структуру (эл-т) узла аст
    Set_Line(StartNode, "start");

    parser->root = StartNode;
    ListTokens* ReturnToken = parser->knots;

    int Type; 
    if (strcmp(ReturnToken->lexeme, "int") == 0){
        Type = 1;
    }else if (strcmp(ReturnToken->lexeme, "void") == 0){
        Type = 2;
    }

    ReturnType(StartNode);

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    IdNode->Token = parser->knots;
    IdNode->type = Type;
    Add_Child(IdNode, StartNode);
        
        eating("id");
        eating("l_paren");
        
    struct AST* ArgListNode = Init_Node_AST();
    Set_Line(ArgListNode, "Arg List");
    Add_Child(ArgListNode, IdNode);    

    ArgList(ArgListNode);
        eating("r_paren");
        eating("l_brace");

    struct AST* StetementNode = Init_Node_AST();
    Set_Line(StetementNode, "Statement");
    Add_Child(StetementNode, IdNode);

    StatemenList(StetementNode);
        eating("r_brace");
}
/*
<func_call> -> id (<argList>);
*/
void Func_call(StartNode){
    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    IdNode->Token = parser->knots;
    Add_Child(IdNode, StartNode);

        eating("id");
        eating("l_paren");

    struct AST* ArgListNode = Init_Node_AST();
    Set_Line(ArgListNode, "Arg List");
    Add_Child(ArgListNode, IdNode);

    ArgList(ArgListNode);
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
void ArgList(struct AST* ArgListNode)
{
    if (strcmp(parser->knots->token, "int") == 0 || 
        strcmp(parser->knots->token, "char") == 0)
    {
        Head_Arg_List(ArgListNode);
        Tail_Arg_List(ArgListNode);
    }
}
/*
<head_Arg_List> -> <arg>
*/
void Head_Arg_List(struct AST* ArgListNode)
{
    Arg(ArgListNode);
}
/*
<tail_Arg_List> -> ,<arg><tail_Arg_List> | E
*/
void Tail_Arg_List(struct AST* ArgListNode)
{
    if (strcmp(parser->knots->token, "comma" ) == 0)
    {
        eating("comma");

        Arg(ArgListNode);
        Tail_Arg_List(ArgListNode);
    }
}
/*
<arg> -> <ad_Type> id
*/
void Arg(struct AST* ArgListNode)
{
    ListTokens* ReturnToken = parser->knots;

    int Type; 
    if (strcmp(ReturnToken->lexeme, "int") == 0){
        Type = 1;
    }else if (strcmp(ReturnToken->lexeme, "char") == 0){
        Type = 3;
    }

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    Add_Child(IdNode, ArgListNode);
    IdNode->type = Type;

        Ad_Type();
        eating("id");       
}
/*
<statementList> -> <anuthing><statementList>  | E
*/
void StatemenList(struct AST* StetementNode)
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
        Anuthing(StetementNode);
        StatemenList(StetementNode);
    }
}
/*
<anuthing> -> <scanf> | <printf> | <if> | <while> | 
                <announcement> | <arithmetic> | <return>
*/
void Anuthing(struct AST* StetementNode)
{
    if (strcmp(parser->knots->token, "scanf") == 0)
    {
        Scanf(StetementNode);
    }else if (strcmp(parser->knots->token, "printf") == 0)
    {
        Printf(StetementNode);
    } else if (strcmp(parser->knots->token, "while") == 0)
    {
        While(StetementNode);
    }else if (strcmp(parser->knots->token, "if") == 0)
    {
        If(StetementNode);
    }else if (strcmp(parser->knots->token, "int") == 0 ||
        strcmp(parser->knots->token, "char") == 0)
    {
        Announcement(StetementNode);
    }else if (strcmp(parser->knots->token, "id") == 0)
    {
        Arithmetic(StetementNode);
    }else if (strcmp(parser->knots->token, "return") == 0)
    {
        Return(StetementNode);
    }else{
        printf("ERROR: %d:%d: EXPECTING scanf OR printf OR while OR if OR int OR char OR id OR return, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<scanf> -> scanf (literal, id);
*/
void Scanf(struct AST* StetementNode)
{
    struct AST* ScanfNode = Init_Node_AST();
    Set_Line(ScanfNode, "Scanf");
    Add_Child(ScanfNode, StetementNode);

        eating("scanf");
        eating("l_paren");

    struct AST* LiteralNode = Init_Node_AST();
    Set_Line(LiteralNode, "Literal");
    Add_Child(LiteralNode, ScanfNode);
    LiteralNode->Token = parser->knots; 

        eating("literal");
        eating("comma");

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    Add_Child(IdNode, ScanfNode);

        eating("id");
        eating("r_paren");
        eating("semicolon");
}
/*
<printf> -> printf (literal <lit_or_id>);
*/
void Printf(struct AST* StetementNode)
{
    struct AST* PrintfNode = Init_Node_AST();
    Set_Line(PrintfNode, "Print");
    Add_Child(PrintfNode, StetementNode);

        eating("printf");
        eating("l_paren");

    struct AST* LiteralNode = Init_Node_AST();
    Set_Line(LiteralNode, "Literal");
    Add_Child(LiteralNode, PrintfNode);
    LiteralNode->Token = parser->knots;

        eating("literal");

    struct AST* LitOrIdNode = Init_Node_AST();
    Set_Line(LitOrIdNode, "literal or id");
    Add_Child(LitOrIdNode, LiteralNode);
    
    Lit_or_id(PrintfNode);
        eating("r_paren");
        eating("semicolon");
}
/*
<lit_or_id> -> , id | E
*/
void Lit_or_id(struct AST* PrintfNode)
{
    if (strcmp(parser->knots->token, "comma") == 0)
    {
        eating("comma");

        struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, PrintfNode);

        eating("id"); 
    }   
}
/*
<if> -> if (<expr>) { <statementList>} <else>
*/
void If(struct AST* StetementNode)
{
    struct AST* IfNode = Init_Node_AST();
    Set_Line(IfNode, "if");
    Add_Child(IfNode, StetementNode);

        eating("if");
        eating("l_paren");
    Expr();
        eating("r_paren");
        eating("l_brace");
    StatemenList(StetementNode); 
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
    StatemenList(StetementNode);
        eating("r_paren");
    } else if (strcmp(parser->knots->token, "if") == 0)
    {
        If(StetementNode);
    }else{
        printf("ERROR: %d:%d: EXPECTING l_paren OR if, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<while> -> while (<expr>) { <statementList> }
*/
void While(struct AST* StetementNode)
{
    struct AST* WhileNode = Init_Node_AST();
    Set_Line(WhileNode, "if");
    Add_Child(WhileNode, StetementNode);
    
        eating("while");
        eating("l_paren");
    Expr();
        eating("r_paren");
        eating("l_brace");
    StatemenList(StetementNode);
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
        /*struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ArgListNode);*/
        

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
void Announcement(struct AST* StetementNode)
{
    struct AST* AnnouncementNode = Init_Node_AST();
    Set_Line(AnnouncementNode, "AnnouncementNode");
    Add_Child(AnnouncementNode, StetementNode);

    Ad_Type();

    /*struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ArgListNode);*/

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
    /*    struct AST* LiteralNode = Init_Node_AST();
        Set_Line(LiteralNode, "Literal");
        Add_Child(LiteralNode, PrintfNode);
        LiteralNode->Token = parser->knots;*/

       eating("literal");
    }else{
        printf("ERROR: %d:%d: EXPECTING numeric OR literal, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<arithmetic> -> id = <oror>;
*/
void Arithmetic(struct AST* StetementNode)
{
    struct AST* ArithmeticNode = Init_Node_AST();
    Set_Line(ArithmeticNode, "Arithmetic");
    Add_Child(ArithmeticNode, StetementNode);

/*struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ArgListNode);*/

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
/*struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ArgListNode);*/

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
void Return(struct AST* StetementNode)
{
    struct AST* ReturnNode = Init_Node_AST();
    Set_Line(ReturnNode, "Return");
    Add_Child(ReturnNode, StetementNode);

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