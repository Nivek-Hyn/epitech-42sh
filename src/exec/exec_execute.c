/*
** EPITECH PROJECT, 2025
** exec_execute
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "shell/built_in.h"
#include "shell/shell.h"
#include "shell/env.h"
#include "shell/misc.h"
#include "shell/exec.h"
#include "shell/job.h"

int sh_exec_monitor(shell_data_t *shell_data, pid_t child_pid,
    bool_t keep_lastexcode)
{
    int status = EXIT_SUCCESS;

    if (shell_data == NULL)
        return FUNC_FAILED;
    if (waitpid(child_pid, &status, WUNTRACED) == FUNC_FAILED)
    if (waitpid(child_pid, &status, WUNTRACED) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE_84);
    sh_sigtstp_manager(shell_data, child_pid, status);
    sh_sigtstp_manager(shell_data, child_pid, status);
    if (WIFSIGNALED(status)) {
        sh_exec_print_crash(status);
        return sh_builtin_fail(shell_data, status);
    }
    if (keep_lastexcode == TRUE)
        return sh_builtin_success(shell_data, shell_data->last_excode == 0 ?
            WEXITSTATUS(status) : shell_data->last_excode);
    if (WEXITSTATUS(status) != EXIT_SUCCESS)
        return sh_builtin_fail(shell_data, WEXITSTATUS(status));
    return sh_builtin_success(shell_data, WEXITSTATUS(status));
}

static void teardown_exec_error(sh_tasker_t *task, char **env)
{
    if (task == NULL)
        return;
    if (task->program != NULL)
        sh_exec_print_execerror(task->program, errno);
    my_tabfree((void **) env);
    sh_shelldata_destroy(task->shell_data);
}

int sh_exec_execute(sh_tasker_t *task, int pipe_fd[2])
{
    char **env = NULL;

    if (task == NULL)
        exit(EXIT_FAILURE);
    if (task->pipes.redir_type != SH_REDIR_UNKNOWN && pipe_fd != NULL)
        if (sh_exec_redirect(task, pipe_fd) == FUNC_FAILED)
            exit(EXIT_FAILURE);
    if (task->shell_data != NULL)
        env = sh_env_to_tab(task->shell_data->env);
    if (env == NULL)
        my_putstr_fd("mysh: Cannot convert env\n", STDERR);
    if (execve(task->program, task->args, env) == FUNC_FAILED) {
        teardown_exec_error(task, env);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    return FUNC_SUCCESS;
}
