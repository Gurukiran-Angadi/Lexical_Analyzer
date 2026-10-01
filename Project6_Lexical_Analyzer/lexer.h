#ifndef LEXICAL_H          // Check whether LEXICAL_H is already defined
#define LEXICAL_H          // Define LEXICAL_H to avoid multiple inclusion

#include <stdio.h>         // For FILE, fopen, fgetc, printf, EOF
#include <string.h>        // For strcmp, strcat and other string functions
#include <ctype.h>         // For isalpha, isdigit and character checking functions

void lexicalAnalyzer(FILE *fp);        // Main lexical analyzer function
void readWord(FILE *fp,int ch);        // Read identifiers and keywords
int is_keyword(char *word);            // Check whether a word is a keyword
void readOperator(FILE *fp,int ch);    // Read operators
int is_operator(char *word);           // Check whether a string is a valid operator
void readNumber(FILE *fp,int ch);      // Read numeric constants
void readDelimiter(int ch);            // Process delimiters
int is_delimiter(char ch);             // Check whether a character is a delimiter
int is_operator_char(char ch);         // Check whether a character can start an operator
void readString(FILE *fp);             // Read string literals
void readCharacter(FILE *fp);          // Read character literals
void readPreprocessor(FILE *fp);       // Read preprocessor directives

#endif                                 // End of header file