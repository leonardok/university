/* Crie um programa em C que permanece em um laço lendo URLs em sua entrada 
 * padrão (uma por linha) e dispare um processo filho para fazer o download da 
 * mesma a partir da internet Dica: utilize os programas wget ou curl para 
 * efetuar do download.
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void){
        char url[80];
        pid_t pid;

        while(1){
                scanf("%s", url);

                if((pid = fork()) < 0){
                        printf("Could not create child\n");
                }
                else if(pid == 0){
                        char *args[] = {"curl", "-s", url, "-o", url};

                        execvp("curl", args);

                        printf("downloaded %s\n", url);
                        exit(0);
                }
        }
        return 0;
}
