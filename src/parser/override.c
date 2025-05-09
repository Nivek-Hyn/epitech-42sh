/*
** EPITECH PROJECT, 2025
** override
** File description:
** Minishell2
*/

#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/parser.h"
#include "utils.h"

int sh_parser_override(sh_prsent_t **chain_ptr, sh_prsent_t *new_patch,
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

void sh_parser_override_var(sh_prsent_t *entry)
{
    if (entry == NULL)
        return;
    if (entry->prev == NULL || entry->type != SH_PARSER_VAR_PIPE)
        return;
    if (entry->prev->type == SH_PARSER_COMMAND)
        entry->type = SH_PARSER_COMMAND;
}
