/*
** EPITECH PROJECT, 2025
** execute
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/config/built_in.h"
#include "shell/exec.h"
#include "shell/misc.h"

int (*sh_get_builtin_exec(sh_prsent_t *parser_entry))(shell_data_t *,
    sh_tasker_t *)
{
    char *entry = NULL;

    if (parser_entry == NULL)
        return NULL;
    if (parser_entry->entry == NULL)
        return NULL;
    entry = parser_entry->entry;
    for (int i = 0; sh_builtins[i].command != NULL; i++)
        if (my_strcmp(entry, sh_builtins[i].command) == CMP_EXACT)
            return sh_builtins[i].builtin_f;
    return NULL;
}

int sh_builtin_exec(shell_data_t *shell_data, sh_tasker_t *task)
{
    int (*builtin_f)(shell_data_t *, sh_tasker_t *) = NULL;
    int pipe_fd[2] = {-1, -1};

    if (shell_data == NULL || task == NULL)
        return FUNC_FAILED;
    if (task->pipes.redir_type != SH_REDIR_UNKNOWN) {
        if (pipe(pipe_fd) == FUNC_FAILED)
            return FUNC_FAILED;
        return sh_builtin_exec_sp(task, pipe_fd);
    }
    builtin_f = sh_get_builtin_exec(task->parser_entry);
    if (builtin_f == NULL)
        return FUNC_FAILED;
    return builtin_f(shell_data, task);
}

static int destroy_shell_data(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return FUNC_FAILED;
    sh_shelldata_reset(shell_data);
    sh_data_purge(shell_data);
    return FUNC_FAILED;
}

int sh_builtin_exec_sp(sh_tasker_t *task, int pipe_fd[2])
{
    pid_t fork_result = -1;
    int (*builtin_f)(shell_data_t *, sh_tasker_t *) = NULL;

    if (task == NULL || pipe_fd == NULL)
        return FUNC_FAILED;
    fork_result = fork();
    if (fork_result == FUNC_FAILED)
        return sh_builtin_fail(task->shell_data, EXIT_FAILURE);
    if (fork_result != 0)
        return sh_exec_monitor(task->shell_data, fork_result, FALSE);
    if (task->pipes.redir_type != SH_REDIR_UNKNOWN && pipe_fd != NULL)
        if (sh_exec_redirect(task, pipe_fd) == FUNC_FAILED)
            exit(EXIT_FAILURE);
    builtin_f = sh_get_builtin_exec(task->parser_entry);
    if (builtin_f == NULL)
        return destroy_shell_data(task->shell_data);
    builtin_f(task->shell_data, task);
    destroy_shell_data(task->shell_data);
    exit(EXIT_SUCCESS);
}
