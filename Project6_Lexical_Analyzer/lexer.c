#include "lexer.h" // Include header file containing function declarations and required libraries

// Arrays to store grouped tokens for final printing
char keyword_list[500] = "";
char identifier_list[500] = "";
char constant_list[500] = "";
char operator_list[500] = "";
char delimiter_list[500] = "";
char string_list[500] = "";
char character_list[500] = "";
char preprocessor_list[500] = "";

// Main lexical analyzer function
void lexicalAnalyzer(FILE *fp)
{
    char ch; // Variable to read one character at a time from file

    // Read characters until end of file
    while ((ch = fgetc(fp)) != EOF)
    {
        // Check for identifiers and keywords
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_')
        {
            readWord(fp, ch);
        }

        // Check for numbers
        else if (ch >= '0' && ch <= '9')
        {
            readNumber(fp, ch);
        }

        // Check for operators
        else if (is_operator_char(ch))
        {
            readOperator(fp, ch);
        }

        // Check for delimiters
        else if (is_delimiter(ch))
        {
            readDelimiter(ch);
        }

        // Check for string literals
        else if (ch == '"')
        {
            readString(fp);
        }

        // Check for character literals
        else if (ch == '\'')
        {
            readCharacter(fp);
        }

        // Check for preprocessor directives
        else if (ch == '#')
        {
            readPreprocessor(fp);
        }
    }

    // Print final grouped output
    printf("\n");
    printf("%-20s%s\n", "Preprocessor : ", preprocessor_list);
    printf("%-20s%s\n", "Keyword : ", keyword_list);
    printf("%-20s%s\n", "Identifier : ", identifier_list);
    printf("%-20s%s\n", "Constant : ", constant_list);
    printf("%-20s%s\n", "Operator : ", operator_list);
    printf("%-20s%s\n", "Delimiter : ", delimiter_list);
    printf("%-20s%s\n", "String Literal : ", string_list);
    printf("%-20s%s\n", "Character Literal : ", character_list);
}

// Function to read identifiers and keywords
void readWord(FILE *fp,int ch)
{
    char buffer[100]; // Buffer to store token
    int i=0; // Index for buffer

    buffer[i++]=ch; // Store first character

    // Read remaining letters, digits, or underscore
    while((ch=fgetc(fp)) != EOF && (isalpha(ch) || isdigit(ch) || ch=='_'))
    {
        buffer[i++]=ch;
    }

    buffer[i]='\0'; // Terminate string

    // Put back extra character into input stream
    if(ch!=EOF)
    {
        ungetc(ch,fp);
    }

    // Check whether token is keyword
    if(is_keyword(buffer))
    {
        strcat(keyword_list, buffer);
        strcat(keyword_list, ", ");
    }
    else
    {
        strcat(identifier_list, buffer);
        strcat(identifier_list, ", ");
    }
}

// Function to check whether a word is a C keyword
int is_keyword(char *word)
{
    char *keyword[] =
        {
            "int", "float", "char", "double","short", "long", "signed", "unsigned",
            "void", "if", "else", "switch","case", "default", "for", "while",
            "do", "break", "continue", "return","goto", "struct", "union", "typedef",
            "enum", "const", "static", "sizeof"
        };

    // Compare input word with every keyword
    for(int i=0;i<sizeof(keyword)/sizeof(keyword[0]);i++)
    {
        if(strcmp(keyword[i],word)==0)
        {
            return 1; // Keyword found
        }
    }

    return 0; // Not a keyword
}

// Function to read integer constants
void readNumber(FILE *fp,int ch)
{
    char buffer[100]; // Buffer to store number
    int i=0;

    buffer[i++]=ch; // Store first digit

    // Read remaining digits
    while((ch=fgetc(fp))!=EOF && isdigit(ch))
    {
        buffer[i++]=ch;
    }

    buffer[i]='\0'; // Terminate string

    // Return extra character to stream
    if(ch!=EOF)
    {
        ungetc(ch,fp);
    }

    // Store constant in list
    strcat(constant_list, buffer);
    strcat(constant_list, ", ");
}

// Function to read operators
void readOperator(FILE *fp, int ch)
{
    char buffer[100]; // Buffer to store operator
    int i = 0;

    buffer[i++] = ch; // Store first operator character

    ch = fgetc(fp); // Read next character

    if (ch != EOF)
    {
        buffer[i++] = ch; // Store second character
        buffer[i] = '\0';

        // If two-character operator is invalid
        if (!is_operator(buffer))
        {
            i--; // Remove second character
            buffer[i] = '\0';
            ungetc(ch, fp); // Return character to stream
        }
        else
        {
            // Check for <<= and >>=
            if (strcmp(buffer, ">>") == 0 || strcmp(buffer, "<<") == 0)
            {
                ch = fgetc(fp);

                if (ch == '=')
                {
                    buffer[i++] = ch;
                    buffer[i] = '\0';
                }
                else if (ch != EOF)
                {
                    ungetc(ch, fp);
                }
            }
        }
    }

    // Store operator in list
    strcat(operator_list, buffer);
    strcat(operator_list, ", ");
}

// Function to check valid operators
int is_operator(char *word)
{
    char *operator[] =
        {
            "+", "-", "*", "/", "%", "=","++", "--", "+=", "-=", "*=", "/=", "%=",
            "==", "!=", "<", ">", "<=", ">=","&&", "||", "&", "|", "^", "~",
            "<<", ">>", "<<=", ">>=","!", "->","&=","|=","^="
        };

    // Compare with every valid operator
    for (int i = 0; i < sizeof(operator) / sizeof(operator[0]); i++)
    {
        if (strcmp(operator[i], word) == 0)
        {
            return 1;
        }
    }

    return 0;
}

// Function to process delimiters
void readDelimiter(int ch)
{
    if(is_delimiter(ch))
    {
        char temp[2];

        temp[0] = ch; // Store delimiter character
        temp[1] = '\0';

        strcat(delimiter_list, temp);
        strcat(delimiter_list, " ");
    }
}

// Function to check delimiters
int is_delimiter(char ch)
{
    char delimiter[] = { ';', ',', '(', ')', '{', '}', '[', ']' };

    for(int i=0;i<sizeof(delimiter)/sizeof(delimiter[i]);i++)
    {
        if(delimiter[i] == ch)
        {
            return 1;
        }
    }

    return 0;
}

// Function to check whether a character can start an operator
int is_operator_char(char ch)
{
    char operator[] = { '+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~' };

    for(int i = 0; i < sizeof(operator) / sizeof(operator[0]); i++)
    {
        if(operator[i] == ch)
        {
            return 1;
        }
    }

    return 0;
}

// Function to read string literals
void readString(FILE *fp)
{
    char buffer[100];
    char ch;
    int i=0;

    // Read characters until closing double quote
    while((ch=fgetc(fp)) !=EOF  && ch != '"' )
    {
        buffer[i++]=ch;
    }

    buffer[i]='\0';

    // Store string literal
    strcat(string_list, buffer);
}

// Function to read character literals
void readCharacter(FILE *fp)
{
    char buffer[10];
    char ch;
    int i = 0;

    // Read characters until closing single quote
    while((ch = fgetc(fp)) != EOF && ch != '\'')
    {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    // Store character literal with quotes
    strcat(character_list, "'");
    strcat(character_list, buffer);
    strcat(character_list, "'");
}

// Function to read preprocessor directives
void readPreprocessor(FILE *fp)
{
    char buffer[100];
    char ch;
    int i = 0;

    buffer[i++] = '#'; // Store # symbol

    // Read characters until newline
    while((ch = fgetc(fp)) != EOF && ch != '\n')
    {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    // Store preprocessor directive
    strcat(preprocessor_list, buffer);
}