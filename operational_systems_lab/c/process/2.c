/* Faça um programa em C que crie 5 processos filhos. Cada filho inicia a 
 * execução dormindo um tempo diferente (sugestão: valor randômico entre 5 e 8) 
 * segundos. Ao acordar o filho imprime sua ordem na criação, seu pid e a 
 * mensagem “acordou”. Após criar todos os filhos, o pai aguarda cada um deles 
 * terminar. imprime “FIM!”.
 *
 * Pai criando filhos... 
 * Pai aguardando filhos... 
 * filho#3 (pid=1234) acordou! 
 * filho#1 (pid=1234) acordou! 
 * filho#5 (pid=1234) acordou! 
 * filho#4 (pid=1234) acordou! 
 * filho#2 (pid=1234) acordou! 
 * FIM!
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
        int pid;
        printf("Current process have PID of %d\n\n", getpid());
        printf("Creating processes...\n");

        int i;
        for(i = 0; i < 5; i++){
                int sleep_time = (random() % 3) + 5;

                pid = fork();
                if(pid < 0){
                        printf("Could not create child\n");
                        exit(-1);
                }
                else if(pid == 0){
                        sleep(sleep_time);
                        printf("I'm son #%d, PID is %d wakeup!\n", i, getpid());
                        exit(0);
                }
        }

        printf("Waiting for child processes to end\n");

        for(i = 0; i < 5; i++)
                wait(NULL);

        printf("\n");
        printf("All good\n");

        return 0;
}
