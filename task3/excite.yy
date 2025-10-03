/*
 * File Name:   excite.yy
 * Description: A Flex program that:
 *              - Replaces "cat" with "lion" and "cats" with "lions"
 *              - Replaces numbers 0–10 with their English word equivalents
 * Author:      Simon Lartey
 * Date:        10/2/2025
 * How to Compile and Run:
 *   1. Generate the scanner with Flex:
 *        flex excite.yy
 *
 *   2. Compile the generated C file with gcc:
 *        gcc lex.yy.c -o excite_program
 *
 *   3. Run the program on an input file:
 *        ./excite_program test.txt
 *
 *   4. Save the output into a file (overwrite mode):
 *        ./excite_program test.txt > output.txt

 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;

// Lookup table for numbers 0–10
const char *words[] = {
    "zero","one","two","three","four",
    "five","six","seven","eight","nine","ten"
};

void replace_number(const char *text) {
    int n = atoi(text);
    if (n >= 0 && n <= 10) {
        printf("%s", words[n]);
    } else {
        printf("%s", text);
    }
}
%}

%option noyywrap case-insensitive

DIGIT   [0-9]

%%

cats            { printf("lions"); }
cat             { printf("lion"); }

10              { replace_number(yytext); }
{DIGIT}         { replace_number(yytext); }

.|\n            { printf("%s", yytext); }

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
