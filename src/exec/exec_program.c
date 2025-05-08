/*
** EPITECH PROJECT, 2025
** exec_program
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "kill.h"
#include "shell/built_in.h"
#include "shell/shell.h"
#include "shell/env.h"
#include "shell/exec.h"
#include "shell/job.h"
#include "shell/job.h"

static int handle_job(shell_data_t *shell_data, sh_tasker_t *task,
    int fork_result)
{
    if (shell_data == NULL || task == NULL)
        return FUNC_FAILED;
    printf("[%d] %d\n", get_job_by_pid(shell_data, fork_result)->id,
        get_job_by_pid(shell_data, fork_result)->pid);
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}

static int execute_preliminaries(shell_data_t *shell_data, sh_tasker_t *task,
    int pipe_fd[2])
{
    if (shell_data == NULL || task == NULL || pipe_fd == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (task->program == NULL || task->args == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_exec_check_access(task->program, TRUE) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (task->pipes.redir_type != SH_REDIR_UNKNOWN)
        if (pipe(pipe_fd) == FUNC_FAILED)
            return sh_builtin_fail(shell_data, EXIT_FAILURE);
    return FUNC_SUCCESS;
}

int sh_exec_program(shell_data_t *shell_data, sh_tasker_t *task)
{
    int pipe_fd[2] = {-1, -1};
    int fork_result = 0;

    if (execute_preliminaries(shell_data, task, pipe_fd) == FUNC_FAILED)
        return FUNC_FAILED;
    fork_result = fork();
    if (fork_result == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (fork_result == 0)
        sh_exec_execute(task, pipe_fd);
    setpgid(fork_result, fork_result);
    sh_add_job(shell_data, task, fork_result);
    if (task->pipes.background == TRUE)
        return handle_job(shell_data, task, fork_result);
    return sh_exec_monitor(shell_data, fork_result, FALSE);
}
