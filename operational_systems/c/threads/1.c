#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *do_thread_stuff(void *i){
        printf("This is a thread %d\n", (int)i);
        pthread_exit(NULL);
}

int main(void){
        pthread_t pthread_id[10];
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        /* create 10 threads */
        int i;
        for(i=0; i<10; i++){
                printf("Thread number %d\n", i);
                pthread_create(&pthread_id[i], 
                               &attr, 
                               &do_thread_stuff,
                               (void *)i);
        }

        pthread_exit(NULL);
}
