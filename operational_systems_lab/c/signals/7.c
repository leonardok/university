/* Create a program that is imune to CTRL+C
 *
 * It will wait for a signal, when the signal comes it should start
 * a counter that increments each 1 second, sleeping in between.
 * When it receives a SIGUSR2 stops counting.
 *
 * Will wait for SIGUSR1 to start counting
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void dummy_handler(int signal){}

int main(void){
        /* declare we are ignoring SIGINT */
        struct sigaction sigint;
        sigint.sa_handler = SIG_IGN;
 
        if(sigaction(SIGINT, &sigint, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }


        /* declare handling of SIGUSR1 and SIGUSR2 */
        struct sigaction sigusr1;
        struct sigaction sigusr2;

        sigusr1.sa_handler = &dummy_handler;
        sigusr2.sa_handler = &dummy_handler;
 
        if(sigaction(SIGUSR1, &sigusr1, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }
        if(sigaction(SIGUSR2, &sigusr2, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        sigset_t mask;
        sigdelset(&mask, SIGINT);
        sigdelset(&mask, SIGUSR1);
        sigdelset(&mask, SIGUSR2);

        sigsuspend(&mask);

        int counter = 0;

        while(1){
                counter++;

                /* implement a sigqueu */
        }

        return 0;
}
