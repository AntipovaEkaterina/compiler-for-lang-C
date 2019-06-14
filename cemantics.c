#include "cemantics.h"

void Init_semantic(struct AST *root){
    root->table = Id_Table_Init(0);
    Tree_traversal(root->table, root);
    Count_Error= 0;
}
void Tree_traversal(struct Id_Table *table, struct AST *node)
{
    struct Id_Table* currTable = table;
    if(strcmp(node->Line, "var") == 0 ||
    strcmp(node->Line, "arr") == 0)
    {
        if(node->type == 1 ||
            node->type == 3 ){
            if (node->Token != NULL) {
                char* name = node->Token->lexeme;
                int value = hashtab_hash(name);
                int base_type;
                if(strcmp(node->Line, "var") == 0){
                    base_type = 1;
                }else if(strcmp(node->Line, "arr") == 0){
                    base_type = 2;
                }
                hashtab_add(table->hashtab, name, value, base_type, node->type);
            }else {
                Redecl_Message(node);
            }
        }
        return;
    }else if (strcmp(node->Line, "if") == 0 ||
            strcmp(node->Line, "while") == 0)
    {
        int lvl = table->level + 1;
        node->table = Id_Table_Init(lvl);

        node->table->next = currTable;
        currTable = node->table;

    }else if(strcmp(node->Line, "func") == 0)
    {
        char* name = node->Token->lexeme;

        struct listnode *Found_Node = hashtab_lookup(table->hashtab, name);

        if (Found_Node == NULL)
        {
            int value = hashtab_hash(name);

            hashtab_add(table->hashtab, name, value, 3, 0); 

            int lvl = table->level + 1;
            node->table = Id_Table_Init(lvl);

            node->table->next = currTable;
            currTable = node->table;
        }else{
            Redecl_Message(node);
        }
    }
    struct ListChild* Children = node->ListChildren;
    while (Children != NULL)
    {
        Tree_traversal(currTable,Children->Node);
        Children = Children->next;
    }
}
void Redecl_Message(struct AST *node)
{
    Count_Error++;
    printf("%d:", node->Token->row);
    printf("%d:", node->Token->column);
    printf("ERROR: REDECLORTE");
    printf("%s\n", node->Token->lexeme);
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
                printf("id = %s\tBase Type = %d\tType = %d\n",
                hash_node->key, hash_node->base_type, hash_node->type);
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