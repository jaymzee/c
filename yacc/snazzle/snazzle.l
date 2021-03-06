%{
#include <iostream>
%}
%%
[ \t]+ { std::cout << "Found whitespace" << std::endl; }
[0-9]+\.[0-9]+ { std::cout << "Found a floating-point number:" << yytext << std::endl; }
[0-9]+  { std::cout << "Found an integer:" << yytext << std::endl; }
[a-zA-Z_][a-zA-Z0-9_]* { std::cout << "Found an identifier: " << yytext << std::endl; }
%%
main() {
    // lex through the input:
    yylex();
}
