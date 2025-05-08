/*
** EPITECH PROJECT, 2025
** sh_is
** File description:
** Minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/parser.h"
#include "shell/pipes.h"
#include "utils.h"

bool_t sh_parser_is_spipe(sh_prsent_t *entry)
{
    if (entry == NULL)
        return FALSE;
    if (entry->type == SH_PARSER_STOP_PIPE)
        return TRUE;
    return FALSE;
}

bool_t sh_parser_is_anypipe(sh_prsent_t *entry)
{
    if (entry == NULL)
        return FALSE;
    for (int i = 0; sh_pipe_info[i].type != SH_PARSER_UNKNOWN; i++) {
        if (entry->type == sh_pipe_info[i].type)
            return TRUE;
    }
    return FALSE;
}

bool_t sh_char_is_sep(char chr)
{
    if (chr == ' ' || chr == '\t' || chr == ';' || chr == '&')
        return TRUE;
    return FALSE;
}

bool_t sh_char_is_sep_sp(char chr)
{
    if (chr == ';' || chr == '&')
        return TRUE;
    return FALSE;
}
