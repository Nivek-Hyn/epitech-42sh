/*
** EPITECH PROJECT, 2025
** get
** File description:
** 42sh
*/

#include <stdlib.h>
#include "my.h"
#include "shell/config/data.h"

static int get_history_id(const char *format)
{
    if (format == NULL)
        return FUNC_FAILED;
    if (IS_NUM(format[0]))
        return atoi(format);
    return my_strlen(format);
}

char *sh_get_history_shard(const char *format, shell_data_t *shell_data)
{
    int id = 0;

    if (shell_data == NULL)
        return NULL;
    if (shell_data->user_data == NULL)
        return NULL;
    if (shell_data->user_data->history == NULL ||
        shell_data->user_data->history_len <= 0)
        return NULL;
    id = get_history_id(format);
    if (id == FUNC_FAILED)
        return NULL;
    if (SH_HIST_LEN(shell_data) - id < 0 ||
        SH_HIST_LEN(shell_data) - id > SH_HIST_LEN(shell_data))
        return NULL;
    return my_strdup(SH_HIST(shell_data)[SH_HIST_LEN(shell_data) - id]);
}
