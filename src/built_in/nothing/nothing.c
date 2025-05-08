/*
** EPITECH PROJECT, 2025
** nothing
** File description:
** 42sh
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"

static void consume_task(sh_tasker_t *task)
{
    if (task == NULL)
        return;
}

int sh_builtin_nothing(shell_data_t *shell_data, sh_tasker_t *task)
{
    if (shell_data == NULL || task == NULL)
        return FUNC_FAILED;
    consume_task(task);
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
