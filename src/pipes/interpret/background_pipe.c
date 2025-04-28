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
#include "utils.h"

static void consume_argument_shard(char *next_argument, char *shard)
{
    if (next_argument == NULL || shard == NULL)
        return;
}

int sh_tsk_intprt_bg_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL)
        return FUNC_FAILED;
    consume_argument_shard(next_argument, shard);
    task->pipes.background = TRUE;
    return FUNC_SUCCESS;
}
