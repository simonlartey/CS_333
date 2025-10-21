/*
 * File Name:   vowelcount.yy
 * Description: A Flex program that reads a text file and reports:
 *              - total number of rows (lines)
 *              - total number of characters
 *              - number of occurrences of each vowel [a, e, i, o, u],
 *                counted case-insensitively.
 * Author:      Simon Lartey
 * How to Run:
 *   1. Change into the task2 directory:
 *        cd task2
 *   2. Generate the scanner:
 *        flex vowelcount.yy
 *
 *   3. Compile the generated C file:
 *        gcc lex.yy.c -o vowelcount_program
 *
 *   4. Run the program on a file:
 *        ./vowelcount_program input_test.txt
 *
 *   5. The program prints the number of rows, characters, and
 *      individual counts of each vowel directly to the terminal.
 *
 *   6. Verify correctness:
 *        Compare the program’s reported counts with manual inspection
 *        of the input file to ensure accuracy.
 *
 * Date: 10/1/2025
 */



%{
#include <stdio.h>
extern FILE *yyin;

int num_rows = 0;
int num_chars = 0;
int num_a = 0, num_e = 0, num_i = 0, num_o = 0, num_u = 0;
%}

%option noyywrap

%%
[aA]    { num_a++; num_chars++; }
[eE]    { num_e++; num_chars++; }
[iI]    { num_i++; num_chars++; }
[oO]    { num_o++; num_chars++; }
[uU]    { num_u++; num_chars++; }
\n      { num_rows++; num_chars++; }
.       { num_chars++; }
%%

int main(int argc, char * argv[]){
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("fopen");
            return 1;
        }
    }
    yylex();
    // If file not empty and last line didn’t end with newline
    if (num_chars > 0 && (num_rows == 0 || (num_rows > 0 && yyin != NULL))) {
        num_rows++;
    }

    printf("Number of Rows: %d\n", num_rows);
    printf("Number of Characters: %d\n", num_chars);
    printf("Number of A/a: %d\n", num_a);
    printf("Number of E/e: %d\n", num_e);
    printf("Number of I/i: %d\n", num_i);
    printf("Number of O/o: %d\n", num_o);
    printf("Number of U/u: %d\n", num_u);

    return 0;
}
