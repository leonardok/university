/* Crie um programa em C que cria um processo filho usando fork(). O filho 
 * apresenta na tela a mensagem “Sou filho!”, seu PID e o PPID. Após o filho 
 * terminar sua execução, o pai apresenta na tela a mensagem “Sou pai!”, o seu 
 * PID e PPID. Não esqueça de executar os tratamentos de erro!
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
        pid_t pid;

	if((pid = fork()) < 0){
		printf("Filho nao foi criado\n");
                exit(-1);
        }
        else if(pid == 0){
		printf("I'm a new process, PID %d\n", getpid());
		printf("Parent have PPID %d\n", getppid());
		exit(0);
	}

	printf("And I'm the father with PID %d\n", getpid());
	return 0;
}
