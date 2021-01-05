%{
#include <stdio.h>
void yyerror(const char *s);
int yylex(void);

int tokval;

%}

%start expr
%token IDENTIFIER INTEGER ARITHOP PLUS MINUS RELOP GREATER GREATEREQL WHILE IF PACKAGE REVERSE LOOP LBRACE RBRACE

%%

expr:   IDENTIFIER RELOP INTEGER { $$ = $3; printf("got integer %d %d\n", $3, $2); } ;

%%

int main(int argc, char *argv[])
{
    return yyparse();
}

void yyerror(const char *str)
{
    fprintf(stderr, "%s\n", str);
}
