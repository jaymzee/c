%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

" "         ;
[a-z]       {
                yylval.id = yytext[0];
                return LETTER;
            }
[0-9]       {
                yylval.num = yytext[0] - '0';
                return DIGIT;
            }
[^a-z0-9\b] {
                return yytext[0];
            }
