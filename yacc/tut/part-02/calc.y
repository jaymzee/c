%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern FILE *yyin;
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
            | PRINT expr                { printf("%d\n", $2); }
            | EXIT                      { YYACCEPT; }

assignment  : IDENTIFIER '=' expr       { SetSymbolVal($1, $3); }

expr        : term
            | expr '+' term             { $$ = $1 + $3; }
            | expr '-' term             { $$ = $1 - $3; }

term        : NUMBER
            | IDENTIFIER                { $$ = GetSymbolVal($1); }

%%

int main(int argc, char *argv[])
{
    int result;
    char *filename;

    if (argc > 1) {
        filename = argv[1];
        yyin = fopen(filename, "r");
        if (yyin) {
            result = yyparse();
            fclose(yyin);
        } else {
            perror(filename);
            result = EXIT_FAILURE;
        }
    } else {
        // parse stdin
        result = yyparse();
    }
    return result;
}

int SymbolIndex(char token)
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
    int bucket = SymbolIndex(symbol);
    return symbols[bucket];
}

/* updates the value of a given symbol */
void SetSymbolVal(char symbol, int val)
{
    int bucket = SymbolIndex(symbol);
    symbols[bucket] = val;
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
