/*
** EPITECH PROJECT, 2025
** data
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"
#include "shell/env.h"
#include "shell/parser.h"
#include "shell/misc.h"
#include "my.h"

static int load_user_data(shell_usr_data_t *user_data)
{
    char *filepath = NULL;

    if (user_data == NULL)
        return FUNC_FAILED;
    filepath = my_strcdup(user_data->user_homedir, "/" SH_HISTORY_FILE);
    if (filepath == NULL)
        return FUNC_FAILED;
    user_data->history = sh_tabreader(filepath, &user_data->history_len);
    user_data->history_len -= 1;
    free(filepath);
    return FUNC_SUCCESS;
}

shell_usr_data_t *sh_usrdata_init(char_dict_t *env)
{
    shell_usr_data_t *shell_usrdata = NULL;

    shell_usrdata = malloc(sizeof(shell_usr_data_t));
    if (shell_usrdata == NULL)
        return NULL;
    shell_usrdata->user = my_strdup(sh_env_get(env, "USER"));
    shell_usrdata->user_homedir = my_strdup(sh_env_get(env, "HOME"));
    shell_usrdata->hostname = my_strdup(sh_env_get(env, "HOSTNAME"));
    shell_usrdata->path = NULL;
    shell_usrdata->history_len = -1;
    shell_usrdata->history = NULL;
    load_user_data(shell_usrdata);
    return shell_usrdata;
}
