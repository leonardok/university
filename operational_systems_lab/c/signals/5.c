/* Loop reading values and when CTRL+C is received if prints the sum
 * of all readed numbers
 *
 * When SIGQUIT is received makes sum zero
 * 
 * CTRL+C is SIGINT
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t sum = 0;

void handle_sigint(int signal){
        printf("SIG %x received\n", signal);
        printf("Sum of entered numbers is %d\n", sum);

        exit(0);
}

void handle_sigquit(int signal){
        printf("\n");
        printf("Zeroing sum of actual %d\n", sum);

        sum = 0;
}

int main(void){
        struct sigaction sigint;
        struct sigaction sigquit;
        sigint.sa_handler = &handle_sigint;
        sigquit.sa_handler = &handle_sigquit;

        if(sigaction(SIGINT, &sigint, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }

        if(sigaction(SIGQUIT, &sigquit, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }


        int num = 0;

        while(1){
                printf("Enter a number: ");

                scanf("%d", &num);

                sum += num;
                num  = 0;
        }

        /* never executed */
        return 0;
}
