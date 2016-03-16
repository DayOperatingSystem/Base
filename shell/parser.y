%{
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C" int yylex();
extern "C" int yyparse();
extern FILE *yyin;
extern char *yytext;
 
void yyerror(const char *s);
void handle_command(char* cmd, std::vector<char*>* args);

%}

%union {
	char* sval;
	std::vector<char*>* args;
}

// Task 1 - Define your tokens here

%token <sval> STRING;
//%token <ival> INTEGER;

//%token DIFFERENCE;

// Task 2 - define your non-terminal types here
//%type <exprval> expr
%type <args> arglist

%%

parser: | expr;

expr: STRING { handle_command($1, NULL); }
     // | STRING arglist { handle_command($1, $2); }

//arglist: STRING { std::vector<char*>* vec = new std::vector<char*>(); vec->push_back(strdup($1)); $$ = vec; }
	//| arglist STRING { $1->push_back(strdup($2)); $$ = $1; }

%%

#define LEXER_IMPLEMENTED

int parse(FILE *fp)
{
	yyin = fp;

	do {
#ifdef LEXER_IMPLEMENTED
		std::cout << "DayOS > ";
		yyparse();
#else
		int x;
		std::cout << "Resulting tokens: ";
		while (x = yylex())
		{
			std::cout << "<" << yytext << "> ";
		}
		std::cout << std::endl;
#endif

	} while(!feof(yyin));
#ifndef LEXER_IMPLEMENTED
	std::exit(EXIT_SUCCESS);
#endif

	return 0;
}

void yyerror(const char *s)
{
	std::cout << "Parser error: Message: " << s << std::endl;
	std::exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	std::cout << "DayOS Shell v0.2" << std::endl;
	return parse(stdin);
}

