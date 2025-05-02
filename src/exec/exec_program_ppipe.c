/*
** EPITECH PROJECT, 2025
** exec_program_pipe
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
#include "shell/tasker.h"
#include "shell/env.h"
#include "shell/misc.h"
#include "shell/exec.h"
#include "shell/pipes.h"

static int assign_pipes(int **pipesfd, int iter)
{
    if (pipesfd == NULL || iter < 0)
        return FUNC_FAILED;
    if (pipesfd[iter] == NULL)
        return FUNC_FAILED;
    if (iter > 0)
        if (dup2(pipesfd[iter][0], STDIN_FILENO) == FUNC_FAILED)
            return FUNC_FAILED;
    if (pipesfd[iter + 1] != NULL)
        if (dup2(pipesfd[iter + 1][1], STDOUT_FILENO) == FUNC_FAILED)
            return FUNC_FAILED;
    sh_pipesfd_close_all(pipesfd);
    return FUNC_SUCCESS;
}

static int check_commands(sh_tasker_t *task)
{
    int status = FUNC_SUCCESS;
    char *path_str = NULL;

    if (task == NULL)
        return FUNC_FAILED;
    for (; task != NULL; task = task->prog_pipes) {
        path_str = my_strdup(sh_env_get(task->shell_data->env, "PATH"));
        if (sh_is_apart_of_path(path_str,
            task) == FUNC_SEMFAIL)
            status = FUNC_FAILED;
        free(path_str);
        if (sh_exec_check_access(task->program) == FUNC_FAILED)
            status = FUNC_FAILED;
    }
    return status;
}

static int is_child(sh_tasker_t *task, int **pipesfd, int iter)
{
    if (task == NULL || pipesfd == NULL || iter < 0)
        exit(EXIT_FAILURE);
    if (assign_pipes(pipesfd, iter) == FUNC_FAILED) {
        sh_pipesfd_close_all(pipesfd);
        exit(EXIT_FAILURE);
    }
    return sh_exec_execute(task, NULL);
}

static int create_children(sh_tasker_t *task, int **pipesfd)
{
    if (task == NULL || pipesfd == NULL) {
        sh_pipesfd_close_free(pipesfd);
        return FUNC_FAILED;
    }
    for (int i = 0; pipesfd[i] != NULL; i++) {
        pipesfd[i][2] = fork();
        if (pipesfd[i][2] == FUNC_FAILED) {
            sh_pipesfd_close_free(pipesfd);
            return FUNC_FAILED;
        }
        if (pipesfd[i][2] == 0)
            is_child(sh_tasker_get_ptask(task, i), pipesfd, i);
        if (pipesfd[i + 1] == NULL)
            sh_pipesfd_close_all(pipesfd);
    }
    return FUNC_SUCCESS;
}

int sh_exec_program_ppipe(shell_data_t *shell_data, sh_tasker_t *task)
{
    int **pipefd = NULL;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, 1);
    if (check_commands(task) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, 1);
    pipefd = sh_pipesfd_generate(task);
    if (pipefd == NULL)
        return sh_builtin_fail(shell_data, 1);
    if (create_children(task, pipefd) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, 1);
    for (int i = 0; pipefd[i] != NULL; i++)
        if (sh_exec_monitor(shell_data, pipefd[i][2], TRUE) == FUNC_FAILED) {
            sh_pipesfd_close_free(pipefd);
            return FUNC_FAILED;
        }
    sh_pipesfd_free(pipefd);
    return FUNC_SUCCESS;
}
