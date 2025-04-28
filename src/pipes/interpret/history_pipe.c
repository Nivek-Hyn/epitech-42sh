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

static int override_parser(sh_prsent_t **chain_ptr, sh_prsent_t *new_patch,
    char **shard_ptr)
{
    sh_prsent_t *chain = (chain_ptr != NULL) ? *chain_ptr : NULL;
    sh_prsent_t *last_patch = new_patch;
    sh_prsent_t *prev_chain = NULL;

    if (chain == NULL || new_patch == NULL || shard_ptr == NULL)
        return FUNC_FAILED;
    for (; last_patch->next != NULL; last_patch = last_patch->next);
    for (; chain != NULL; chain = chain->next) {
        if (&chain->entry == shard_ptr && prev_chain != NULL)
            prev_chain->next = new_patch;
        if (&chain->entry == shard_ptr) {
            chain->type = SH_PARSER_COMMAND;
            last_patch->next = chain->next;
            sh_prsent_free(chain);
            *chain_ptr = (chain == *chain_ptr) ? new_patch : *chain_ptr;
            break;
        }
        prev_chain = chain;
    }
    return FUNC_SUCCESS;
}

static int patch_task(sh_tasker_t *task)
{
    if (task == NULL)
        return FUNC_FAILED;
    free(task->program);
    my_tabfree((void **) task->args);
    if (task->shell_data != NULL) {
        free(task->shell_data->line);
        task->shell_data->line = sh_prsent_to_char_ptr(task->parser_entry);
        task->shell_data->command_chain = task->parser_entry;
    }
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
    if (hist_shard == NULL)
        hist_shard = my_strdup("");
    override_parser(&task->parser_entry, sh_parse_string(hist_shard),
        shard_ptr);
    free(hist_shard);
    patch_task(task);
    consume_next_argument(next_argument);
    return FUNC_SUCCESS;
}
