#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "stshell.h"
#define MAX_COMMAND_LENGTH 1024

/* make some changes on the basic_shell*/

int main() {

    int i;
    char *token;
    char *argv[10];
    char command[MAX_COMMAND_LENGTH + 1] = {0};
    sig_atomic_t interrupte = 0;

    while(1) {
        printf("stshell> ");
        fflush(stdout);
	    while( fget( command, 1024, stdin) ) {
            if(errno == EINTR && interrupte ) {
                printf( "^C \n " );
                fflush(stdout);
                interrupte = 0;
                break;
            }
        }

	    command[strlen(command) - 1] = '\0'; 
        
        if (strcmp(command, "exit") == 0)
            break;
    
	    i = 0;
	    token = strtok (command," ");

	    while (token != NULL) {
            argv[i] = token;
            token = strtok (NULL, " ");
            i++;
	    }

	    argv[i] = NULL;

	    /* Is command empty */ 
	    if (argv[0] == NULL)
		    continue;

	    /* for commands not part of the shell command language */ 
	    if (fork() == 0) { 
		execvp(argv[0], argv);
		wait(NULL);
	    }    
	}
}


