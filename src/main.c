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
        customer.needed_resources = malloc(sizeof(int) * resource_amount);
        customer_resources[i].finished = false;

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
int safe_state(int customer_amount, int resource_amount) {
    int safe = 0;
    int *work = available_resources; 
    
    /* Finish = false for all i to n */

    for(int i=0; i < customer_amount; i++){
        struct Customer cust = customer_resources[i];
        /*Step 2 */
        if (cust.finished == false && (need_work_comparison(cust.needed_resources, work, resource_amount) == 1)) {    
            /*Step 3 */
            work[i] = array_addition(work, cust.allocated_resources[i], resource_amount);
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


/**
 * 
 * Auxilary Function to Perform work + allocation operation
 * 
 * @author Declan Hollingworth 
 * 
 */
int array_addition(int *work, int *allocation, int resource_amount) {
    for(int i = 0; i < resource_amount; i++) {
        work[i] = work[i] + allocation[i];
    }
    return work;
}

void request_resources_command(int customer_index, int *requested_resources) {}

void release_resources_command(int customer_index, int *releasing_resources) {}

void run_command() {}

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