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

bool need_work_comparison(int *need, int *work);
int *array_addition(int *work, int *allocation);

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

/**
 * 
 * Scans and returns the line entered by the user from the standard input (Console).
 * 
 * @returns A string containing the line entered by the user.
 * @author Nausher Rao
 * 
 */
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

/**
 * 
 * Compares the work to the need. 
 * If need <= work, return true
 * If need > work, return false
 * 
 * @param *need The needed resources.
 * @param *work The work resources.
 * 
 * @returns Whether or not need is greater than work.
 * @author Declan Hollingworth 
 * 
 */
bool need_work_comparison(int *need, int *work) {
    for(int i = 0; i < resource_amount; i++) 
        if (need[i] <= work[i]) 
            return true;
    
    return false;
}

/**
 * 
 * Compares the need to the request. 
 * If request <= need, return true
 * If need > work, return false
 * 
 * @param *need The needed resources.
 * @param *request The request.
 * 
 * @returns Whether or not need is greater than request.
 * @author Declan Hollingworth 
 * 
 */
bool need_request_comparison(int *need, int *request) {
    for(int i = 0; i < resource_amount; i++) 
        if (request[i] <= need[i]) 
            return true;

    return false;
}

/**
 * 
 * Compares the available to the request. 
 * If request <= availible, return true
 * If request > availible, return false
 * 
 * @param *availible The availible resources.
 * @param *request The request.
 * 
 * @returns Whether or not availible is greater than work.
 * @author Declan Hollingworth 
 * 
 */
bool available_request_comparison(int *available, int *request) {
    for(int i = 0; i < resource_amount; i++) 
        if (request[i] <= available[i]) 
            return true;
    
    return false;
}



/**
 * 
 * Auxilary Function to Perform work + allocation operation
 * 
 * @param *work The work resources.
 * @param *allocation The allocated resources.
 * 
 * @returns The work resources after allocation.
 * @author Declan Hollingworth 
 * 
 */
int *array_addition(int *work, int *allocation) {
    for(int i = 0; i < resource_amount; i++) {
        work[i] = work[i] + allocation[i];
    }

    return work;

}