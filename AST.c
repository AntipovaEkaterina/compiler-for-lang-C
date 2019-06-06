#include "AST.h"

int countNode = 1;

struct AST* Init_Node_AST(){
    struct AST* ast;
    ast = (struct AST*) calloc(1, sizeof(struct AST));
    ast->Line = NULL;
    ast->Token = NULL;
    ast->ListChildren = NULL;
    ast->Node_id = countNode;
    countNode++;
    ast->type = 0;
    return ast;
}
void Add_Child(struct AST* Node, struct AST* Parent){
    struct ListChild* reb;
    reb = (struct ListChild*) calloc(1, sizeof(struct ListChild)); //reb=child
    reb->next = NULL;
    reb->Node = Node;
    struct ListChild* Par_Node = Parent->ListChildren; //pnode=Par_Node
    if (Par_Node == NULL)
    {
        Parent-> ListChildren = reb;
    }else {
        while (Par_Node->next != NULL)
        {
            Par_Node = Par_Node->next;
        }
        Par_Node->next = reb;
    }
}
//передает узел и строку и он сам устанавливает 
void Set_Line(struct AST *node, char* str )
{
    node->Line = (char*) calloc(strlen(str), sizeof(char*));
    strcpy(node->Line, str);
}