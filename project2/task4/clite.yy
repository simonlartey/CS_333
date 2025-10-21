/*
 * File Name:   clite.yy
 * Description: A Flex scanner for Clite that prints tokens.
 *              Extension: Normalizes float output to 6 decimal places.
 * Author:      Simon Lartey
 * Date:        10/2/2025
 *
 * How to Compile and Run:
 *   1. Generate the scanner with Flex:
 *        flex clite.yy
 *
 *   2. Compile the generated C file with gcc:
 *        gcc lex.yy.c -o clite_program
 *
 *   3. Run the program on a test input file:
 *        ./clite_program test.c
 *
 *   4. Save the tokens to an output file (overwrite mode):
 *        ./clite_program test.c > output.txt
 */

%{
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
%}

%option noyywrap

%%

    /* ignore preprocessor directives (#include, etc.) */
\#.*                        {}

    /* remove single-line comments */
"//".*                      {}

    /* remove multi-line comments */
"/*"([^*]|\n)*"*/"          {}

    /* remove whitespace */
[ \t\n]+                     {}

    /* remove semi-colon */
";"                          {}

    /* keywords */
if|else|while|for|int|float  { printf("Keyword-%s\n", yytext); }

    /* float (normalize to 6 decimal places) */
[0-9]+\.[0-9]+               {
                                double val = atof(yytext);
                                printf("Float-%f\n", val);
                             }

    /* integer */
0|[1-9][0-9]*                {
                                int val = atoi(yytext);
                                printf("Integer-%d\n", val);
                             }

    /* identifier */
[A-Za-z_][A-Za-z_0-9]*       { printf("Identifier-%s\n", yytext); }

    /* assignment */
"="                          { printf("Assignment\n"); }

    /* comparison (longest matches first) */
"<="|">="|"=="|"<"|">"       { printf("Comparison-%s\n", yytext); }

    /* operators */
"+"|"-"|"*"|"/"              { printf("Operator-%s\n", yytext); }

    /* brackets */
"{"                          { printf("Open-bracket\n"); }
"}"                          { printf("Close-bracket\n"); }

    /* parentheses */
"("                          { printf("Open-paren\n"); }
")"                          { printf("Close-paren\n"); }

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("fopen");
            return 1;
        }
    }
    yylex();
    return 0;
}
