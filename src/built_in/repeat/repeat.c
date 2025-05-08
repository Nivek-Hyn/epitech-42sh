/*
** EPITECH PROJECT, 2025
** repeat
** File description:
** 42sh
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"

int sh_builtin_repeat(shell_data_t *shell_data, char **args)
{
    int count = 0;
    int pid = 0;
    int i = 0;

    if (!args[1] || !args[2]) {
        fprintf(stderr, "repeat: usage: repeat <n> <command>\n");
        return 1;
    }
    count = atoi(args[1]);
    if (count <= 0) {
        fprintf(stderr, "repeat: invalid repeat count: %s\n", args[1]);
        return 1;
    }
    while (i < count) {
        pid = fork();
        if (pid == 0) {
            execvp(args[2], &args[2]);
            perror("execvp");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            return 1;
        } else {
            int status = 0;
            waitpid(pid, &status, 0);
        }
        i++;
    }
    return 0;
}
