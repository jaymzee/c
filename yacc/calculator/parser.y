%{
#include <stdio.h>

#define RegIndex(c) (c - 'a')
int yylex(void);
void yyerror(const char *str);

long lpow(long base, int exp);
long regs[26];  // register file
int radix;       // radix of current number being parsed
%}

%union {
    char    id;
    long    num;
}
%start list
%token <num> DIGIT
%token <id> LETTER
%type <num> number expr

%right POW          /* exponentiation operator */
%left '|'           /* bitwise or */
%left '^'           /* bitwise xor */
%left '&'           /* bitwise and */
%left '+' '-'       /* addition and subtraction */
%left '*' '/' '%'   /* multiply divide mod */
%left UMINUS        /* supplies precedence for unary minus */

%%

list    : /* empty */
        | list stat '\n'
        | list error '\n'               { yyerrok; }
        ;

stat    : expr                          { printf("%ld\n", $1); }
        | '$' expr                      { printf("0%lo\n", $2); }
        | LETTER '=' expr               { regs[RegIndex($1)] = $3; }
        ;

expr    : '(' expr ')'                  { $$ = $2; }
        | expr POW expr                 { $$ = lpow($1, $3); }
        | expr '*' expr                 { $$ = $1 * $3; }
        | expr '/' expr                 { $$ = $1 / $3; }
        | expr '%' expr                 { $$ = $1 % $3; }
        | expr '+' expr                 { $$ = $1 + $3; }
        | expr '-' expr                 { $$ = $1 - $3; }
        | expr '&' expr                 { $$ = $1 & $3; }
        | expr '|' expr                 { $$ = $1 | $3; }
        | expr '^' expr                 { $$ = $1 ^ $3; }
        | '-' expr %prec UMINUS         { $$ = -$2; }
        | LETTER                        { $$ = regs[RegIndex($1)]; }
        | number
        ;

number  : DIGIT                         { radix = ($1==0) ? 8 : 10; }
        | number DIGIT                  { $$ = radix * $1 + $2; }
        ;

%%

int main()
{
    return yyparse();
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int yywrap(void)
{
    return 1;
}

long lpow(long base, int exp)
{
    long result = 1;
    if (exp < 0) {
        return 0;       // prevent hang on negative exponenent
    }
    while (1) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}
