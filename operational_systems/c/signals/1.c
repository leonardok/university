/* Develop a program that shows its PID and the PPID when receives the SIGUSR2 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


/* function signature has to be "void foo(int var)" */
void show_pids(int a){
        printf("The process PID is %d and the PPID is %d\n", getpid(), getppid());
}

int main(void){
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));

        sa.sa_handler = &show_pids;

        if(sigaction(SIGUSR2, &sa, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        /* busy waiting */
        while(1);

        /* never run */
        return 0;
}


