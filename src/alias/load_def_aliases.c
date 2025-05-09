/*
** EPITECH PROJECT, 2025
** load_def_aliases
** File description:
** 42sh
*/

#include "shell/alias.h"
#include "my.h"

char_dict_t *sh_load_def_aliases(void)
{
    char_dict_t *dict = NULL;
    char_dict_t *new_chain = NULL;

    for (int i = 0; sh_default_aliases[i].base != NULL; i++) {
        new_chain = my_chardict_create(my_strdup(sh_default_aliases[i].base),
            my_strdup(sh_default_aliases[i].target));
        if (new_chain == NULL)
            return dict;
        if (my_chardict_chain(&dict, new_chain) == FUNC_FAILED)
            return dict;
    }
    return dict;
}
