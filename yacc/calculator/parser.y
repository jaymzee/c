%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *str);

int regs[26];
int base;
%}

%start list
%token DIGIT LETTER
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS  /*supplies precedence for unary minus */

%%      /* beginning of rules section */

list:   /* empty */ |
        list stat '\n' |
        list error '\n' { yyerrok; } ;

stat:   expr { printf("%d\n",$1); } |
        LETTER '=' expr { regs[$1] = $3; } ;

expr:   '(' expr ')'  { $$ = $2; } |
        expr '*' expr { $$ = $1 * $3; } |
        expr '/' expr { $$ = $1 / $3; } |
        expr '%' expr { $$ = $1 % $3; } |
        expr '+' expr { $$ = $1 + $3; } |
        expr '-' expr { $$ = $1 - $3; } |
        expr '&' expr { $$ = $1 & $3; } |
        expr '|' expr { $$ = $1 | $3; } |
        '-' expr %prec UMINUS { $$ = -$2; } |
        LETTER { $$ = regs[$1]; } |
        number ;

number: DIGIT { $$ = $1; base = ($1==0) ? 8 : 10; } |
        number DIGIT { $$ = base * $1 + $2; } ;

%%

int main(int argc, char *argv[])
{
    return(yyparse());
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int yywrap()
{
    return(1);
}
