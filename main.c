#include "lexer.h"
#include "parser.h"
//#include "cemantics.h"
#include "tabl.h"

int main(int argc, char const *argv[]) 
{
    ListTokens* Tokens = IdentifyTokens(argc, argv[1]);
    ListPrint(Tokens);
    struct AST* root = Init_Par(Tokens);
    Construc_Tree(root);

/*int main()
{
    //поиск 
   // struct listnode *node;
    hashtab_init(hashtab);
    hashtab_add(hashtab, "Tigr", 2300);
    hashtab_add(hashtab, "Slon", 190);
    hashtab_add(hashtab, "Volk", 0);
    node = hashtab_lookup(hashtab, "Volk");*/
   // printf("Node: %s, %d\n", node->key, node->value);
    //return 0;
    //удаление 
   // hashtab_delete(hashtab, "Slon");
  //  node = hashtab_lookup(hashtab, "Slon");
   /* if (node != NULL) 
    {
        printf("Node: %s, %d\n", node->key, node->value);
    } else {
        printf("Key 'Slon' not found\n");
    }
    return 0;
}*/

    return 0;
}