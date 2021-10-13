#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "string.h"

#define PROMPT "$ "

int exec(char **args);

int main(int argc, char *argv[])
{
    char buf[256], *cmdline;
    int status;

    fputs(PROMPT, stdout);
    while ((cmdline = fgets(buf, sizeof(buf), stdin)) != NULL) {
        char **args = split(cmdline, " \n\t");
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            } else if (strcmp(args[0], "echo") == 0 &&
                       strcmp(args[1], "$?") == 0) {
                printf("%d\n", status);
            } else {
                status = exec(args);
            }
        }
        fputs(PROMPT, stdout);
    }
}

int exec(char **args)
{
    int status;
    int pid;

    pid = fork();
    if (pid == 0) {
        // child process
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, "shell: ");
            perror(args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0 ) {
        // error forking
        perror("shell");
        return 1;
    }
    // parent process, fork successful, wait for child to complete
    do {
        waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) & !WIFSIGNALED(status));

    return WEXITSTATUS(status);
}
