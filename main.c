#include "lexer.h"
#include "parser.h"
#include "semantics.h"
#include "tabl.h"

int main(int argc, char const *argv[]) 
{
    ListTokens* Tokens = IdentifyTokens(argc, argv[1]);
    //ListPrint(Tokens);
    struct AST* root = Init_Par(Tokens);
    Construc_Tree(root);
    Init_semantic(root);
    print_table(root);

    return 0;
}