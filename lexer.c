#include "lexer.h"

char *DefineToken(char *lexeme) {
    if(strcmp(lexeme, "int") == 0)
        return "int";
    if(strcmp(lexeme, "char") == 0)
        return "char";
    if(strcmp(lexeme, "void") == 0)
        return "void";
    if(strcmp(lexeme, "scanf") == 0)
        return "scanf";
    if(strcmp(lexeme, "printf") == 0)
        return "printf";
    if(strcmp(lexeme, "{") == 0)
        return "l_brace";
    if(strcmp(lexeme, "}") == 0)
        return "r_brace";
    if(strcmp(lexeme, "(") == 0)
        return "l_paren";
    if(strcmp(lexeme, ")") == 0)
        return "r_paren";
    if(strcmp(lexeme, "[") == 0)
        return "l_square";
    if(strcmp(lexeme, "]") == 0)
        return "r_square";
    if(strcmp(lexeme, ",") == 0)
        return "comma";
    if(strcmp(lexeme, ";") == 0)
        return "semicolon";
    if(strcmp(lexeme, "if") == 0)
        return "if";
    if(strcmp(lexeme, "else") == 0)
        return "else";
    if(strcmp(lexeme, "while") == 0)
        return "while";
    if(strcmp(lexeme, "+") == 0)
        return "plus";
    if(strcmp(lexeme, "-") == 0)
        return "minus";
    if(strcmp(lexeme, "=") == 0)
        return "equally";
    if(strcmp(lexeme, "\\" ) == 0)
        return "slash";
    if(strcmp(lexeme, "%") == 0)
        return "percent";
    if(strcmp(lexeme, "*") == 0)
        return "star";
	if(strcmp(lexeme, "/") == 0)
        return "division";
    if(strcmp(lexeme, "||") == 0)
      return "or";
    if(strcmp(lexeme, "&&") == 0)
        return "and";
    if(strcmp(lexeme, "<") == 0)
        return "less";
    if(strcmp(lexeme, ">") == 0)
        return "more";
    if(strcmp(lexeme, "==") == 0)
        return "d_equally";
    if(strcmp(lexeme, "<=") == 0)
        return "l_eq";
    if(strcmp(lexeme, ">=") == 0)
        return "m_eq";
    if(strcmp(lexeme, "!=") == 0)
        return "not_equal";
    if(strcmp(lexeme, "return") == 0)
       return "return";
	if(lexeme[0] == '"') {
		if (lexeme[strlen(lexeme)-1] == '"')
			return "literal";
		else
			return "unknown";
	}

	if (lexeme[0] > '0' && lexeme[0] <= '9') {
		for (int i = 1; i < strlen(lexeme); i++) {
			if (!(lexeme[i] >= '0' && lexeme[i] <= '9'))
				return "unknown";	
		} 
		return "numeric";
	}

	if ((lexeme[0] >= 'A' && lexeme[0] <= 'Z') ||
		(lexeme[0] >= 'a' && lexeme[0] <= 'z') || (lexeme[0] == '_')) {
	
		for (int i = 1; i < strlen(lexeme); i++) {
			if (!((lexeme[i] >= 'A' && lexeme[i] <= 'Z') ||
				(lexeme[i] >= 'a' && lexeme[i] <= 'z') || (lexeme[i] == '_') ||
				(lexeme[i] >= '0' && lexeme[i] <= '9')))
				return "unknown";
		}
		return "id";
	}
	return "unknown";
}

ListTokens* IdentifyTokens(int argc, char const *argv) {
	char buf[100];
	if (argc > 1) {
		FILE *file;

		file = fopen (argv, "r");

		if (file == NULL) {
			printf("error\n");
			return NULL;
		}

		ListTokens *List = init();
		ListTokens *head = List;

		char sym;
		int i = 0;
		int row = 1, column = 1;
		char *token = (char *) malloc(sizeof(char) * 80);

		while ((sym = fgetc(file)) != EOF) {
			if (sym == '"') {
				buf[i] = sym;
				i++;
				column++;
				while ((sym = fgetc(file)) != '"' && sym != '\n') {
					buf[i] = sym;
					i++;
					column++;
				}
				if (sym == '"') {
					buf[i] = sym;
					i++;
					column++;
				}
				buf[i] = '\0';

				token = DefineToken(buf);
				List = addlexeme(List, token, buf, row, column-i);

				i = 0;
				continue;
			}
			//пробелы
			else if (sym == ' ') {
				if (i == 0) {
					column++;
					continue;
				}

				buf[i] = '\0';
			
				token = DefineToken(buf);
				List = addlexeme(List, token, buf, row, column-i);

				i = 0;
				column++;
				continue;

			} 
	
			else if (sym == '\n') {
				/*if (i == 0){
					column++;
					continue;
				}*/
				buf[i] = '\0';
				
				token = DefineToken(buf);
				List = addlexeme(List, token, buf, row, column-i);

				column = 1;
				row++;
				i = 0;
				continue;
			}
			 else if (sym == '/') {
				char tmp = fgetc(file);
				if (tmp == '/') {
					// sym = fgetc(file);
					while (sym != '\n' && sym != '\0' && sym != EOF) {
						sym = fgetc(file);
					}
					i = 0;
					row++;
					column = 1;
					continue;
				} else {
					ungetc(tmp, file);
				}
			}
			else if (sym == ',' || sym == ';' || sym ==  '+' || sym == '-'|| 								sym == '*' || sym == '%' || sym ==  '(' || sym == ')'|| 
					sym == '[' || sym == ']' || sym == '{' || sym == '}' ) {
				
				if (i != 0) {
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;
				}

				buf[i] = sym;
				i++;
				column++;
				buf[i] = '\0';

				token = DefineToken(buf);
				List = addlexeme(List, token, buf, row, column-i);

				i = 0;
				continue;
			}

			else if (sym == '>') {
				if (i != 0) {
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;
				}

				buf[i] = sym;
				i++;
				column++;

				if ((sym = fgetc(file)) == '=') {
					buf[i] = sym;
					i++;
					column++;
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;
					continue;
				} else {
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;

					if (sym == ' ') {
						column++;
						continue;
					}
				}
			}

			else if (sym == '<') {
				if (i != 0) {
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;
				}
				buf[i] = sym;
				i++;
				column++;

				sym = fgetc(file);

				if ((sym == '=')) {
					buf[i] = sym;
					i++;
					column++;
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;
					continue;
				} else {
					buf[i] = '\0';

					token = DefineToken(buf);
					List = addlexeme(List, token, buf, row, column-i);

					i = 0;

					if (sym == ' ') {
						column++;
						continue;
					}
				}
			}

			buf[i] = sym;
			i++;
			column++;
		}
		if (i != 0) {
			buf[i] = '\0';

			token = DefineToken(buf);
			List = addlexeme(List, token, buf, row, column-i);

			i = 0;
		}
		List = addlexeme(List, "end", "", row, column-i);
		fclose (file);
		return head;
	}
	return NULL;
}