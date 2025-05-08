/*
** EPITECH PROJECT, 2025
** fg
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"

int sh_builtin_fg(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, 1};

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    my_putstr("[WIP]: Foreground Activated!\n");
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
