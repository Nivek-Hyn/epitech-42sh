/*
** EPITECH PROJECT, 2025
** history
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "my_printf.h"
#include "utils.h"

static int print_history(shell_usr_data_t *user_data)
{
    if (user_data == NULL)
        return FUNC_FAILED;
    if (user_data->history == NULL)
        return FUNC_FAILED;
    for (int i = 0; user_data->history[i] != NULL; i++)
        my_printf("    %d\t%s\n", i, user_data->history[i]);
    return FUNC_SUCCESS;
}

int sh_builtin_history(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, -1};

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    print_history(shell_data->user_data);
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
