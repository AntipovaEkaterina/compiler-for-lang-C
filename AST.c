#include "AST.h"

AST* Init_Node_AST(ListTokens* Token){
    AST *ast = calloc(1, sizeof(AST*));
    ast->Token = Token;
    ast->ListChildren = NULL;
    ast->Node_id = countNode;
    countNode++;

    return ast;
}
void Add_Child(AST* Node, AST* Parent){
    ListChild* reb = calloc(1, sizeof(ListChild*)); //reb=child
    reb->next = NULL;
    ListChild* Par_Node = Parent->ListChildren;
    if (Par_Node = NULL)
    {
        Par_Node = reb;
    }else {
        while (Par_Node->next != NULL)
        {
            Par_Node = Par_Node->next;
        }
        Par_Node->next = reb;
    }