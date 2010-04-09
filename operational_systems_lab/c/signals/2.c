/* Develop a program that handles two signals of any kind other than SIGUSR1, 
 * SIGUSR2, SIGQUIT, SIGCHLD or SIGINT. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void handle_sigterm(int a){
        printf("The process PID is %d and it will be terminated\n", getpid());

        exit(0);
}
void handle_siginfo(int a){
        printf("The process PID is %d hanlding a SIGINFO\n", getpid());
}


int main(void){
        struct sigaction sigterm;
        struct sigaction siginfo;

        sigterm.sa_handler = &handle_sigterm;
        siginfo.sa_handler = &handle_siginfo;

        if(sigaction(SIGINFO, &siginfo, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        if(sigaction(SIGTERM, &sigterm, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        while(1);

        return 0;
}
