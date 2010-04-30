/* Crie um programa em C que permaneça em um laço lendo nomes de comandos da 
 * entrada padrão e disparando o programa correspondente em um processo filho. 
 * Cada processo filho no incio de sua execução imprime seu pid e o nome do 
 * programa que executará. Por simplicidade, assuma que os comandos executados 
 * estão no PATH do sistema (selecione a variante de exec() apropriada.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1

int main(void){
        char command[15];
        pid_t pid;

        while(TRUE){
                printf("Tell me, what do you want to execute? (no arguments) ");
                scanf("%s", command);

                if((pid = fork()) < 0){
                        printf("Could not create the child");
                        exit(-1);
                }
                else if(pid == 0){
                        printf("This is a child process with PID %d\n", getpid());
                        printf("Executing command: %s\n", command);

                        char *args[] = {command, (char *) 0};

                        execvp(command, args);
                        exit(0);
                }
                else {
                        wait(NULL);
                }

                printf("\n");
        }

        return 0;
}
