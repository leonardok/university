#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 3

char WORDS[3] = "ABC";

void *do_thread_stuff(void *i){
        int index = (int) i;
        char *letter = malloc(sizeof(char) + 1);
        
        letter[0] = WORDS[index];
               
        unsigned short int sleep_time = rand() % 10 + 1;

        sleep(sleep_time);

        pthread_exit((void*) letter);
}

int main(void){
        pthread_t pthread_id[MAX_THREADS];
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        int i;
        for(i=0; i < MAX_THREADS; i++){
                printf("Thread number %d\n", i);
                pthread_create(&pthread_id[i], 
                               &attr, 
                               &do_thread_stuff,
                               (void *)i);
        }

        printf("Returning text: \n");

        for(i=0; i < MAX_THREADS; i++){
                char *character = malloc(sizeof(char) + 1);
                pthread_join(pthread_id[i], (void *) &character);

                printf("%s\n", character);
        }

        printf("\n");
        pthread_exit(NULL);
}
