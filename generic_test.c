#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashmap.c"

typedef enum {
    INT,
    STR,
    FLOAT
}TYPE;

typedef struct {
    TYPE type;
    union {
        char *str_buffer;
        int integer_value;
        float float_value;
    }value;
}Generic;

Generic *createGeneric(TYPE type) {
    Generic *generic = (Generic *)malloc(sizeof(Generic));
    generic->type = type;
    if (generic->type == STR)
    {
        generic->value.str_buffer = malloc(sizeof(char));
    }
    return generic;
}

const char *typeOf(Generic *generic) {
    switch (generic->type) {
        case INT:
            return "INT";
        case STR:
            return "STR";
        case FLOAT:
            return "FLOAT";
        default:
            return "UNKNOWN";
    }
}

void split_line(char const *line, char const delimiter[], char ***tokenMatrix, int matrixRowIndex){
    // Using strtok to split the string
    char *copy_of_line = strdup(line);
    char **tokens = (char **)malloc(sizeof(char *));
    int i = 0;

    // Iterate through the tokens
    char *token = strtok(copy_of_line, delimiter);
    while (token != NULL) {
        printf("Token: %s\n", token);
        tokens = (char **)realloc(tokens, (i + 1) * sizeof(char *));
        tokens[i] = strdup(token);
        // Get the next token
        token = strtok(NULL, delimiter);
        i++;
    }

    tokenMatrix[matrixRowIndex] = tokens;
    free(copy_of_line);
}

FILE *openFile(int argc, char const *argv[], char *mode) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return NULL;
    }
    
    FILE *file = fopen(argv[1], mode);

    if (file == NULL)
    {
        perror("File doesn't exist\n");
    }
    
    return file;
}

void readFile(FILE *file) {
        // Allocate initial memory for the line buffer
    size_t buffer_size = 5000;
    int rowIndex = 0, no_of_rows = 5000;
    char *new_line = (char *)malloc(buffer_size);
    char ***tokenMatrix = (char ***)malloc(no_of_rows * sizeof(char **));
    
    Node *head_node;

    // Check if memory allocation is successful
    if (new_line == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return ; // Return a non-zero value to indicate an error
    }

    // Read and process the contents of the file line by line
    while (fgets(new_line, buffer_size, file) != NULL) {
        // Print or process the entire line
        printf("Line: %s\n", new_line);
        split_line(new_line, "=()\n", tokenMatrix, rowIndex);
        rowIndex++;
    }

    head_node = createNode(createPair(tokenMatrix[0][0], tokenMatrix[0][1]));
    for (int i = 1; i < rowIndex; i++)
    {
        insert(head_node, tokenMatrix[i][0], tokenMatrix[i][1]);
    }
    print_dict(head_node);

    // Close the file
    fclose(file);
    free(tokenMatrix);
    // Free the allocated memory
    free(new_line);
}

char **split_dict_value(Node *head_node, const char delimiter[]){
    char ***tokenMatrix = (char ***)malloc(sizeof(char **) * getDictLength());
    char **token = (char **)malloc(sizeof(char *));
    
    for (int i = 0; i < getDictLength(); i++)
    {
        tokenMatrix[i] = (char **)malloc(sizeof(char *));
        char *token = strtok(getViaIndex(head_node, i), delimiter);
        printf("token = %s", token);
    }
    
}

void execute_file(Node *head_node) {
    split_dict_value(head_node, " ");
}

int main(int argc, char const *argv[])
{
    FILE *file = openFile(argc, argv, "r");
    readFile(file);
    Generic *generic = createGeneric(INT);
    printf("type: %s\n", typeOf(generic));
    return 0;
}
