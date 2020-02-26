#include <stdio.h>
#include "banker.h"

int compare(int[], int[]);
int safety_check();
void print_array(char *description, int array[][NUMBER_OF_RESOURCES]);

/* 
 * return 0 if all resources can be requested immediately,else return -1
 */
int request_resources(int customer_num, int request[]) {
    if (compare(request, need[customer_num]) == 1) {
        printf("requested resources exceed max demand\n");
        return -1;
    }

    // if there aren't enough resources,request should be denied
    if (compare(request, available) == 0) {
        // set state to after receiving the request
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            available[i] -= request[i];
            allocation[customer_num][i] += request[i];
            need[customer_num][i] -= request[i];
        }

        // if the system is not in a safe state,request should be denied and state should be rollbacked
        if (safety_check() == 0) {
            return 0;
        } else {
            for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
                available[i] += request[i];
                allocation[customer_num][i] -= request[i];
                need[customer_num][i] += request[i];
            }
            return -1;
        }
    } else {
        printf("requested resources exceed available resources\n");
        return -1;
    }
}

void release_resources(int customer_num, int release[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
    }
}

void print_property() {
    printf("available resources:");
    printf("\n");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d", available[i]);
        printf(" ");
    }
    printf("\n");

    print_array("max demand of resources:", maximum);
    print_array("allocated resources:", allocation);
    print_array("remaining needed resources:", need);
}

/* 
 * define a<=b for arbitrary i, a[i]<=b[i]
 * if a<=b return 0,else return 1
 */
int compare(int a[], int b[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (a[i] > b[i]) {
            return 1;
        }
    }
    return 0;
}

/* 
 * return 0 if the system is in a safe state,else return 1
 */
int safety_check() {
    int finish[NUMBER_OF_CUSTOMERS];
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        finish[i] = 0;
    }
    int work[NUMBER_OF_RESOURCES];
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (finish[i] == 0 && compare(need[i], work) == 0) {
            for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                work[j] += allocation[i][j];
            }
            finish[i] = 1;
            i = -1;
        }
    }

    // if all customers finish their requests,it means that the system is in a safe state
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (finish[i] == 0) {
            return 1;
        }
    }
    return 0;
}

void print_array(char *description, int array[][NUMBER_OF_RESOURCES]) {
    printf(description);
    printf("\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d", array[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}