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
#include "helper.c"

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

    int resource_amount = load_available_resources(arg_count, args);
    int customer_amount = load_customer_resources(resource_amount);
    
    // Example of how to loop through every custoimer and their max resources.
    for(int i = 0; i < customer_amount; i++) {
        struct Customer customer = customer_resources[i];
        printf("Customer %d\n", i);
        for(int j = 0; j < resource_amount; j++) {
            printf("%d ", customer.max_resources[j]);

        }

        printf("\n");
    }

    //run();

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
    
    return count - 1;
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
int load_customer_resources(int resource_amount) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file \"%s\"", FILE_NAME);
        return -1;
    }

    int customer_amount = 0;
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
        customer.max_resources = split_int_array(line, ",", resource_amount);
        customer.allocated_resources = malloc(sizeof(int) * resource_amount);
        customer.needed_resources = malloc(sizeof(int) * resource_amount);
        customer_resources[i].finished = false;

        customer_resources[i] = customer;
        i++;
    }

    fclose(file);
    return customer_amount;
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
        sscanf("Command >> %s", input); 
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

/**
 * 
 * Checks if the system is in a safe state. 
 * 
 * @author Declan Hollingworth 
 * 
 */
int safe_state(int customer_amount, int resource_amount) {
    int safe = 0;
    int *work = available_resources; 
    
    /* Finish = false for all i to n */

    for(int i=0; i < customer_amount; i++){
        struct Customer cust = customer_resources[i];
        /*Step 2 */
        if (cust.finished == false && (need_work_comparison(cust.needed_resources, work, resource_amount) == 1)) {    
            /*Step 3 */
            for(int x = 0; x < resource_amount; x++) {
                work[x] = work[x] + cust.allocated_resources[x];
            }
            cust.finished = true;
        } else { 
            /*Step 4 */
            int j = 0;
            while (j < customer_amount) {
                if (customer_resources[j].finished == true) {
                    j++;
                }
                if (j == customer_amount - 1){
                    printf("System is in Safe State");
                    safe = 1;
                    break;
                }
            }
        }
    }
    return safe;
}

/**
 * 
 * Compares the work to the need. 
 * If need <= work, return 1
 * If need > work, return 0 
 * 
 * @author Declan Hollingworth 
 * 
 */
int need_work_comparison(int *need, int *work, int resource_amount) {
    int greater = 1;
    for(int i = 0; i < resource_amount; i++) {
        if (need[i] > work[i]) {
            greater = 0;
            break;
        }
    }
    return greater;
}


void request_resource() {}

void release_resource() {}

void run_resource() {}

void print_resources() {}