<h1 align="center"> 
  Bankers Algorithm
</h1>

<blockquote align="center">
  This is a a multi-threaded, command-line/CLI based program that implements the banker's algorithm.
</blockquote>

<br/>

[![ESLint](https://github.com/SherRao/CP-317/actions/workflows/eslint.yml/badge.svg)](https://github.com/SherRao/BankersAlgorithmProject/actions/workflows/eslint.yml)

[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?)](https://github.com/SherRao/BankersAlgorithmProject/blob/main/LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/SherRao/BankersAlgorithmProject.svg?style=flat)](https://github.com/SherRao/BankersAlgorithmProject/graphs/contributors)
[![GitHub last commit](https://img.shields.io/github/last-commit/SherRao/BankersAlgorithmProject.svg?style=flat)](https://github.com/SherRao/BankersAlgorithmProject/commits/main)

## Motivation
The Motivation for the assignment comes from the course requirments of CP383: Operating Systems

## Installation
x.

## Preview 
![rqCommand](/src/Pictures/rqCommand.png)
![statusCommand](/src/Pictures/StatusCommand.png)
![rlCommand](/src/Pictures/runCommand.png)

## Contributors
- [Declan Hollingworth](https://github.com/wowitsdeclan)<br/>
- [Nausher Rao](https://www.github.com/sherrao)<br/>

```c
int load_available_resources(int count, char *args[]); //Nausher
int load_customer_resources() //Nausher
void run_program() //Nausher
bool safe_state() //Declan
void request_resources_command(int customer_index, int *requested_resources) //Nausher
void release_resources_command(int customer_index, int *releasing_resources) //Nausher
void status_command() //Nausher
char **split_string_array(char* input, char *delimiter) //Nausher
int *split_int_array(char* input, char *delimiter) //Nausher
int length_int_array(int *array) //Nausher
bool need_work_comparison(int *need, int *work) //Declan
bool need_request_comparison(int *need, int *request) //Declan
bool available_request_comparison(int *available, int *request) //Declan
int *array_addition(int *work, int *allocation) //Declan
```

## Features
This program implements the Banker's Algorithm and allows a Customer to request and release resources from the bank. The banker will grant a request if it satsfies the safety algorithm.

## Tests
EX: 
    
    ./main 10 5 7 8

    rq 0 1 0 0 1

    rq 1 1 1 1 1

    rq 2 2 2 2 2

    rq 3 1 1 1 1

    rq 4 1 0 0 0

    run

## Code Examples
EX: 
    
    rq: request resource

    rl: release resource

    status: see the current status of the bank

    exit: exit the program

## About The Developers 
- [Declan Hollingworth](https://github.com/wowitsdeclan): Wilfrid Laurier University BSc in Computer Science '23<br/>
- [Nausher Rao](https://www.github.com/sherrao): Wilfrid Laurier University BSc in Computer Science and Applied Maths '23<br/>

## Credits
- Declan Hollingworth
- Nausher Rao

## License
This project uses the **MIT License** which can be located [here](https://github.com/SherRao/BankersAlgorithmProject/blob/main/LICENSE)
