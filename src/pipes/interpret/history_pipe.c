/*
** EPITECH PROJECT, 2025
** std_pipe
** File description:
** Minishell2
*/

#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/pipes.h"
#include "shell/parser.h"
#include "shell/tasker.h"
#include "utils.h"

static void consume_next_argument(char *next_argument)
{
    if (next_argument == NULL)
        return;
}

int sh_tsk_intprt_history_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;
    char *hist_shard = NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL)
        return FUNC_FAILED;
    hist_shard = sh_get_history_shard(shard, task->shell_data);
    if (hist_shard == NULL)
        hist_shard = my_strdup("");
    sh_parser_override(&task->parser_entry, sh_parse_string(hist_shard),
        shard_ptr);
    free(hist_shard);
    sh_tasker_patch(task);
    consume_next_argument(next_argument);
    return FUNC_SUCCESS;
}
