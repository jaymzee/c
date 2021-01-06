%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void yyerror(char *s);
int yylex();

int symbols[52];
int GetSymbolVal(char symbol);
void SetSymbolVal(char symbol, int val);
%}

%union {
    int num;
    char id;
}
%token PRINT EXIT
%token <num> NUMBER
%token <id> IDENTIFIER
%type <num> expr term
%start statements

%%

statements  : /* empty */
            | statements statement ';'

statement   : assignment
            | PRINT expr                { printf("Printing %d\n", $2); }
            | EXIT                      { exit(EXIT_SUCCESS); }

assignment  : IDENTIFIER '=' expr       { SetSymbolVal($1, $3); }

expr        : term
            | expr '+' term             { $$ = $1 + $3; }
            | expr '-' term             { $$ = $1 - $3; }

term        : NUMBER
            | IDENTIFIER                { $$ = GetSymbolVal($1); }

%%

int ComputeSymbolIndex(char token)
{
    int idx = 0;
    if (islower(token)) {
        idx = token - 'a' + 26;
    } else if (isupper(token)) {
        idx = token - 'A';
    }
    return idx;
}

/* returns the value of a given symbol */
int GetSymbolVal(char symbol)
{
    int bucket = ComputeSymbolIndex(symbol);
    return symbols[bucket];
}

/* updates the value of a given symbol */
void SetSymbolVal(char symbol, int val)
{
    int bucket = ComputeSymbolIndex(symbol);
    symbols[bucket] = val;
}

int main(void) {
    /* init symbol table */
    for (int i = 0; i < 52; i++) {
        symbols[i] = 0;
    }
    return yyparse();
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
