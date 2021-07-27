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

/**
 * 
 * A structure representing a customer - a line in the file.
 * 
 */
struct Customer
{
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
 * Stores every resource available in the program.
 * 
 */
int *available_resources;

int load_available_resources(int count, char *args[]);

int load_customer_resources();

void run();

void request_resource();

void release_resource();

void run_resource();

void print_resources();