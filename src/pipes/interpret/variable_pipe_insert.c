/*
** EPITECH PROJECT, 2025
** std_pipe
** File description:
** Minishell2
*/

#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/pipes.h"
#include "shell/parser.h"
#include "shell/tasker.h"
#include "utils.h"

static void consume_next_argument(char *next_argument)
{
    if (next_argument == NULL)
        return;
}

static char *get_variable(shell_data_t *shell_data, char *shard)
{
    char_dict_t *dict = NULL;
    shell_usr_data_t *usr_data = (shell_data != NULL) ? SH_USRDAT(shell_data)
        : NULL;

    if (shell_data == NULL || shard == NULL)
        return NULL;
    if (usr_data == NULL || shard[0] == '\0')
        return NULL;
    shard++;
    if (my_str_isupperprintable(shard) == TRUE)
        dict = my_chardict_find_dict(shell_data->env, (void *) shard,
            my_chardict_find_key);
    if (my_str_islowerprintable(shard) == TRUE)
        dict = my_chardict_find_dict(usr_data->variables, (void *) shard,
            my_chardict_find_key);
    return (dict != NULL) ? dict->value : NULL;
}

static sh_prsent_t *get_pipe_parser_ent(sh_tasker_t *task, const char *shard)
{
    sh_prsent_t *curr_ent = NULL;

    if (task == NULL)
        return NULL;
    for (curr_ent = task->parser_entry; curr_ent != NULL;
        curr_ent = curr_ent->next) {
            if (curr_ent->type == SH_PARSER_VAR_INSERT_PIPE &&
                my_strcmp(curr_ent->entry, shard) == CMP_EXACT)
                return curr_ent;
        }
    return NULL;
}

int sh_tsk_intprt_var_pipe_insert(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    sh_prsent_t *entry = NULL;
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;
    char *variable = NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL)
        return FUNC_FAILED;
    entry = get_pipe_parser_ent(task, shard);
    variable = get_variable(task->shell_data, shard);
    if (variable == NULL || my_strcmp(shard, variable) == CMP_EXACT)
        entry->type = SH_PARSER_COMMAND;
    else
        if (sh_parser_override(&task->parser_entry, sh_parse_string(variable),
            shard_ptr) == FUNC_FAILED)
            return FUNC_FAILED;
    sh_tasker_patch(task);
    consume_next_argument(next_argument);
    return FUNC_SUCCESS;
}
