/* Create a program that waits from input a pid number P and time in
 * seconds T. After T the program should send a SIGINT to P.
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

        struct sigaction sigalrm;
        sigalrm.sa_handler = &handle_sigalrm;
 
        if(sigaction(SIGALRM, &sigalrm, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }


        printf("This program will send SIGINT to the specified PID\n\n");

        printf("Enter PID: ");
        scanf("%d", &pid);

        printf("Enter time: ");
        scanf("%d", &seconds);

        alarm(seconds);
        sleep(seconds + 1);

        return 0;
}
