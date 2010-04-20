#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define POINTER_SIZE 4

int main(int argc, char **argv){
        if(argc < 2){
                printf("Unsuficient parameters.\nUse %s command [command]\n", argv[0]);
                exit(-1);
        }

        /* arg_num is argc - 1 bacause in argv position 0 is the cmd name
         * and we just want to get passed args
        **/
        int arg_num = argc - 1;

        /* ns = return status 0
         * nf = other return status
        **/
        int ns, nf;

        int pid[arg_num];
        char **commands = malloc(POINTER_SIZE * argc);

        /* copy contents from argv to **commands */
        int i;
        for(i=1; i<argc;i++){
                int current_size = sizeof(char)*(strlen(argv[i])+1);

                /* now allocate the size of the current command and
                 * store it into the commands pointer-pointer
                **/
                commands[i-1] = malloc(current_size);
                strcpy(commands[i-1], argv[i]);
        }


        for(i=0; i<arg_num; i++){

                /* THIS IS DANGEROUS
                 *
                 * get command to run and cerefull with the command pointer.
                 * when we free the commands[i] the memory pointed by *command
                 * is freed within. 
                **/
                char *command = commands[i];

                /* do fork in the cmd */
                if((pid[i] = fork()) < 0){
                        printf("Could not create the child");
                        exit(-1);
                }
                else if(pid[i] == 0){
#ifdef DEBUG
                        printf("This is a child process with PID %d\n", getpid());
                        printf("Executing command: %s\n", command);
#endif
                        char *args[] = {command, (char *) 0};

                        execvp(command, args);
                        exit(0);
                }
        
                /* if pid still not done kill it */
                else {
                        sleep(2);
                        kill(pid[i], SIGKILL);

                        int stat_loc;
                        waitpid(pid[i], &stat_loc, WUNTRACED);

                        if(stat_loc == 0) ns++; else nf++;
                }
        /* end for */
        }

        printf("\nStatus:\n");
        printf("Total commands executed is %d\n", ns+nf);
        printf("Total commands executed with success is %d\n", ns);

        /* we can free it all now, even knowing OS will free all areas
         * of this process when it is done, it is nice to know we are
         * doing it ourselves
        **/
        for(i=arg_num-1; i>=0; i--){
                int current_size = sizeof(char)*(strlen(commands[i])+1);

                free(commands[i]);
                commands[i] = NULL;
                printf("free ok\n");
        }

        free(commands);

        return 0;
}
