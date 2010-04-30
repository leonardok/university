/* Create a program that receives as parameter a command and a max time
 * for that command to run.
 *
 * It must create create a child process to execute the given command
 * and control execution time. If the command exceds the time given
 * it must terminate with a signal that guarantees its termination.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t pid = 0;

void handle_sigalrm(int signal){
        kill(pid, SIGINT);
        exit(0);
}

int main(void){
        int seconds;
        char command[30];

        struct sigaction sigalrm;
        sigalrm.sa_handler = &handle_sigalrm;
 
        if(sigaction(SIGALRM, &sigalrm, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        printf("This program will execute a command for a given time\n\n");

        printf("Enter command: ");
        scanf("%s", &command);

        printf("Enter time: ");
        scanf("%d", &seconds);

        if((pid = fork()) == 0){
                /* executes the given command */
                execvp();
                exit(0);
        }
        if(pid > 0){
                /* set alarm for time limit*/
                alarm(seconds);

                /* set mask of signals to readfrom */
                sigsuspend();
        }

        return 0;
}
