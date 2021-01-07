%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *str);

int regs[26];   // symbol table
#define RegIndex(c) (c - 'a')
int base;       // current base of integer
%}

%union {
    char id;
    int  num;
}
%start list
%token <num> DIGIT
%token <id> LETTER
%type <num> number expr

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS  /*supplies precedence for unary minus */

%%

list    : /* empty */
        | list stat '\n'
        | list error '\n'               { yyerrok; }
        ;

stat    : expr                          { printf("%d\n", $1); }
        | LETTER '=' expr               { regs[RegIndex($1)] = $3; }
        ;

expr    : '(' expr ')'                  { $$ = $2; }
        | expr '*' expr                 { $$ = $1 * $3; }
        | expr '/' expr                 { $$ = $1 / $3; }
        | expr '%' expr                 { $$ = $1 % $3; }
        | expr '+' expr                 { $$ = $1 + $3; }
        | expr '-' expr                 { $$ = $1 - $3; }
        | expr '&' expr                 { $$ = $1 & $3; }
        | expr '|' expr                 { $$ = $1 | $3; }
        | '-' expr %prec UMINUS         { $$ = -$2; }
        | LETTER                        { $$ = regs[RegIndex($1)]; }
        | number
        ;

number  : DIGIT                         { base = ($1==0) ? 8 : 10; }
        | number DIGIT                  { $$ = base * $1 + $2; }
        ;

%%

int main(int argc, char *argv[])
{
    return yyparse();
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int yywrap()
{
    return 1;
}
