all:
	gcc -Wall -g main.c lexer.c parser.c ListChildren.c AST.c ListTokens.c tabl.c semantics.c -o main

.PHONY: g 
g:
	dot -Tps graph.gv -o graph.ps

.PHONY: r
r: 
	./main test1.txt