/*
** EPITECH PROJECT, 2025
** history
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "my_printf.h"
#include "utils.h"
#include "shell/env.h"
#include "shell/parser.h"
#include "shell/misc.h"

static int new_history(shell_usr_data_t *user_data, char *filepath)
{
    user_data->history = sh_tabreader(filepath, &user_data->history_len);
    user_data->history_len -= 1;
    if (user_data->history == NULL) {
        user_data->history = malloc(sizeof(char *) * 1);
        user_data->history[0] = NULL;
        user_data->history_len = 0;
    }
    free(filepath);
    return FUNC_SUCCESS;
}

int sh_builtin_clear_history(shell_data_t *shell_data, sh_tasker_t *task)
{
    shell_usr_data_t *user_data = shell_data->user_data;
    char *filepath = my_strcdup(user_data->user_homedir, "/" SH_HISTORY_FILE);

    if (filepath == NULL || task == NULL)
        return FUNC_FAILED;
    if (remove(filepath) == 0) {
        printf("History cleared successfully.\n");
    } else {
        printf("Error: Unable to erase your history file.\n");
        return FUNC_FAILED;
    }
    my_tabfree((void **)user_data->history);
    return new_history(user_data, filepath);
}
