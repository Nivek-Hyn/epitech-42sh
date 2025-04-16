/*
** EPITECH PROJECT, 2025
** history
** File description:
** 42sh
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "shell/config/data.h"
#include "utils.h"

static int write_history_file(FILE *file,
    shell_data_t *shell_data, const char *string)
{
    shell_usr_data_t *user_data = NULL;

    if (shell_data == NULL || string == NULL || file == NULL)
        return FUNC_FAILED;
    user_data = shell_data->user_data;
    fwrite(string, sizeof(char), my_strlen(string), file);
    fwrite("\n", sizeof(char), 1, file);
    if (user_data != NULL) {
        user_data->history = (char **) my_realloc_tab((void **)
            user_data->history, user_data->history_len,
                user_data->history_len + 1, sizeof(char *));
        user_data->history_len++;
    }
    return FUNC_SUCCESS;
}

int sh_write_into_history(shell_data_t *shell_data, const char *string)
{
    char *filepath = NULL;
    FILE *file = NULL;

    if (shell_data == NULL || string == NULL)
        return FUNC_FAILED;
    if (shell_data->user_data == NULL)
        return FUNC_FAILED;
    filepath = my_strcdup(shell_data->user_data->user_homedir,
        "/" SH_HISTORY_FILE);
    if (filepath == NULL)
        return FUNC_FAILED;
    file = fopen(filepath, "a");
    if (file == NULL) {
        free(filepath);
        return FUNC_FAILED;
    }
    write_history_file(file, shell_data, string);
    free(filepath);
    fclose(file);
    return FUNC_SUCCESS;
}
