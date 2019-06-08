#include "parser.h"

struct AST* Init_Par(ListTokens* Tokens)
{
    parser = (Parser*) calloc(1, sizeof(Parser));   
    parser->Tokens = Tokens;                
    parser->count = 0;                      
    parser->knots = Tokens;                 
    parser->root = NULL;

    struct AST* StartNode = Init_Node_AST();           
    Set_Line(StartNode, "start");

    parser->root = StartNode;
    //ListTokens* ReturnToken = parser->knots;

    S(StartNode);
    printf("End parsing\n");
    return parser->root;
}
/*
S -> <returnType> id (<argList>) { <statementList> } 
*/
void S(struct AST* StartNode)
{

    if(strcmp(parser->knots->token, "int")  == 0 ||
        strcmp(parser->knots->token, "void")  == 0)
    {
    struct AST* SNode = Init_Node_AST();           
    Set_Line(SNode, "S");
    Add_Child(SNode, StartNode);

    ListTokens* ReturnToken = parser->knots;

    int Type; 
    if (strcmp(ReturnToken->lexeme, "int") == 0){
        Type = 1;
    }else if (strcmp(ReturnToken->lexeme, "void") == 0){
        Type = 2;
    }

    ReturnType(SNode);

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    IdNode->Token = parser->knots;
    IdNode->type = Type;
    Add_Child(IdNode, SNode);
        
        eating("id");
        eating("l_paren");
        
    struct AST* ArgListNode = Init_Node_AST();
    Set_Line(ArgListNode, "Arg_List");
    Add_Child(ArgListNode, IdNode);    

    ArgList(ArgListNode);
        eating("r_paren");
        eating("l_brace");

    struct AST* StetementNode = Init_Node_AST();
    Set_Line(StetementNode, "Statement");
    Add_Child(StetementNode, IdNode);

    StatemenList(StetementNode);
        eating("r_brace");

    if(strcmp(parser->knots->token, "int")  == 0 ||
        strcmp(parser->knots->token, "void")  == 0)
    {    
        S(StartNode);

    }
    }
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
<anuthing> -> <scanf> | <printf> | <if> | <while> | <announcement> |
                 id <arith_or_func> | <return> | S
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
        Tat(StetementNode);
    }else if (strcmp(parser->knots->token, "return") == 0)
    {
        Return(StetementNode);
    }else{
        printf("ERROR: %d:%d: EXPECTING scanf OR printf OR while OR if OR int OR char OR id OR return, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<scanf> -> scanf (literal, &id);
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
        eating("ampersand");

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    Add_Child(IdNode, LiteralNode);

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
    Set_Line(PrintfNode, "Printf");
    Add_Child(PrintfNode, StetementNode);

        eating("printf");
        eating("l_paren");

    struct AST* LiteralNode = Init_Node_AST();
    Set_Line(LiteralNode, "Literal");
    Add_Child(LiteralNode, PrintfNode);
    LiteralNode->Token = parser->knots;

        eating("literal");
    
    Lit_or_id(LiteralNode);
        eating("r_paren");
        eating("semicolon");
}
/*
<lit_or_id> -> , id | E
*/
void Lit_or_id(struct AST* LiteralNode)
{
    if (strcmp(parser->knots->token, "comma") == 0)
    {        
        eating("comma");

        struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, LiteralNode);

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

    Expr(IfNode);
        eating("r_paren");
        eating("l_brace");

    struct AST* StatNode = Init_Node_AST();
    Set_Line(StatNode, "StatementList");
    Add_Child(StatNode, IfNode);

    StatemenList(StatNode); 
        eating("r_brace");
    Else(IfNode);
}
/*
<else> -> else <else`> | E
*/
void Else(struct AST* IfNode)
{
    if (strcmp(parser->knots->token, "else") == 0)
    {
        eating("else");
        Else_T(IfNode);
    }
}
/*
<else_t> -> { <statementList> } | <if> 
*/
void Else_T(struct AST* IfNode)
{
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        struct AST* ElseTNode = Init_Node_AST();
        Set_Line(ElseTNode, "Expresion");
        Add_Child(ElseTNode, IfNode); 

        eating("l_paren");

    struct AST* StatNode = Init_Node_AST();
    Set_Line(StatNode, "StatementList");
    Add_Child(StatNode, ElseTNode);

    StatemenList(StatNode);
        eating("r_paren");
    } else if (strcmp(parser->knots->token, "if") == 0)
    {
        If(IfNode);
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
    Set_Line(WhileNode, "while");
    Add_Child(WhileNode, StetementNode);
    
        eating("while");
        eating("l_paren");
    Expr(WhileNode);
        eating("r_paren");
        eating("l_brace");

    struct AST* StatNode = Init_Node_AST();
    Set_Line(StatNode, "StatementList");
    Add_Child(StatNode, WhileNode);

    StatemenList(StatNode);
        eating("r_brace");
}
/*
<expr> -> numeric | id <compar>
*/
void Expr(struct AST* Node)
{
    struct AST* ExprNode = Init_Node_AST();
    Set_Line(ExprNode, "Expresion");
    Add_Child(ExprNode, Node);

    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        struct AST* NumericNode = Init_Node_AST();
        Set_Line(NumericNode, "numeric");
        Add_Child(NumericNode, ExprNode);

        eating("numeric");
    }else if (strcmp(parser->knots->token, "id") == 0)
    {
        struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ExprNode);
        
        eating("id");
        Compar(ExprNode);
    }else{
        printf("ERROR: %d:%d: EXPECTING numeric OR id, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<copmar> -> <comparison> <id_or_num> | E
*/
void Compar(struct AST* ExprNode){
    if (strcmp(parser->knots->token, "d_equally") == 0 || 
        strcmp(parser->knots->token, "not_equal") == 0 ||
        strcmp(parser->knots->token, "less") == 0 ||
        strcmp(parser->knots->token, "more") == 0 ||
        strcmp(parser->knots->token, "l_eq") == 0 || 
        strcmp(parser->knots->token, "m_eq") == 0)
    {
        struct AST* ComparNode = Init_Node_AST();
        Set_Line(ComparNode, parser->knots->token);
        swapChild(ExprNode, ComparNode);
        //Add_Child(ComparNode, ExprNode);

        Comparison(ExprNode);
        Id_or_Num(ComparNode);
    }
}
/*
<comparison> -> == | != | < | <= | > | >=
*/
void Comparison(struct AST* ExprNode)
{
    //struct AST* ComparNode = Init_Node_AST();
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
    Set_Line(AnnouncementNode, "Announcement");
    Add_Child(AnnouncementNode, StetementNode);

    Ad_Type();

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    Add_Child(IdNode, AnnouncementNode);

        eating("id");
    Ident(AnnouncementNode);
        eating("semicolon");
}
/*
<ident> -> [<mas>]<prod_mas> | = <oror> | , id <ident>| E
*/
void Ident(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "l_square") == 0)
    {
        //Set_Line(IdNode, "arv");

            eating("l_square");
        Mas(AnnouncementNode);
            eating("r_square");
        Prod_mas(AnnouncementNode);
    } else if (strcmp(parser->knots->token, "equally") == 0)
    {
        struct AST* ComparNode = Init_Node_AST();
        Set_Line(ComparNode, parser->knots->token);
        swapChild(AnnouncementNode, ComparNode);

            eating("equally");
        Oror(ComparNode);
    } else if (strcmp(parser->knots->token, "comma") == 0)
    {
            eating("comma");

        struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, AnnouncementNode);

        /*struct AST* ComparNode = Init_Node_AST();
        Set_Line(ComparNode, parser->knots->token);
        swapChild(AnnouncementNode, ComparNode);*/

            eating("id");
            Ident(AnnouncementNode);
    }
}
/*
<mas> -> numeric | E
*/
void Mas(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        struct AST* NumericNode = Init_Node_AST();
        Set_Line(NumericNode, "numeric");
        Add_Child(NumericNode, AnnouncementNode);

        eating("numeric");
    }
}
/*
<prod_mas> -> = <equal> | E
*/
void Prod_mas(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "equally") == 0)
    {
        struct AST* ComparNode = Init_Node_AST();
        Set_Line(ComparNode, parser->knots->token);
        swapChild(AnnouncementNode, ComparNode);       

        eating("equally");
        Equal(ComparNode);
    }
}
/*
<equal> -> numeric | literal   
*/
void Equal(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "numeric") == 0)
    {
        struct AST* NumericNode = Init_Node_AST();
        Set_Line(NumericNode, "numeric");
        Add_Child(NumericNode, AnnouncementNode);

        eating("numeric");
    }else if (strcmp(parser->knots->token, "literal") == 0)
    {
        struct AST* LiteralNode = Init_Node_AST();
        Set_Line(LiteralNode, "Literal");
        Add_Child(LiteralNode, AnnouncementNode);
        LiteralNode->Token = parser->knots;

       eating("literal");
    }else{
        printf("ERROR: %d:%d: EXPECTING numeric OR literal, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<tat> -> id <arith_or_func>
*/
void Tat(struct AST* StetementNode){

    struct AST* IdNode = Init_Node_AST();
    Set_Line(IdNode, "id");
    IdNode->Token = parser->knots;
    Add_Child(IdNode, StetementNode);

    eating("id");
    Arith_or_func(StetementNode);
}
/*
<arith_or_func> -> <func_call> | <arithmetic>
*/
void Arith_or_func(struct AST* StetementNode){
    if (strcmp(parser->knots->token, "l_paren") == 0)
    {
        struct AST* FuncCallNode = Init_Node_AST();
        Set_Line(FuncCallNode, "Func_call");
        swapChild(StetementNode, FuncCallNode);

        Func_call(FuncCallNode);
    }else if (strcmp(parser->knots->token, "equally") == 0)
    {
        struct AST* ArithmeticNode = Init_Node_AST();
        Set_Line(ArithmeticNode, "Arithmetic");
        swapChild(StetementNode, ArithmeticNode);

        Arithmetic(ArithmeticNode);
    }else{
        printf("ERROR: %d:%d: EXPECTING equally OR l_paren, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }

}
/*
<func_call> -> id (id , id);
*/
void Func_call(struct AST* IdNode ){

        eating("l_paren");

    struct AST* ArgListNode = Init_Node_AST();
    Set_Line(ArgListNode, "Arg_List");
    Add_Child(ArgListNode, IdNode);
    
    struct AST* Id__Node = Init_Node_AST();
    Set_Line(Id__Node, "id");
    Add_Child(Id__Node, ArgListNode);

        eating("id");
        eating("comma");

    struct AST* Id_Node = Init_Node_AST();
    Set_Line(Id_Node, "id");
    Add_Child(Id_Node, ArgListNode);

        eating("id");
        eating("r_paren");
        eating("semicolon");
}
/*
<arithmetic> ->  = <oror>;
*/
void Arithmetic(struct AST* ArithmeticNode)
{
    struct AST* ComparNode = Init_Node_AST();
    Set_Line(ComparNode, parser->knots->token);
    swapChild(ArithmeticNode, ComparNode);

        eating("equally");
    Oror(ComparNode);
        eating("semicolon");
}
/*
<oror> -> <vot> 
*/
void Oror(struct AST* EquallyNode)
{
    Vot(EquallyNode);
}
/*
<vot> -> <id_or_num> <top>
*/
void Vot(struct AST* EquallyNode)
{
    Id_or_Num(EquallyNode);
    Top(EquallyNode);
}
/*
<top> -> <mult_or_add> <id_or_num> | E 
*/
void Top(struct AST* EquallyNode)
{
    if (strcmp(parser->knots->token, "star") == 0 ||
        strcmp(parser->knots->token, "division") == 0||
        strcmp(parser->knots->token, "plus") == 0 || 
        strcmp(parser->knots->token, "minus") == 0)
    {
        struct AST* ComparNode = Init_Node_AST();
        Set_Line(ComparNode, parser->knots->token);
        swapChild(EquallyNode, ComparNode);

        Mult_or_Add(EquallyNode);
        Id_or_Num(ComparNode);
    }
}
/*
<id_or_num> -> id | <neg_sings>numeric
*/
void Id_or_Num(struct AST* ComparNode)
{
    if (strcmp(parser->knots->token, "id") == 0)
    {
        struct AST* IdNode = Init_Node_AST();
        Set_Line(IdNode, "id");
        Add_Child(IdNode, ComparNode);

        eating("id");
    } else if (strcmp(parser->knots->token, "minus") == 0 ||
                strcmp(parser->knots->token, "plus") == 0 ||
                strcmp(parser->knots->token, "numeric") == 0)
    {
        Neg_Sings(ComparNode);

        struct AST* NumericNode = Init_Node_AST();
        Set_Line(NumericNode, "numeric");
        Add_Child(NumericNode, ComparNode);

        eating("numeric");
    }else
    {
        printf("ERROR: %d:%d: EXPECTING id OR minus OR plus, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<mult_Oper> -> * | /
*/
void Mult_Oper(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "star") == 0)
    {
        struct AST* StarNode = Init_Node_AST();
        Set_Line(StarNode, "star");
        Add_Child(StarNode, AnnouncementNode);

        eating("star");
    }else if (strcmp(parser->knots->token, "division") == 0)
    {
        struct AST* DivisionNode = Init_Node_AST();
        Set_Line(DivisionNode, "division");
        Add_Child(DivisionNode, AnnouncementNode);

        eating("division");
    }else{
        printf("ERROR: %d:%d: EXPECTING star OR division, FIND %s\n",
        parser->knots->row, parser->knots->column, parser->knots->token);
    }
}
/*
<add_Oper> -> + | -
*/
void Add_Oper(struct AST* AnnouncementNode)
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
void Mult_or_Add(struct AST* AnnouncementNode)
{
    if (strcmp(parser->knots->token, "plus") == 0 ||
        strcmp(parser->knots->token, "minus") == 0)
    {
        Add_Oper(AnnouncementNode);
    }else if (strcmp(parser->knots->token, "division") == 0 ||
                strcmp(parser->knots->token, "star") == 0)
    {
        Mult_Oper(AnnouncementNode);
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
    Return_Value(ReturnNode);
        eating("semicolon");
}
/*
<return_Value> -> <neg_sings>numeric | E
*/
void Return_Value(struct AST* ReturnNode)
{
    if (strcmp(parser->knots->token, "minus") == 0 ||
                strcmp(parser->knots->token, "plus") == 0 ||
                strcmp(parser->knots->token, "numeric") == 0)
    {
        Neg_Sings(ReturnNode);

    struct AST* NumericNode = Init_Node_AST();
    Set_Line(NumericNode, "numeric");
    Add_Child(NumericNode, ReturnNode);
    
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
void eating(char* x) 
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
ListTokens* Get_knots()
{
    return parser->knots;
}
void Print_Er_Message(int row, int column, char *x)
{
    printf("%d:%d - ERROR: expecting %s; find %s\n", row, column, x, parser->knots->token);
}