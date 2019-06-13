#include "cemantics.h"

void Init_semantic(struct AST *root){
    root->table = Id_Table_Init(0);
    Tree_traversal(root->table, root);
}
void Tree_traversal(struct Id_Table *table, struct AST *node)
{
    if(strcmp(node->Line, "Announcement") == 0){

    }else if (strcmp(node->Line, "if") == 0 ||
            strcmp(node->Line, "while") == 0)
    {

    }else if(strcmp(node->Line, "Func_call") == 0){
        
    }
}