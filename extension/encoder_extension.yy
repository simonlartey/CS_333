/*
 * File Name:   encode_ext.yy
 * Description: A Flex program that performs a progressive Caesar cipher:
 *              - Each alphabetic character is shifted forward by an amount
 *                equal to its position in the input text (1st char +1, 2nd +2, etc.).
 *              - Wraps around 'z'/'Z' to stay in the alphabet.
 * Author:      Simon Lartey
 * Date:        10/3/2025
 * How to Compile and Run:
 *   1. flex encoder.yy
 *   2. gcc lex.yy.c -o encoder_program
 *   3. ./encoder_program input.txt > output.txt
 */

%{
#include <stdio.h>
#include <ctype.h>
extern FILE *yyin;

int position = 0;   // keeps track of character position
%}

%option noyywrap

%%

[A-Z] {
    position++;
    int shift = position % 26;
    char c = ((yytext[0] - 'A' + shift) % 26) + 'A';
    printf("%c", c);
}

[a-z] {
    position++;
    int shift = position % 26;
    char c = ((yytext[0] - 'a' + shift) % 26) + 'a';
    printf("%c", c);
}

.|\n {
    // Non-alphabetic characters → print as is
    printf("%s", yytext);
    if (*yytext != '\n' && *yytext != ' ')
        position++;  // count towards shifting positions too
}

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
