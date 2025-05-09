/*
** EPITECH PROJECT, 2025
** pipe_consume
** File description:
** minishell2
*/

#include <stdio.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/parser.h"
#include "shell/tasker.h"
#include "shell/exec.h"
#include "shell/pipes.h"

int sh_p_pipe_consume(sh_tasker_t *tasker, sh_prsent_t **parser_ent)
{
    sh_prsent_t *curr_ent = NULL;
    sh_tasker_t *new_task = NULL;

    if (tasker == NULL || parser_ent == NULL)
        return FUNC_FAILED;
    for (curr_ent = *parser_ent; curr_ent != NULL &&
        sh_parser_is_spipe(curr_ent) == FALSE; curr_ent = curr_ent->next) {
        if (curr_ent->type != SH_PARSER_PROG_PIPE)
            continue;
        new_task = sh_tasker_create(tasker->shell_data, curr_ent->next);
        if (new_task == NULL)
            return FUNC_FAILED;
        new_task->exec_fnc = sh_exec_program_ppipe;
        tasker->exec_fnc = sh_exec_program_ppipe;
        sh_tasker_chain_ppipe(&tasker->prog_pipes, new_task);
    }
    return FUNC_SUCCESS;
}

static bool_t reset_pipes(sh_prsent_type_t type)
{
    switch (type) {
        case SH_PARSER_HISTORY_PIPE:
        case SH_PARSER_GLOBBING_PIPE:
        case SH_PARSER_VAR_INSERT_PIPE:
            return TRUE;
        default:
            return FALSE;
    }
}

static int interpret_pipe(sh_tasker_t *tasker, sh_prsent_t **entry_ptr)
{
    sh_prsent_type_t type = SH_PARSER_UNKNOWN;
    sh_prsent_t *curr_ent = (entry_ptr != NULL) ? *entry_ptr : NULL;

    if (tasker == NULL || entry_ptr == NULL || curr_ent == NULL)
        return FUNC_FAILED;
    type = curr_ent->type;
    if (sh_pipes_interpret(tasker, &curr_ent->entry, curr_ent->next
        != NULL ? curr_ent->next->entry : NULL) == FUNC_FAILED)
        return FUNC_FAILED;
    if (reset_pipes(type) == TRUE)
        *entry_ptr = tasker->parser_entry;
    return FUNC_SUCCESS;
}

int sh_pipe_consume(sh_tasker_t *tasker, sh_prsent_t **parser_ent)
{
    sh_prsent_t *curr_ent = NULL;

    if (tasker == NULL || parser_ent == NULL)
        return FUNC_FAILED;
    if (sh_p_pipe_consume(tasker, parser_ent) == FUNC_FAILED)
        return FUNC_FAILED;
    for (curr_ent = *parser_ent; curr_ent != NULL &&
        sh_parser_is_spipe(curr_ent) == FALSE; curr_ent = curr_ent->next) {
        if (curr_ent->type == SH_PARSER_COMMAND)
            continue;
        if (interpret_pipe(tasker, &curr_ent) == FUNC_FAILED)
            return FUNC_FAILED;
        if (curr_ent == NULL)
            break;
        if (curr_ent->type == SH_PARSER_BACKGROUND_PIPE ||
            curr_ent->type == SH_PARSER_VAR_PIPE)
            break;
        *parser_ent = curr_ent->next != NULL ? curr_ent->next->next : NULL;
    }
    return FUNC_SUCCESS;
}
