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
#include "utils.h"

static void consume_next_argument(char *next_argument)
{
    if (next_argument == NULL)
        return;
}

static int override_type(sh_prsent_t *chain, char **shard_ptr)
{
    if (chain == NULL || shard_ptr == NULL)
        return FUNC_FAILED;
    for (; chain != NULL; chain = chain->next) {
        if (&chain->entry == shard_ptr) {
            chain->type = SH_PARSER_COMMAND;
            break;
        }
    }
    return FUNC_SUCCESS;
}

static int patch_task(sh_tasker_t *task)
{
    if (task == NULL)
        return FUNC_FAILED;
    free(task->program);
    free(task->args);
    task->program = my_strdup(sh_get_prsent_index(task->parser_entry, 0));
    task->args = sh_prsent_to_char_tab(task->parser_entry);
    return FUNC_SUCCESS;
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
    free(*shard_ptr);
    override_type(task->parser_entry, shard_ptr);
    if (hist_shard == NULL)
        hist_shard = my_strdup("");
    *shard_ptr = hist_shard;
    patch_task(task);
    consume_next_argument(next_argument);
    return FUNC_SUCCESS;
}
