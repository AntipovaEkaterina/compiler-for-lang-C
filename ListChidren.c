#include "ListChildren.h"

ListChild *init_ch() {
    ListChild *ListChildren;
    ListChildren = (ListChild*)malloc(sizeof(ListChild));
    ListChildren->Node = NULL;
    ListChildren->next = NULL;
    return ListChildren;
}
ListTokens *addChild(ListChild *List, AST *Node) {
    if (List-> Node == NULL) {
        List->Node = Node; 
        return List;
    } else {
        ListChild *List2;
        List2 = (ListChild*)malloc(sizeof(ListChild));
        List->next = List2;
        List->Node = Node; 
        List->next = NULL;
        return List2;
    }
    return NULL;
}
/*void ListPrint(ListTokens *head) {
    ListTokens *print;
    print = head;
    while (print != NULL) {
        printf("Position: %d:%d -- %s '%s'\n", print->row, print->column, print->token, print->lexeme);
        print = print->next;
    }
}*/