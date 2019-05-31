#include "lexer.h"
#include "parser.h"

int main(int argc, char const *argv[]) {

    ListTokens* Tokens = IdentifyTokens(argc, argv[1]);
    ListPrint(Tokens);
    //S(Tokens);
    Init_Par(Tokens);
    return 0;
    
}


