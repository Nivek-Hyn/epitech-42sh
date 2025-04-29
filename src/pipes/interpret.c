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

int sh_pipes_interpret(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;
    sh_prsent_type_t type = SH_PARSER_UNKNOWN;

    if (task == NULL || shard_ptr == NULL || shard == NULL)
        return FUNC_FAILED;
    type = sh_pipe_type(shard);
    if (sh_pipe_info[type].tsk_interpret_f != NULL)
        return sh_pipe_info[type].tsk_interpret_f(task,
            shard_ptr, next_argument);
    return FUNC_SUCCESS;
}
