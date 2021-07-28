#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

char **split_string_array(char *input, char *delimiter);
int *split_int_array(char *input, char *delimiter);

int length_int_array(int *array);
int length_string_split_array(char *input, char *delimiter);

char *scan_line();

/**
 * 
 * Helper function that splits a string into an array of strings.
 * 
 * @param input The string to split.
 * @param delimiter The delimiter to split the string on.
 * 
 * @returns An array of strings.
 * @author Nausher Rao
 * 
 */
char **split_string_array(char* input, char *delimiter) {
    char *input_copy = strdup(input);
    char *token;

    int length = length_string_split_array(input, delimiter);
    char **array = malloc(sizeof(char*) * length);

    int i = 0;
    while((token = strsep(&input_copy, delimiter))) {
        array[i] = token;
        i += 1;
    }

    return array;
}

/**
 * 
 * Helper function that splits a string into an array of ints.
 * 
 * @param input The string to split.
 * @param delimiter The delimiter to split the string on.
 * @param length The length of the array to create.
 * 
 * @returns An array of ints.
 * @author Nausher Rao
 * 
 */
int *split_int_array(char* input, char *delimiter) {
    char *input_copy = strdup(input);
    char *token;

    int length = length_string_split_array(input, delimiter);
    int *array = malloc(sizeof(int) * length);

    int i = 0;
    while((token = strsep(&input_copy, delimiter))) {
        array[i] = atoi(token);
        i += 1;
    }

    return array;
}

/**
 * 
 * Returns the amount of elements in an int array.
 * 
 * @param array The array to count the elements of.
 * @returns The amount of elements in the array.
 * @author Nausher Rao
 * 
 */
int length_int_array(int *array) {
    int length = 0;
    int *pointer = array;
    
    while(*pointer) {
        length++;
        pointer++;

    }

    return length;
}

/**
 * 
 * Returns the amount of elements in a string array after it has been split.
 * 
 * @param array The array to count the elements of.
 * @param delimiter The delimiter to split the string on.
 * 
 * @returns The amount of elements in the array.
 * @author Nausher Rao
 * 
 */
int length_string_split_array(char *input, char *delimiter) {
    char *input_copy = strdup(input);
    char *token;

    int length = 0;
    while((token = strsep(&input_copy, delimiter)))
        length++;

    return length;
}


char *scan_line(void) {
    int max_length = 100;
    char *result = malloc(max_length);

    char *line = result;
    int length = max_length;
    if(result == NULL)
        return NULL;

    while(true) {
        int c = tolower(fgetc(stdin));
        if(c == EOF || c == '\n' || c == '\r')
            break;

        if(--length == 0) {
            length = max_length;
            char * linen = realloc(line, max_length *= 2);

            if(linen == NULL) {
                free(line);
                return NULL;
            }
            result = linen + (result - line);
            line = linen;
        }

        if((*result++ = c) == '\n')
            break;
    }

    *result = '\0';
    result[strcspn(result, "\n")] = 0;

    return line;
}