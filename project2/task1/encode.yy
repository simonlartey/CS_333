/*
 * File Name:   encode.yy
 * Description: A Flex program that shifts each
 *              alphabetic character in the input by 13 positions in the alphabet,
 *              wrapping around from 'z' to 'a' and from 'Z' to 'A'. Non-alphabetic
 *              characters are left unchanged.
 * Author:      Simon Lartey
 * How to Run:
 *   1. Change into the task1 directory:
 *        cd task2
 *   2. Generate the scanner:
 *        flex encode.yy
 *
 *   3. Compile the generated C file:
 *        gcc lex.yy.c -o encode_program
 *
 *   4. Encode a file:
 *        ./encode_program input_test.txt > output_encoded.txt
 *
 *   5. Decode back (run again on encoded file):
 *        ./encode_program output_encoded.txt > output_decoded.txt
 *   Date : 10/1/2025
 */



%{
#include <stdio.h>
extern FILE *yyin;
%}

%option noyywrap

%%
[A-Z]   { printf("%c", 'A' + ((*yytext - 'A' + 13) % 26)); }
[a-z]   { printf("%c", 'a' + ((*yytext - 'a' + 13) % 26)); }
.       { printf("%s", yytext); }
\n      { printf("\n"); }
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
