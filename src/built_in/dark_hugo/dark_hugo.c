/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** dark_hugo
*/

#include "shell/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int sh_builtin_dark_hugo(shell_data_t *shell_data, sh_tasker_t *task)
{
    pid_t pid = fork();

    if (!shell_data || !task)
        return -1;
    if (pid == 0) {
        execlp("cat", "cat", "ascii_art/dark_hugo.txt", NULL);
        perror("execlp");
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
    return 0;
}
