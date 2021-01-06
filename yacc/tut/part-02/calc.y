%{
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <ctype.h>

void yyerror (char *s);
int yylex();

int symbols[52];
int SymbolVal(char symbol);
void UpdateSymbolVal(char symbol, int val);
%}

%union {
    int num;
    char id;
}
%token PRINT EXIT
%token <num> NUMBER
%token <id> IDENTIFIER
%type <num> line expr term
%type <id> assignment
%start line

%%

/* descriptions of expected inputs     corresponding actions (in C) */

line        : assignment ';'            {;}
            | line assignment ';'       {;}
            | PRINT expr ';'            { printf("Printing %d\n", $2); }
            | line PRINT expr ';'       { printf("Printing %d\n", $3); }
            | line EXIT ';'             { exit(EXIT_SUCCESS); }
            | EXIT ';'                  { exit(EXIT_SUCCESS); }
            ;

assignment  : IDENTIFIER '=' expr       { UpdateSymbolVal($1, $3); }
            ;

expr        : term                      { $$ = $1; }
            | expr '+' term             { $$ = $1 + $3; }
            | expr '-' term             { $$ = $1 - $3; }
            ;

term        : NUMBER                    { $$ = $1; }
            | IDENTIFIER                { $$ = SymbolVal($1); }
            ;

%%                     /* C code */

int ComputeSymbolIndex(char token)
{
    int idx = -1;
    if (islower(token)) {
        idx = token - 'a' + 26;
    } else if(isupper(token)) {
        idx = token - 'A';
    }
    return idx;
}

/* returns the value of a given symbol */
int SymbolVal(char symbol)
{
    int bucket = ComputeSymbolIndex(symbol);
    return symbols[bucket];
}

/* updates the value of a given symbol */
void UpdateSymbolVal(char symbol, int val)
{
    int bucket = ComputeSymbolIndex(symbol);
    symbols[bucket] = val;
}

int main(void) {
    /* init symbol table */
    int i;
    for(i=0; i<52; i++) {
        symbols[i] = 0;
    }
    return yyparse();
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
