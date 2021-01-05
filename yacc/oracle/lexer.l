%{
#include "y.tab.h"
extern int yylval;
%}

%%

while   return WHILE;
if      return IF;
package return PACKAGE;
reverse return REVERSE;
loop    return LOOP;
[a-zA-Z][a-zA-Z0-9]*  {
        //tokval = put_in_tabl();
        return IDENTIFIER;
    }
[0-9]+ {
        yylval = atoi(yytext);
        return INTEGER;
    }
\+  {
        yylval = PLUS;
        return ARITHOP;
    }
\-  {
        yylval = MINUS;
        return ARITHOP;
    }
>   {
        yylval = GREATER;
        return RELOP;
    }
>=  {
        yylval = GREATEREQL;
        return RELOP;
    }
