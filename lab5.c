#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int bankers_algorithm();

int request_resources(int customer_number, int request[]);
int release_resources(int customer_number, int release[]);
int main(int argc, char* argv[]){
    
    if (argc != NUMBER_OF_RESOURCES + 1){
        printf("Not enough arguments");
        return 1;
    }

    // assign the available resources to the available array
    for (int i = 1; i < NUMBER_OF_RESOURCES + 1; i++){
        available[i - 1] = argv[i];
    }


}

//customer method to request resources
int request_resources(int customer_number, int request[]){
    //check if there is enough of each resource to allocate
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        if (available[i] < request[i]){
            printf("Not enough resources");
            return -1;
        }
        if (need[customer_number][i] < request[i]){
            printf("Allocating too much resources");
            return -1;
        }
    }
    //allocate the resources, subtract allocated resources from need
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        available[i] -= request[i];
        allocation[customer_number][i] += request[i];
        need[customer_number][i] -= request[i];
    }
    return 0;
}

//customer method to release resources
int release_resources(int customer_number, int release[]){
    // check if there is enough resources to release
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        if (allocation[customer_number][i] - release[i] < 0){
            return -1;
        }
    }
    // release the resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++){
        allocation[customer_number][i] -= release[i];
    }
    printf("Released: [%d, %d, %d]", release[0], release[1], release[2]);
    return 0;
}