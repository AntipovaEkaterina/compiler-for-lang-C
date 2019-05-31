all:
	gcc -Wall main.c lexer.c parser.c ListTokens.c -o main
