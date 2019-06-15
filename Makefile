all:
	gcc -Wall -g main.c lexer.c parser.c ListChildren.c AST.c ListTokens.c tabl.c semantics.c Code_Gen.c -o main

.PHONY: g 
g:
	dot -Tps graph.gv -o graph.ps

.PHONY: r
r: 
	./main test1.txt
	
.PHONY: asm
asm:
	nasm -felf64 main.asm -o mainq.o	
	gcc -no-pie mainq.o -o mainq