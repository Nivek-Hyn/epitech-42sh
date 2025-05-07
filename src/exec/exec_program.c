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

void sigtstp_manager(shell_data_t *shell_data, pid_t child_pid, int status)
{
    if (WIFSTOPPED(status)) {
        printf("Suspended\n");
        get_job_by_pid(shell_data, child_pid)->status = SUSPENDED;
    }
    remove_job_by_pid(shell_data, child_pid);
}

static int is_dad(shell_data_t *shell_data, pid_t child_pid)
{
    int status = EXIT_SUCCESS;

    if (shell_data == NULL)
        return FUNC_FAILED;
    if (waitpid(child_pid, &status, WUNTRACED) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE_84);
    sigtstp_manager(shell_data, child_pid, status);
    if (WIFSIGNALED(status)) {
        sh_exec_print_crash(status);
        return sh_builtin_fail(shell_data, status);
    }
    if (WEXITSTATUS(status) == 127)
        return sh_builtin_fail(shell_data, WEXITSTATUS(status));
    return sh_builtin_success(shell_data, WEXITSTATUS(status));
}

static int is_child(sh_tasker_t *task)
{
    char **env = NULL;
    pid_t pid = getpid();

    if (task == NULL) {
        exit(EXIT_FAILURE);
        return FUNC_FAILED;
    }
    setpgid(pid, pid);
    if (task->shell_data != NULL)
        env = sh_env_to_tab(task->shell_data->env);
    if (env == NULL)
        my_putstr_fd("mysh: Cannot convert env\n", STDERR);
    if (execve(task->program, task->args, env) == FUNC_FAILED) {
        if (task->program != NULL)
            sh_exec_print_execerror(task->program, errno);
        exit(EXIT_FAILURE);
        return FUNC_FAILED;
    }
    return FUNC_SUCCESS;
}

int sh_exec_program(shell_data_t *shell_data, sh_tasker_t *task)
{
    int fork_result = 0;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (task->program == NULL || task->args == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    fork_result = fork();
    if (fork_result == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (fork_result == 0)
        is_child(task);
    setpgid(fork_result, fork_result);
    sh_add_job(shell_data, task, fork_result);
    if (task->pipes.background == TRUE) {
        printf("[%d] %d\n", get_job_by_pid(shell_data, fork_result)->id,
            get_job_by_pid(shell_data, fork_result)->pid);
        return sh_builtin_success(shell_data, EXIT_SUCCESS);
    }
    return is_dad(shell_data, fork_result);
}
