/**
 * 
 * CP 386 - Assignment 4
 * 
 * 
 * @author Nausher Rao (190906250) - https://github.com/SherRao/
 * @author Declan Hollingworth () - https://github.com/wowitsdeclan
 * 
 * @see https://github.com/SherRao/BankersAlgorithmProject
 * 
 */

#include "main.h"

/**
 * 
 * Main entry point.
 * 
 * @author <> 
 * 
 */
int main(int arg_count, char *args[]) {
    if(arg_count == 1) {
        printf("There should be more than one integer arguments!");
        return 1;

    }

    load_available_resources();
    load_customer_resources();
    run();

    return 0;
}

/**
 * 
 * Loads the avilable resources from the command line.
 * @author Nausher Rao
 * 
 */
void load_available_resources(int count, int *args[]) {
	for (int i = 1; i < count; i++) 
        available_resources[i] = atoi( args[i] );

}

/**
 * 
 * Loads customer data from file.
 * @author <>
 *  
 */
void load_customer_resources() {
    FILE *file = fopen("sample4_in.txt", "r");
    if (file == NULL) {
        printf("Error opening file \"sample4_in.txt\"");
        return;
    }

    struct stat file_stats;
	fstat(fileno(file), &file_stats);
	char* contents = (char*) malloc( ((int)file_stats.st_size + 1) * sizeof(char) );
    contents[0] = '\0';

    // Add the entire contents of the file to the string.
    char str[1000];
    while (fgets(str, sizeof(str), file) != NULL) 
        strncat(contents, str, strlen(str));

    // Close the file.


    fclose(file);

}

/**
 * 
 * Loops until the user types in "exit" - allows the user to 
 * interact with the program.
 * 
 * @author Nausher Rao 
 * 
 */
void run() {
    char *input;
    while(running) {
        scanf("Command >> %d", input); 
        for(char *p = input; *p; p++) *p = tolower(*p); // Converts to lower case.

        if(strcmp(input, "rq") == 0) {
            request_resource();

        } else if(strcmp(input, "rl") == 0) {
            release_resource();
        
        } else if(strcmp(input, "run") == 0) {
            run_resource();
        
        } else if(strcmp(input, "*") == 0) {
            print_resources();
        
        } else if(strcmp(input, "exit") == 0) {
            running = false;

        } else 
            printf("Invalid command!\n");

    }
}

void request_resource() {}

void release_resource() {}

void run_resource() {}

void print_resources() {}