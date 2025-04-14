/*
** EPITECH PROJECT, 2025
** is
** File description:
** Minishell2
*/

#include <stdio.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/parser.h"
#include "shell/pipes.h"
#include "utils.h"

bool_t sh_pipe_is(const char *shard, sh_prsent_type_t type)
{
    if (shard == NULL || type == SH_PARSER_UNKNOWN)
        return FALSE;
    return my_isin(shard, (const char **)
        sh_pipe_info[type].symbol) == TRUE;
}

bool_t sh_pipe_is_redirect(char *shard)
{
    if (shard == NULL)
        return FALSE;
    return my_isin(shard, (const char **)
        sh_pipe_info[SH_PARSER_PIPE].symbol) == TRUE;
}

bool_t sh_pipe_is_stop(char *shard)
{
    if (shard == NULL)
        return FALSE;
    return my_isin(shard, (const char **)
        sh_pipe_info[SH_PARSER_STOP_PIPE].symbol) == TRUE;
}

bool_t sh_pipe_is_background(char *shard)
{
    if (shard == NULL)
        return FALSE;
    return my_isin(shard, (const char **)
        sh_pipe_info[SH_PARSER_BACKGROUND_PIPE].symbol) == TRUE;
}
