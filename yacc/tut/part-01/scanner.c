#include <stdio.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char *yytext;

char *names[] = {
    "db_type",
    "db_name",
    "db_table_prefix",
    "db_port",
    "identifier",
    "integer"
};

void PrintToken(int token, FILE *stream)
{
    if (token > 32 && token < 127) {
        // token is actually a printable character
        fprintf(stream, "'%c'", token);
    } else if (token >= 256 && token < IDENTIFIER) {
        // token represents a keyword
        fprintf(stream, "'%s'", names[token - 256]);
    } else if (token >= IDENTIFIER && token <= INTEGER) {
        // token represents a type
        fprintf(stream, "%s", names[token - 256]);
    } else {
        // just print the token value
        fprintf(stream, "%d", token);
    }
}

void Expected(int expected_token)
{
    printf("Syntax error in line %d, expected ", yylineno);
    PrintToken(expected_token, stdout);
    printf(" but found '%s'\n", yytext);
}

int main()
{
    int ntoken, vtoken;

    ntoken = yylex();
    while (ntoken) {
        if (yylex() != ':') {
            Expected(':');
            return 1;
        }
        vtoken = yylex();
        switch (ntoken) {
        case TYPE:
        case NAME:
        case TABLE_PREFIX:
            if (vtoken != IDENTIFIER) {
                Expected(IDENTIFIER);
                return 1;
            }
            PrintToken(ntoken, stdout);
            printf(" is set to '%s'\n", yytext);
            break;
        case PORT:
            if (vtoken != INTEGER) {
                Expected(INTEGER);
                return 1;
            }
            PrintToken(ntoken, stdout);
            printf(" is set to %s\n", yytext);
            break;
        default:
            printf("Syntax error in line %d\n", yylineno);
        }
        ntoken = yylex();
    }
    return 0;
}
