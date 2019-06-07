all:
	gcc -Wall main.c lexer.c parser.c ListChildren.c AST.c ListTokens.c -o main

.PHONY: graph
graph:
	dot -Tps graph.gv -o graph.ps


