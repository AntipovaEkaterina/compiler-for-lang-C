#include "Code_Gen.h"

void code_gen(struct AST *root)
{
	if ((asmb = fopen("main.asm", "w")) == NULL) 
	{
		printf ("!!!!I CANNOT OPEN FILE!!!!!\n");
		exit(1); 
	}
	for (int i = 0; i < 6; i++) {
		regValArg[i] = 0;
		regValAri[i] = 0;
	}

	fprintf(asmb, "section .text");
	fprintf(asmb, "\tglobal\tmain\n");

	treversal(root);

    fclose(asmb);
} 
void treversal(struct AST *node)
{
    struct Id_Table *table = currTable;
    if(node->table != NULL)
    {
        currTable = node->table;
    }
    if (strcmp(node->Line, "equally") == 0 ) 
    {
		struct ListChild *child1 = node->ListChildren;
		struct ListChild *child2 = child1->next;
        
        char *name = child1->Node->Token->lexeme;
        struct listnode *elemOfTab = Find_in_all_table(currTable, name);
        int offset = elemOfTab->offset;

        int sizeNumb = getSizeNumber(offset);

        char* str1 = (char*)calloc(7 + sizeNumb, sizeof(char));
        sprintf(str1, "[rbp-%d]", offset);

        char* str2 = rightPart(child2->Node);
        fprintf(asmb, "\tmov\t\t%s, %s\n", str1, "testReg");

		free(str1);
	}
	// else if (strcmp(node->Line, "if") == 0) {

	// } else if (strcmp(node->Line, "while") == 0) {

	// } else if (strcmp(node->Line, "func") == 0) {

	// }
    struct ListChild* Children = node->ListChildren;
	while (Children != NULL)
    {
		treversal(Children->Node);
		Children = Children->next;
	}
}
char* rightPart(struct AST *node)
{
	char *reg = NULL;
	if (strcmp(node->Line, "numeric") == 0) 
	{
		reg = regAriNumToStr(getRegForAri());
		Mov(reg, node->Token->lexeme);
		return reg;
	}else if(strcmp(node->Line, "id") == 0)
	///////////////////////////////////
	//////////////////////////////что у меня будет вместо id 
////////////////////////////////////
//////////////////////////////////
////////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
///////////////////////////////////////
	///////////////////////////////////
	{
		reg = regAriNumToStr(getRegForAri());

	//	char* offset = getOffset(node);

		// operMov(reg, "[rbp-" + offset + "]");
		return reg;
	}
	return reg;
}
int getRegForAri()
{
	for (int i = 1; i < 6; i++) 
	{
		if (regValAri[i] == 0) 
		{
			setRegForAri(i, 1);
			return i;
		}
	}
	return -1;
}
void setRegForAri(int numReg, int value)
{
	regValAri[numReg] = value;
}
char* regAriNumToStr(int numReg)
{
	char* reg = (char*) calloc(3, sizeof(char));
	switch(numReg)
	{
		case 0:
			strcpy(reg, "rax");
			break;
		case 1:
			strcpy(reg, "rdx");
			break;
		case 2:
			strcpy(reg, "rcx");
			break;
		case 3:
			strcpy(reg, "rsi");
			break;
		case 4:
			strcpy(reg, "r8");
			break;
		case 5:
			strcpy(reg, "r9");
			break;
		default:
			strcpy(reg, "000");
			break;
	}
	return reg;
}
int regAriStrToReg(char* strReg)
{
	int intReg = -1;

	if (strcmp(strReg, "rax") == 0) {
		intReg = 0;
	} else if (strcmp(strReg, "rdx") == 0) {
		intReg = 1;
	} else if (strcmp(strReg, "rcx") == 0) {
		intReg = 2;
	} else if (strcmp(strReg, "rsi") == 0) {
		intReg = 3;
	} else if (strcmp(strReg, "r8") == 0) {
		intReg = 4;
	} else if (strcmp(strReg, "r9") == 0) {
		intReg = 5;
	}
	return intReg;
}

// void printRegValAri()
// {
// 	for (int i = 0; i < 6; i++)
// 		cout << regAriNumToStr(i) + ": " + to_string(getValRegAri(i)) << endl;
//}
void freeRegValAri(char* strReg)
{
	setRegForAri(regAriStrToReg(strReg), 0);
}
int getValRegAri(int numReg)
{
	return regValAri[numReg];
}
int getSizeNumber(int num)
{
	int size = 1;
	int mult = 10;
	while (mult < num) 
	{
		mult *= 10;
		size++;
	}
	return size;
}
void Mov(char *str1, char *str2)
{
	fprintf(asmb, "\tmov\t\t%s, %s\n", str1, str2);
}

/*char* getOffset(struct AST *node)
{
	char* nodeLexem = node->Token->lexeme;
	// IdAttributes *idAttrib = currIdTable->searchAttrib(nodeLexem);
	struct listnode *hashtab = findInAllTable(currTable, nodeLexem);
	string offset = to_string(Id_Attrib->getOffset());
	int numOffset = Id_Attrib->getOffset();

	if (idAttrib->getType() == "arr") {
		AST *child = node->getFirstChild();

		string lexeme = child->getToken()->getLexeme();
		if (child->getToken()->getTokenName() == num_const) {
			int intdex = stoi(lexeme);
			int sizeData = idAttrib->getSize();

			numOffset -= intdex * sizeData;
			offset = to_string(numOffset);
		} else if (child->getToken()->getTokenName() == id) {
			IdAttributes *idAttribChlid = currIdTable->searchAttrib(lexeme);

			operMov("rax", to_string(idAttribChlid->getSize()));
			operImul("rax", "[rbp-" + getOffset(child) + "]");
			offset += "+rax";
		}
	}

	return offset;
} */