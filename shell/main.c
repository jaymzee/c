#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "string.h"

#define PROMPT "$ "

int status;

int shell_execute(char **args);
int shell_launch(char **args);
int bltin_cd(char **args);
int bltin_echo(char **args);
int bltin_exit(char **args);
int bltin_help(char **args);

char *builtin_str[] = {
    "cd",
    "echo",
    "exit",
    "help"
};

int (*builtin_func[])(char **args) = {
    bltin_cd,
    bltin_echo,
    bltin_exit,
    bltin_help
};

#define NUM_OF_BUILTINS (sizeof(builtin_str)/sizeof(char *))

int main(int argc, char *argv[])
{
    char buf[256], *cmdline;

    fputs(PROMPT, stdout);
    while ((cmdline = fgets(buf, sizeof(buf), stdin)) != NULL) {
        char **args = split(cmdline, " \n\t");
        status = shell_execute(args);
        fputs(PROMPT, stdout);
    }
}

int shell_execute(char **args)
{
    if (args[0] == NULL) {
        return 1;
    }
    for (int i = 0; i < NUM_OF_BUILTINS; i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return builtin_func[i](args);
        }
    }
    return shell_launch(args);
}

int shell_launch(char **args)
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

int bltin_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell: cd: argument expected\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 0;
}

int bltin_echo(char **args)
{
    if (strcmp(args[1], "$?") == 0) {
        printf("%d\n", status);
    } else {
        // normal echo
        for (char **ptr = args; *ptr != NULL; ptr++) {
            printf("%s ", *ptr);
        }
        printf("\n");
    }
}

int bltin_exit(char **args)
{
    exit(0);
}

int bltin_help(char **args)
{
    printf("help not available\n");
    return 0;
}
