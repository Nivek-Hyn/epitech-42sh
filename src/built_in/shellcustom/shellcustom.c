/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** shellcustom
*/

#include <stdio.h>
#include <sys/wait.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/env.h"
#include "utils.h"

int sh_builtin_shellcustom(shell_data_t *shell_data, sh_tasker_t *task)
{
    pid_t pid = fork();

    if (!shell_data || !task)
        return FUNC_FAILED;
    if (pid == 0) {
        execlp("cat", "cat", "./src/ascii_art/rip_shellcustom.txt", NULL);
        perror("execlp");
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
