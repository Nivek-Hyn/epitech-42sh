/*
** EPITECH PROJECT, 2025
** alias
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "my_printf.h"
#include "utils.h"

static int print_aliases(shell_data_t *shell_data)
{
    char_dict_t *dict = NULL;

    if (shell_data == NULL)
        return FUNC_FAILED;
    if (SH_USRDAT(shell_data) == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (SH_USRDAT(shell_data)->aliases == NULL) {
        my_putstr_fd("alias: No aliases to print.\n", STDERR);
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    for (dict = SH_USRDAT(shell_data)->aliases; dict != NULL;
        dict = dict->next) {
        my_printf("Command: %s\nAlias: %s\n", dict->key, dict->value);
        if (dict->next != NULL)
            my_putstr("----- NEXT -----\n");
    }
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}

static char *dup_wout_quotes(char *data)
{
    char *end_ptr = NULL;

    if (data == NULL)
        return NULL;
    if (data[0] != '\'' || my_strlen(data) < 2)
        return NULL;
    data = &data[1];
    for (int i = 0; data[i] != '\0'; i++)
        if (data[i] == '\'' && data[i + 1] == '\0') {
            end_ptr = &data[i];
            break;
        }
    if (end_ptr == NULL)
        return NULL;
    return my_strptrdup(data, end_ptr);
}

static int insert_alias(char *data[2], char_dict_t **aliases)
{
    char *value = NULL;

    if (data == NULL || aliases == NULL)
        return FUNC_FAILED;
    value = dup_wout_quotes(data[1]);
    if (value == NULL)
        return FUNC_FAILED;
    if (*aliases == NULL) {
        *aliases = my_chardict_create(my_strdup(data[0]), value);
        if (*aliases == NULL) {
            free(value);
            return FUNC_FAILED;
        }
        return FUNC_SUCCESS;
    }
    return my_chardict_set(*aliases, data[0], value, TRUE);
}

static int create_alias(const char *string, shell_usr_data_t *usr_data)
{
    char **data = NULL;

    if (string == NULL || usr_data == NULL)
        return FUNC_FAILED;
    data = my_sepstr(string, "=");
    if (data == NULL)
        return FUNC_FAILED;
    if (my_tablen((const void **) data) != 2) {
        my_tabfree((void **) data);
        return FUNC_FAILED;
    }
    if (insert_alias(data, &usr_data->aliases) == FUNC_FAILED) {
        my_tabfree((void **) data);
        return FUNC_FAILED;
    }
    my_tabfree((void **) data);
    return FUNC_SUCCESS;
}

int sh_builtin_alias(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {1, -1};
    char *argument = NULL;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    argument = sh_prsent_to_char_ptr(
        sh_get_prsent_obj_index(task->parser_entry, 1));
    if (my_strcmp(argument, "--show") == CMP_EXACT) {
        free(argument);
        return print_aliases(shell_data);
    }
    if (create_alias(argument, SH_USRDAT(shell_data)) == FUNC_FAILED) {
        free(argument);
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    free(argument);
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
