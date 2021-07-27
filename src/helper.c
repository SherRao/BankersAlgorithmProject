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

char **split_string_array(char *input, char *delimiter, int length);
int *split_int_array(char *input, char *delimiter, int length);

/**
 * 
 * Helper function that splits a string into an array of strings.
 * 
 * @param input The string to split.
 * @param delimiter The delimiter to split the string on.
 * @param length The length of the array to create.
 * 
 * @returns An array of strings.
 * @author Nausher Rao
 * 
 */
char **split_string_array(char* input, char *delimiter, int length) {
    char **array = malloc(sizeof(char*) * length);

    int i = 0;
    char *token;
    while((token = strsep(&input, delimiter))) {
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
int *split_int_array(char* input, char *delimiter, int length) {
    int *array = malloc(sizeof(int) * length);

    int i = 0;
    char *token;
    while((token = strsep(&input, delimiter))) {
        array[i] = atoi(token);
        i += 1;
    }

    return array;
}