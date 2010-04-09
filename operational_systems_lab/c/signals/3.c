/* Modify the exercise 2 to ignore the chosen signals
 * 
 * Chosen signals: SIGTERM and SIGINFO. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int main(void){
        struct sigaction sigterm;
        struct sigaction siginfo;

        sigterm.sa_handler = SIG_IGN;
        siginfo.sa_handler = SIG_IGN;

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
