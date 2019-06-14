#include "semantics.h"

void Init_semantic(struct AST *root){
	root->table = Id_Table_Init(0);
	Tree_traversal(root->table, root);
	Count_Error= 0;
}
void Tree_traversal(struct Id_Table *table, struct AST *node)
{
	struct Id_Table* currTable = table;
	if(strcmp(node->Line, "var") == 0 || strcmp(node->Line, "arr") == 0)
	{
		if(node->type == 1 || node->type == 3 )
		{
			struct listnode *Found_Node = hashtab_lookup(currTable->hashtab, node->Token->lexeme);
			if (Found_Node == NULL)
			{
				char* name = node->Token->lexeme;
				int value = hashtab_hash(name);
				int base_type;
				if(strcmp(node->Line, "var") == 0)
				{
					base_type = 1;
				}else if(strcmp(node->Line, "arr") == 0)
				{
					base_type = 2;
				}
				hashtab_add(currTable->hashtab, name, value, base_type, node->type);
				//Add_Size_Table(currTable);
			   // hashtab_setOffset(currTable->hashtab, name, table->sizeTable);
			} else {
				Redecl_Message(node);
			}
		} else {
			char* name = node->Token->lexeme;
			struct listnode *Found_Node = Find_in_all_table(currTable, name);
			if (Found_Node == NULL)
			{
				Not_Declar_Message(node);
			}
		}
		return;
	}else if (strcmp(node->Line, "if") == 0 ||
			strcmp(node->Line, "while") == 0)
	{
		int lvl = currTable->level + 1;
		node->table = Id_Table_Init(lvl);

		node->table->next = currTable;
		currTable = node->table;

	} else if(strcmp(node->Line, "func") == 0)
	{
		char* name = node->Token->lexeme;

		struct listnode *Found_Node = hashtab_lookup(currTable->hashtab, name);

		if (Found_Node == NULL)
		{
			int value = hashtab_hash(name);

			hashtab_add(currTable->hashtab, name, value, 3, 0); 

			int lvl = currTable->level + 1;
			node->table = Id_Table_Init(lvl);

			node->table->next = currTable;
			currTable = node->table;
		}else{
			Redecl_Message(node);
		}
		//вызов
	}else if(strcmp(node->Line, "Function") == 0){
		char* name = node->Token->lexeme;
		struct listnode *Found_Node = Find_in_all_table(currTable, name);//hashtab_lookup(currTable->hashtab, name);

		if (Found_Node != NULL)
		{

			/*//int value = hashtab_hash(name);

			//hashtab_add(currTable->hashtab, name, value, 3, 0);
			//int lvl = currTable->level + 1;
			//node->table = Id_Table_Init(lvl);

			node->table->next = currTable;
			currTable = node->table;
			printf(" 2%s\n", name); */
			
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
	printf("ERROR: REDECLORTE\t");
	printf("%s\n", node->Token->lexeme);
}
void Not_Declar_Message(struct AST *node)
{
	Count_Error++;
	printf("%d:", node->Token->row);
	printf("%d:\t", node->Token->column);
	printf("ERROR: undeclared (first use in this function)\t ");
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
				printf("id = %s\t", hash_node->key);
				printf("Base Type = %d\t", hash_node->base_type);
				printf("Type = %d\t", hash_node->type);
				printf("offset = %d\n", hash_node->offset);
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
