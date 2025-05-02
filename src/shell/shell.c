/*
** EPITECH PROJECT, 2025
** shell
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/render.h"
#include "shell/built_in.h"
#include "shell/parser.h"
#include "shell/tasker.h"
#include "utils.h"

void sh_shelldata_reset(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return;
    sh_tasker_destroy(shell_data->tasks);
    sh_prsent_destroy(shell_data->command_chain);
    shell_data->tasks = NULL;
    shell_data->command_chain = NULL;
    free(shell_data->line);
    shell_data->line = NULL;
}

static int shell_tty_mode(shell_data_t *shell_data)
{
    int exec_success = FUNC_SUCCESS;

    if (shell_data == NULL)
        return FUNC_FAILED;
    while (sh_parse_entry(shell_data) != FUNC_FAILED
        && exec_success == FUNC_SUCCESS) {
        sh_build_tasker(shell_data);
        exec_success = sh_tasker_execute(shell_data);
        sh_shelldata_reset(shell_data);
        shell_data->command_chain = NULL;
    }
    sh_shelldata_reset(shell_data);
    return FUNC_SUCCESS;
}

static int parse_data(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return FUNC_FAILED;
    if (sh_parse_entry(shell_data) == FUNC_FAILED) {
        my_putstr("exit\n");
        return FUNC_FAILED;
    }
    if (shell_data->last_excode == EXIT_FAILURE)
        return FUNC_SEMFAIL;
    sh_build_tasker(shell_data);
    sh_write_into_history(shell_data, shell_data->line);
    sh_tasker_execute(shell_data);
    return FUNC_SUCCESS;
}

int shell(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return FUNC_FAILED;
    if (isatty(STDIN) == FALSE)
        return shell_tty_mode(shell_data);
    do {
        sh_shelldata_reset(shell_data);
        sh_render_window(shell_data);
        shell_data->last_excode = SH_DATA_DEFAULT_EC;
        if (parse_data(shell_data) == FUNC_FAILED)
            shell_data->is_active = FALSE;
    } while (shell_data->is_active);
    sh_shelldata_reset(shell_data);
    return FUNC_SUCCESS;
}

int shell_auto(void)
{
    return FUNC_SUCCESS;
}
