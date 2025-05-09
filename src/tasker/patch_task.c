/*
** EPITECH PROJECT, 2025
** patch_task
** File description:
** Minishell2
*/

#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/parser.h"
#include "utils.h"

int sh_tasker_patch(sh_tasker_t *task)
{
    if (task == NULL)
        return FUNC_FAILED;
    free(task->program);
    my_tabfree((void **) task->args);
    if (task->shell_data != NULL) {
        free(task->shell_data->line);
        task->shell_data->line = sh_prsent_to_char_ptr(task->parser_entry);
        if (task->shell_data->tasks != NULL)
            task->shell_data->command_chain =
                task->shell_data->tasks->parser_entry;
    }
    task->program = my_strdup(sh_get_prsent_index(task->parser_entry, 0));
    task->args = sh_prsent_to_char_tab(task->parser_entry);
    return FUNC_SUCCESS;
}
