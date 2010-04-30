#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#define MAX_THREADS 2
#define MAX_MEMBERS 100

int vector[MAX_MEMBERS];

void *sum_stuff(void *arg){
        int *vector_part = (int *)arg;
        int begin = vector_part[0];
        int end   = vector_part[1];

        int sum = 0;
        int i;
        for(i=begin; i<=end; i++){
                sum += vector[i];
        }

        pthread_exit((void *)sum);
}

void populate_vector(int vector[MAX_MEMBERS]){
        int i, total_sum = 0;

        for(i=0; i<MAX_MEMBERS; i++){
                srand(time(NULL));
                vector[i] = rand() % 73;
                total_sum += vector[i];
        }

        printf("Sum with no threads is %d\n", total_sum);
}

void print_vector(int vector[MAX_MEMBERS]){
        int i;
        for(i=0; i<MAX_MEMBERS; i++){
                printf("%d ", vector[i]);
        }
}

int main(void){
        /* declare the vector */
        int **vector_part;
        vector_part = malloc(sizeof(int) * MAX_THREADS * 2);

        int total_sum = 0;

        pthread_t pthread_id[MAX_THREADS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        populate_vector(vector);
        //print_vector(vector);

        /* split vector into MAX_THREADS */
        int size = floor(MAX_MEMBERS/MAX_THREADS);

        /* calculate if the size of each part times number of threads is 
         * different from the size of the vector. This will happen when the 
         * size of the vector is not multiple of the number of threads
        **/
        int last_part = size;
        if((size * MAX_THREADS) != MAX_MEMBERS){
                last_part = (MAX_MEMBERS - (size * (MAX_THREADS - 1)));
        }

        /* i go only to MAX_THREADS - 1 to leave space for the last_part
         * thread. If the MAX_THREADS is 1 it wont go inside this loop
        **/
        int i = 0;
        for(i=0;i<(MAX_THREADS - 1);i++){
                vector_part[i] = malloc(sizeof(int) * 2);

                vector_part[i][0] = (size * i);
                vector_part[i][1] = (size * (i+1)) - 1;

                /* create thread to count on elements */
                pthread_create(&pthread_id[i],
                               &attr,
                               (void *) &sum_stuff,
                               (void *) vector_part[i]);
        }

        /* last_part */
        vector_part[i] = malloc(sizeof(int) * 2);

        vector_part[i][0] = (size * i);
        vector_part[i][1] = (size * i) + last_part;

        /* create thread that will count the last_part vector */
        pthread_create(&pthread_id[i],
                       &attr,
                       (void *) &sum_stuff,
                       (void *) vector_part[i]);

        /* join with threads */
        int sum;
        for(i=0;i<(MAX_THREADS);i++){
                pthread_join(pthread_id[i], (void *) &sum);
                total_sum += sum;
        }
        

        /* free allocated space on vector_part */
        for(i=0;i<(MAX_THREADS);i++){
                free(vector_part[i]);
        }
        free(vector_part);

        printf("Total sum with %d threads is %d\n", MAX_THREADS, total_sum);
        pthread_exit(0);
}
