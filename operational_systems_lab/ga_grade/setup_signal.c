void handle_sighup(int signal){
        /* when SIGHUP exit */
        exit(0);
}

void handle_sigusr1(int signal){
        /* when SIGUSR1 reload */
        int ret = reload_parameters(void);
}

int setup_signals(void){
        /* Ignore signal */
        int ret2 = sigaction(SIGTERM,SIG_IGN,NULL);

        /* creating sigaction structs */
        struct sigaction sighup, sigusr1;

        /* assign handlers */
        sighup.sa_handler = &handle_sighup;
        sigusr1.sa_handler = &handle_sigusr1;

        /* assign sighup sigaction to handle SIGHUP */
        int ret1 = sigaction(SIGHUP,&sighup,NULL); 
        /* assign sigusr1 sigaction to handle SIGUSR1 */
        int ret2 = sigaction(SIGUSR1,&sigusr1,NULL);

        /* if ret is -1 an error occured */
        if(ret1 == -1 || ret2 == -1){
                printf("An error occured when assigning 
                                a function to signal\n");
                exit(-1);
        }

        return 0;
}

