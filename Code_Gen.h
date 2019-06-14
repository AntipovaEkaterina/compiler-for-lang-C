#include "Code_Gen.h"

void code_gen(struct AST *root)
{
	if ((asmb = fopen("main.c", "w")) == NULL) {
		printf ("Cannot open file.\n");
		exit(1); 
	}

	fprintf(asmb, "\nsection .text");
	fprintf(asmb, "\tglobal\tmain");

	fclose();
} 