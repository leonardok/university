#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 2
#define MAX_MEMBERS 100


void populate_vector(int *vector[MAX_MEMBERS]){
        int i;
        for(i=0; i<MAX_MEMBERS; i++){
                vector[i] = rand() % 10000;
        }

}
int main(void){
        /* declare the vector */
        int vector[MAX_MEMBERS];
        populate_vector(vector[MAX_MEMBERS]);

        /* first 

        printf("\n");
        pthread_exit(NULL);
        */

        return 0;
}
