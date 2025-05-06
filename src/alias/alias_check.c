/*
** EPITECH PROJECT, 2025
** alias_check
** File description:
** libmy
*/

#include "shell/shell.h"
#include "shell/tasker.h"
#include "my.h"
#include <stdlib.h>

static int check_for_aliases(sh_prsent_t **parser_entry, char_dict_t *aliases)
{
    char_dict_t *alias = NULL;
    sh_prsent_t *curr_entry = NULL;
    sh_prsent_t *new_patch = NULL;

    if (parser_entry == NULL)
        return FUNC_FAILED;
    for (curr_entry = *parser_entry; curr_entry != NULL;
        curr_entry = curr_entry->next) {
        alias = my_chardict_find_dict(aliases, (void *) curr_entry->entry,
            my_chardict_find_key);
        if (alias == NULL)
            continue;
        new_patch = sh_parse_string(alias->value);
        sh_parser_override(parser_entry, new_patch,
            &curr_entry->entry);
        curr_entry = new_patch;
    }
    return FUNC_SUCCESS;
}

static char_dict_t *get_alias(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return NULL;
    if (SH_USRDAT(shell_data) == NULL)
        return NULL;
    return SH_USRDAT(shell_data)->aliases;
}

int sh_alias_check(shell_data_t *shell_data)
{
    char_dict_t *aliases = NULL;

    if (shell_data == NULL)
        return FUNC_FAILED;
    aliases = get_alias(shell_data);
    if (aliases == NULL)
        return FUNC_SUCCESS;
    if (check_for_aliases(&shell_data->command_chain, aliases) == FUNC_FAILED)
        return FUNC_FAILED;
    return FUNC_SUCCESS;
}
