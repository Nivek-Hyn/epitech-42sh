/*
** EPITECH PROJECT, 2025
** std_pipe
** File description:
** Minishell2
*/

#include <stdio.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/pipes.h"
#include "shell/parser.h"
#include "shell/exec.h"
#include "utils.h"

static int assign_output(sh_tasker_t *task, int fd, char *argument)
{
    if (fd < 0 || fd > 2 || task == NULL || argument == NULL)
        return FUNC_FAILED;
    if (fd == STDIN) {
        task->pipes.stdin_fd = STDIN;
        task->pipes.stdin_fn = argument;
    }
    if (fd == STDOUT) {
        task->pipes.stdout_fd = STDOUT;
        task->pipes.stdout_fn = argument;
    }
    if (fd == STDERR) {
        task->pipes.stderr_fd = STDERR;
        task->pipes.stderr_fn = argument;
    }
    return FUNC_SUCCESS;
}

static int sh_tsk_check_positive_pipe(sh_tasker_t *task, char *shard, fd_t fd,
    char *next_argument)
{
    if (task == NULL || shard == NULL || next_argument == NULL)
        return FUNC_FAILED;
    if (my_strcmp(">", shard) == CMP_EXACT) {
        task->pipes.redir_type = SH_REDIR_RIGHT;
        return assign_output(task, fd, next_argument);
    }
    if (my_strcmp(">>", shard) == CMP_EXACT) {
        task->pipes.redir_type = SH_REDIR_RIGHT_APPEND;
        return assign_output(task, fd, next_argument);
    }
    return FUNC_FAILED;
}

static int sh_tsk_check_negative_pipe(sh_tasker_t *task, char *shard,
    char *next_argument)
{
    if (task == NULL || shard == NULL || next_argument == NULL)
        return FUNC_FAILED;
    if (my_strcmp("<", shard) == CMP_EXACT) {
        task->pipes.redir_type = SH_REDIR_LEFT;
        return assign_output(task, STDIN, next_argument);
    }
    if (my_strcmp("<<", shard) == CMP_EXACT) {
        task->pipes.redir_type = SH_REDIR_LEFT_APPEND;
        return assign_output(task, STDIN, next_argument);
    }
    return FUNC_FAILED;
}

int sh_tsk_intprt_std_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL || next_argument == NULL)
        return FUNC_FAILED;
    if (shard[0] == '0' || shard[0] == '1' || shard[0] == '2') {
        if (shard[1] == '>')
            return sh_tsk_check_positive_pipe(task, &shard[1],
                my_getnbr(shard), next_argument);
        else
            return sh_tsk_check_negative_pipe(task, &shard[1], next_argument);
    }
    if (shard[0] == '>')
        return sh_tsk_check_positive_pipe(task, shard, STDOUT, next_argument);
    return sh_tsk_check_negative_pipe(task, shard, next_argument);
}
