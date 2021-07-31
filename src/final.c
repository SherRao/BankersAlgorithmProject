/**
 * 
 * CP 386 - Assignment 4
 * 
 * 
 * @author Nausher Rao (190906250) - https://github.com/SherRao/
 * @author Declan Hollingworth (109765210) - https://github.com/wowitsdeclan
 * 
 * @see https://github.com/SherRao/BankersAlgorithmProject
 * 
 */
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

bool running = true;
const char *FILE_NAME = "sample4_in.txt";

/**
 * 
 * A structure representing a customer/thread.
 * 
 */
struct Customer
{
    int id;
    int *max_resources;
    int *allocated_resources;
    int *needed_resources;
    bool finished;
};

/**
 * 
 * Stores every customer currently in the program.
 * 
 */
struct Customer *customer_resources;

/**
 * 
 * Stores the amount of every type of resource available in the program.
 * 
 */
int *available_resources;

/**
 * 
 * Stores the types of resources available in the program. 
 * 
 */
int resource_amount;

/**
 * 
 * Stores the amount of customers currently in the program.
 * 
 */
int customer_amount;

int load_available_resources(int count, char *args[]);

int load_customer_resources();

void run_program();

void request_resources_command(int customer_index, int *requested_resources);

void release_resources_command(int customer_index, int *releasing_resources);

void run_command();

void *run_command_function();

void status_command();

char **split_string_array(char *input, char *delimiter);

int *split_int_array(char *input, char *delimiter);

int length_int_array(int *array);

int length_string_split_array(char *input, char *delimiter);

char *scan_line();

bool need_work_comparison(int *need, int *work);

int *array_addition(int *work, int *allocation);

/**
 * 
 * Helper function that splits and returns a string into
 * an array of strings.
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
 * Helper function that splits and returns a string
 * into an array of ints.
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
 * Helper function that calculated and teturns the
 * amount of elements in an int array.
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
 * Helper function that calculates returns the amount of 
 * elements in a string array after it has been split.
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
 * Helper function that scans and returns the line entered by the
 * user from the standard input (Console).
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
 * Helper function that compares the work to the need. 
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
 * Helper function that compares the need to the request. 
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
        if (request[i] > need[i]) 
            return false;

    return true;
}

/**
 * 
 * Helper function that compares the available to the request. 
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
        if (request[i] > available[i]) 
            return false;
    
    return true;
}

/**
 * 
 * Helper function that performs the work + allocation operation
 * 
 * @param *work The work resources.
 * @param *allocation The allocated resources.
 * 
 * @returns The work resources after allocation.
 * @author Declan Hollingworth 
 * 
 */
int *array_addition(int *work, int *allocation) {
    for(int i = 0; i < resource_amount; i++) 
        work[i] = work[i] + allocation[i];

    return work;
}

/**
 * 
 * Main entry point.
 * 
 * @author Nausher Rao
 * @author Declan Hollingworth
 * 
 */
int main(int arg_count, char *args[]) {
    if(arg_count == 1) {
        printf("[System] There should be more than one integer arguments!\n");
        return 1;
    }

    load_available_resources(arg_count, args);
    load_customer_resources(resource_amount);
    run_program();
    return 0;
}

/**
 * 
 * Loads the avilable resources from the command line.
 * 
 * @param count The amount of arguments from the command line.
 * @param args The arguments from the command line.
 * 
 * @returns The number of resources per customer.
 * @author Nausher Rao
 * 
 */
int load_available_resources(int count, char *args[]) {
	available_resources = (int *)malloc((count - 1) * sizeof(int));
    for (int i = 1; i < count; i++)
        available_resources[i - 1] = atoi(args[i]);
    
    resource_amount = count - 1;
}

/**
 * 
 * Loads customer data from file.
 * 
 * @param resource_amount The number of resources per customer.
 * 
 * @returns The number of customers.
 * @author Nausher Rao
 *  
 */
int load_customer_resources() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("[System] Error opening file \"%s\"", FILE_NAME);
        return -1;
    }

    char line[1000];

    // Go through the file line by line to grab the file length.
    while (fgets(line, sizeof(line), file) != NULL)
        customer_amount += 1;

    customer_resources = malloc(sizeof(struct Customer) * customer_amount);
    fseek(file, 0, SEEK_SET);

    // Grabs every line from the file and turn it into a Customer struct.
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        struct Customer customer;
        customer.max_resources = split_int_array(line, ",");
        customer.allocated_resources = malloc(sizeof(int) * resource_amount);
        customer.needed_resources = split_int_array(line, ",");
        customer.finished = false;
        customer.id = i;

        customer_resources[i] = customer;
        i++;
    }

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
void run_program() {
    while(running) {
        printf("Enter Command >> ");
        char *input = scan_line();
        char **args = split_string_array(input, " ");
        int arg_length = length_string_split_array(input, " ");

        // Logic for the "request" command
        if(strcmp(args[0], "rq") == 0) {
            if(arg_length == 2 + resource_amount) {
                int customer_index = atoi(args[1]);
                int requested_resources[resource_amount];
                for(int i = 0; i < resource_amount; i++)
                    requested_resources[i] = atoi(args[2 + i]);

                request_resources_command(customer_index, requested_resources);

            } else {
                printf("[System] Error! This command takes %d arguments!\n", resource_amount + 1);
                printf("[System] Usage: rq <customer_id> ");
                for(int i = 0; i < resource_amount; i++)  printf("<resource%d> ", i+1);
                printf("\n");
            }

        // Logic for the "release" command
        } else if(strcmp(args[0], "rl") == 0) {
            if(arg_length == 2 + resource_amount) {
                int customer_index = atoi(args[1]);
                int releasing_resources[resource_amount];

                for(int i = 0; i < resource_amount; i++)
                    releasing_resources[i] = atoi(args[2 + i]);

                release_resources_command(customer_index, releasing_resources);

            } else {
                printf("[System] Error! This command takes %d arguments!\n", resource_amount + 1);
                printf("[System] Usage: rl <customer_id> ");
                for(int i = 0; i < resource_amount; i++) printf("<resource%d> ", i+1);
                printf("\n");
            }

        // Logic for the "run" command
        } else if(strcmp(args[0], "run") == 0) {
            run_command();
        
        // Logic for the "status" command
        } else if(strcmp(args[0], "status") == 0) {
            status_command();
        
        // Logic for the "exit" command
        } else if(strcmp(args[0], "exit") == 0) {
            running = false;
            printf("[System] Exiting program...\n");

        } else 
            printf("[System] Invalid command!\n");
    }
}

/**
 * 
 * Checks if the system is in a safe state. 
 * 
 * @author Declan Hollingworth 
 * 
 */
bool safe_state() {
    bool safe = false;
    int *work = malloc(sizeof(int) * resource_amount);
    
    // Set work = availible
    for(int i = 0; i < resource_amount; i++)
        work[i] = available_resources[i];
    
    // Set all finish statuses to false
    for(int i = 0; i < customer_amount; i++)
        customer_resources[i].finished = false;

    // Set i such that Finish[i] = false and need <= work
    bool found = false;
    for(int i=0; i < customer_amount; i++) {
        struct Customer cust = customer_resources[i];

        // Step 2
        if (cust.finished == false && need_work_comparison(cust.needed_resources, work)) {  
            // Step 3
            work = array_addition(work, cust.allocated_resources);
            cust.finished = true;
            customer_resources[i] = cust;
        } 
    }

    // Step 4
    int j = 0;
    while (j < customer_amount) {
        if(customer_resources[j].finished == true)
            j++;

        if(j == customer_amount - 1)
            return true;
    }

    return safe;
}

void request_resources_command(int customer_index, int *requested_resources) {
    struct Customer customer = customer_resources[customer_index];
    bool is_safe = safe_state();

    if(is_safe) {
        printf("[System] The system is in safe state!\n");
        bool is_needed = need_request_comparison(customer.needed_resources, requested_resources);

        if(is_needed) {
            bool is_available = available_request_comparison(available_resources, requested_resources);
            if(is_available) {
                for(int i = 0; i < resource_amount; i++) {
                    available_resources[i] = available_resources[i] - requested_resources[i];
                    customer.allocated_resources[i] = customer.allocated_resources[i] + requested_resources[i];
                    customer.needed_resources[i] = customer.needed_resources[i] - requested_resources[i];
                }

                printf("[System] Requested resources for customer #%d\n", customer_index);

            } else 
                printf("[System] Error! Not enough resources available!\n");

        } else
            printf("[System] Error! Resources arent needed!\n");
        
    } else
        printf("[System] The system is currently not safe!\n");
}

void release_resources_command(int customer_index, int *releasing_resources) {
    struct Customer customer = customer_resources[customer_index];
    bool should_release = true;
    
    for(int i = 0; i < resource_amount; i++) {
        if(releasing_resources[i] > customer.allocated_resources[i]) {
            should_release = false;
            break;
        }
    }

    if(should_release) {
        for(int i = 0; i < resource_amount; i++) {
            available_resources[i] = available_resources[i] + releasing_resources[i];
            customer.allocated_resources[i] = customer.allocated_resources[i] - releasing_resources[i];
        }

        printf("[System] Released resources for customer #%d!\n", customer_index);

    } else 
        printf("[System] Can't release all the resources!\n");
}

void run_command() {
    printf("[System] Starting the run command...\n");
    for(int i = 0; i < customer_amount; i++) {
        struct Customer cust = customer_resources[i];
        pthread_t thread_id;
        pthread_attr_t thread_attribs;

        pthread_attr_init(&thread_attribs);
        pthread_create(&thread_id, &thread_attribs, run_command_function, (void *) &i);
        pthread_join(thread_id, NULL);
    }

    printf("[System] The run command is finished! Printing the new state of the program...\n");
    status_command();
}

void *run_command_function(void *customer_id) {
    int customer_index = *((int *) customer_id);
    struct Customer customer = customer_resources[customer_index];

    for(int i = 0; i < resource_amount; i++) {
        available_resources[i] = available_resources[i] + customer.allocated_resources[i];
        customer.allocated_resources[i] = 0;
        customer.needed_resources[i] = customer.max_resources[i];
    }
}

/**
 * 
 * Prints the current state of the system.
 * 
 * @author Nausher Rao
 * 
 */
void status_command() {
    printf("[System] Printing the current state of the program...\n\n");
    printf("Customers: %d\n", customer_amount);
    printf("Resources: %d\n", resource_amount);
    printf("Available Resources: [ ");
    for (int i = 0; i < resource_amount; i++)
        printf("%d ", available_resources[i]);

    printf("]\nCustomers:\n");

    for (int i = 0; i < customer_amount; i++) {
        struct Customer cust = customer_resources[i];
        printf("\tCustomer #%d\n", i);

        printf("\t\tAllocated Resources: [ ");
        for (int j = 0; j < resource_amount; j++)
            printf("%d ", cust.allocated_resources[j]);

        printf("]\n\t\tMaximum Resources: [ ");
        for (int j = 0; j < resource_amount; j++) 
            printf("%d ", cust.max_resources[j]);

        printf("]\n\t\tNeeded Resources: [ ");
        for (int j = 0; j < resource_amount; j++) 
            printf("%d ", cust.needed_resources[j]);

        printf("]\n\t\tFinished: %d\n\n", cust.finished);
    }
}