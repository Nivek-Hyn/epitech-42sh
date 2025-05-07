/*
** EPITECH PROJECT, 2025
** std_pipe
** File description:
** Minishell2
*/

#include <stdlib.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/pipes.h"
#include "shell/parser.h"
#include "utils.h"

static void consume_argument(char *next_argument)
{
    if (next_argument == NULL)
        return;
}

static char **generate_var(const char *shard)
{
    char **output = NULL;
    char *equal_ptr = NULL;

    if (shard == NULL)
        return NULL;
    equal_ptr = my_strchr(shard, '=');
    if (equal_ptr == NULL)
        return NULL;
    output = malloc(sizeof(char *) * 3);
    if (output == NULL)
        return NULL;
    output[0] = my_strptrdup(shard, equal_ptr);
    output[1] = NULL;
    output[2] = NULL;
    if (equal_ptr[0] != '\0')
        output[1] = my_strdup(&equal_ptr[1]);
    return output;
}

static int insert_into_varsdict(shell_usr_data_t *usr_data, const char *key,
    const char *value)
{
    if (usr_data == NULL || key == NULL || value == NULL)
        return FUNC_FAILED;
    if (usr_data->variables == NULL) {
        usr_data->variables = my_chardict_create(my_strdup(key),
            my_strdup(value));
        if (usr_data->variables == NULL)
            return FUNC_FAILED;
        return FUNC_SUCCESS;
    }
    return my_chardict_set(usr_data->variables, (char *) key,
        my_strdup(value), TRUE);
}

static int alter_task(sh_tasker_t *task)
{
    char *ref_program[] = {"nothing", NULL};

    if (task == NULL)
        return FUNC_FAILED;
    free(task->program);
    task->program = my_strdup("nothing");
    my_tabfree((void **) task->args);
    task->args = my_tabdup(ref_program);
    if (task->parser_entry != NULL) {
        free(task->parser_entry->entry);
        task->parser_entry->entry = my_strdup("nothing");
    }
    task->exec_fnc = sh_builtin_exec;
    return FUNC_SUCCESS;
}

int sh_tsk_intprt_var_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    shell_data_t *shell_data = NULL;
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;
    char **var = NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL)
        return FUNC_FAILED;
    shell_data = task->shell_data;
    var = generate_var(shard);
    if (var == NULL)
        return FUNC_FAILED;
    if (insert_into_varsdict(SH_USRDAT(shell_data), var[0], var[1])
        == FUNC_FAILED) {
        my_tabfree((void **) var);
        return FUNC_FAILED;
    }
    my_tabfree((void **) var);
    alter_task(task);
    consume_argument(next_argument);
    return FUNC_SUCCESS;
}
