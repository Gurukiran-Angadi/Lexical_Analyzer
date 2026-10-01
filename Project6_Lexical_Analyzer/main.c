#include "lexer.h" // Include header file containing function declarations

int main()
{
    FILE *fp = fopen("Sample.c", "r"); // Open Sample.c in read mode

    if(fp == NULL) // Check whether file opened successfully
    {
        perror("Unable to open the file"); // Print error message
        return 1; // Exit program with error status
    }

    lexicalAnalyzer(fp); // Call lexical analyzer function

    fclose(fp); // Close the file

    return 0; 
}
// Compilation command : "gcc main.c lexer.c -o lexer"
// ./lexer