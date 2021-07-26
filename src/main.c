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
    load_data_from_file();
    run();

    return 0;
}

/**
 * 
 * Loads the bank's resources from the command line.
 * @author <>
 * 
 */
void load_available_resources() {


}

/**
 * 
 * Loads customer data from file.
 * @author <>
 *  
 */
void load_data_from_file() {
    FILE *file = fopen("sample4_in.txt", "r");
    if (file == NULL) {
        printf("Error opening file \"sample4_in.txt\"");
        return;
    }



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
        for(char *p = input; *p; p++) *p=tolower(*p); // Converts to lower case.

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