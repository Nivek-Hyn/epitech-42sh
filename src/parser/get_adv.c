/*
** EPITECH PROJECT, 2025
** get_adv
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell/parser.h"
#include "getline.h"
#include "my.h"
#include "utils.h"

sh_prsent_t *sh_get_prsent_obj_index(sh_prsent_t *chain, int index)
{
    int curr_index = 0;

    for (; chain != NULL; chain = chain->next) {
        if (my_strcmp(chain->entry, "") == CMP_EXACT)
            continue;
        if (curr_index == index && sh_parser_is_anypipe(chain) == FALSE)
            return chain;
        if (sh_parser_is_anypipe(chain) == TRUE)
            return NULL;
        curr_index++;
    }
    return NULL;
}
