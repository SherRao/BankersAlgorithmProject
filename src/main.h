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