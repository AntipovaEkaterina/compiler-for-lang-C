#include "AST.h"

//dot -Tps graph.gv -o graph.ps

int countNode = 1;

struct AST* Init_Node_AST()
{
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
void Add_Child(struct AST* Node, struct AST* Parent)
{
	struct ListChild* reb;
	reb = (struct ListChild*) calloc(1, sizeof(struct ListChild)); //reb=child
	reb->next = NULL;
	reb->Node = Node;
	struct ListChild* Par_Node = Parent->ListChildren; //pnode=Par_Node
	if (Par_Node == NULL)
	{
		Parent-> ListChildren = reb;
	}else 
	{
		while (Par_Node->next != NULL)
		{
			Par_Node = Par_Node->next;
		}
		Par_Node->next = reb;
	}
}
struct ListChild* searchLastChild(struct AST* node)
{
	struct ListChild* listChild = node->ListChildren;
	while (listChild->next != NULL)
		listChild = listChild->next;
	return listChild;
}
struct AST* getLastChilde(struct AST* node)
{
	return searchLastChild(node)->Node;
}
void deleteLastChild(struct AST *node)
{
	struct ListChild* listChild = searchLastChild(node);
	listChild->Node = NULL;
}
void swapChild(struct AST *parent, struct AST *newChild)
{
	struct AST *oldChild = getLastChilde(parent);
	deleteLastChild(parent);
	addNewChild(parent, newChild);
	Add_Child(oldChild, newChild);
}
void addNewChild(struct AST *parent, struct AST *newChild)
{
	struct ListChild *listChild = searchLastChild(parent);
	listChild->Node = newChild;
	
}
void Set_Line(struct AST *node, char* str )
{
	node->Line = (char*) calloc(strlen(str), sizeof(char*));
	strcpy(node->Line, str);
}
void Set_Token(struct AST* node, char *str)
{ }
void Construc_Tree(struct AST* Node)
{
	FILE *graph;
	if((graph = fopen ("graph.gv", "w")) == NULL){
		printf("!!!!!!!!!I CANN'T OPEN FILE!!!!!!!!!!\n");
		exit(1);
	}
	fprintf(graph, "digraph {\n");
	Construc_Connect(graph, Node);
	fprintf(graph, "}\n");
}
void Construc_Connect(FILE *graph, struct AST* Node)
{
	Create_Box(graph, Node);
	struct ListChild* reb = Node->ListChildren;
	while (reb != NULL)
	{
		fprintf(graph, "\t");
		Line_Output(graph, Node);
		fprintf(graph, "->");
		Line_Output(graph, reb->Node);
		fprintf(graph, "\n");
		Construc_Connect(graph, reb->Node);
		reb = reb->next;
	}   
}
void Create_Box(FILE *graph, struct AST* Node)
{
	fprintf(graph,"\t\"node%d\"[label=%s]\n", Node->Node_id, Node->Line);
}
void Line_Output(FILE *graph, struct AST* Node)
{
	fprintf(graph, "\"node%d\"", Node->Node_id);
}
