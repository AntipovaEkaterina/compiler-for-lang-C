#include "cemantics.h"

void Init_semantic(struct AST *root){
    root->table = Id_Table_Init(0);
    Tree_traversal(root->table, root);
}
void Tree_traversal(struct Id_Table *table, struct AST *node)
{
    // printf("%s\n", node->Line);
    struct Id_Table* currTable = table;
    if(strcmp(node->Line, "id") == 0 )
    {
        //printf("%s\n", node->Line);
        if(node->type == 1 ||
            node->type == 3 ){
           // struct ListChild* Children = node->ListChildren;
            if (node->Token != NULL) {
                char* name = node->Token->lexeme;
                //printf("%s\n", name);
                int value = hashtab_hash(name);
                hashtab_add(table->hashtab, name, value);
            }
        }
    }else if (strcmp(node->Line, "if") == 0 ||
            strcmp(node->Line, "while") == 0)
    {

    }else if(strcmp(node->Line, "Func_call") == 0){
        
    }
    struct ListChild* Children = node->ListChildren;
    while (Children != NULL)
    {
        Tree_traversal(currTable,Children->Node);
        Children = Children->next;
    }
}
void print_table(struct AST *node)
{
    if (node->table != NULL)
    {
        printf("    level   =   %d\n", node->table->level);
        for (int i = 0; i < HASHTAB_SIZE; i++)
        {
            struct listnode *hash_node = node->table->hashtab[i] ;
            if (hash_node != NULL)
            {
                printf("%s\n", hash_node->key);
            }
        }
    }
    struct ListChild* Children = node->ListChildren;
    while (Children != NULL)
    {
        print_table(Children->Node);
        Children = Children->next;
    }
}