%{
#include "y.tab.h"

void yyerror(char *s);
int yylex();
%}

%%

print               return PRINT;
exit                return EXIT;
[a-zA-Z]            {
                        yylval.id = yytext[0];
                        return IDENTIFIER;
                    }
[0-9]+              {
                        yylval.num = atoi(yytext);
                        return NUMBER;
                    }
[ \t\n]             ;
[-+=;]              return yytext[0];
.                   {
                        ECHO;
                        yyerror ("unexpected character");
                    }

%%

int yywrap(void)
{
    return 1;
}
