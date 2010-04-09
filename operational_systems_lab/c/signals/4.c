/* Loop reading values and when CTRL+C is received if prints the sum
 * of all readed numbers
 * 
 * CTRL+C is SIGINT
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int sum;

void handle_sigint(int signal){
        printf("SIG %x received\n", signal);
        printf("Sum of entered numbers is %d\n", sum);

        exit(0);
}

int main(void){
        struct sigaction sigint;
        sigint.sa_handler = &handle_sigint;

        if(sigaction(SIGINT, &sigint, NULL) != 0){
                perror("Could not process signal");
                exit(-1);
        }


        sum = 0;

        while(1){
                printf("Enter a number: ");

                int num;
                scanf("%d", &num);

                sum += num;
        }

        /* never executed */
        return 0;
}
