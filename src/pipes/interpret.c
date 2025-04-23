/*
** EPITECH PROJECT, 2025
** interpret
** File description:
** Minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/parser.h"
#include "shell/pipes.h"
#include "utils.h"

int sh_pipes_interpret(sh_tasker_t *task, char *shard,
    char *next_argument)
{
    sh_prsent_type_t type = SH_PARSER_UNKNOWN;

    if (task == NULL || shard == NULL || next_argument == NULL)
        return FUNC_FAILED;
    type = sh_pipe_type(shard);
    if (sh_pipe_info[type].tsk_interpret_f != NULL)
        return sh_pipe_info[type].tsk_interpret_f(task,
            shard, next_argument);
    return FUNC_SUCCESS;
}
