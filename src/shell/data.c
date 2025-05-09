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
#include "my.h"
#include "shell/job.h"

shell_data_t *sh_data_init(char_dict_t *env)
{
    shell_data_t *shell_data = NULL;

    shell_data = malloc(sizeof(shell_data_t));
    if (shell_data == NULL)
        return NULL;
    shell_data->line = NULL;
    shell_data->command_chain = NULL;
    shell_data->tasks = NULL;
    shell_data->env = env;
    shell_data->is_active = TRUE;
    shell_data->user_data = sh_usrdata_init(env);
    shell_data->last_excode = SH_DATA_DEFAULT_EC;
    shell_data->old_pwd = NULL;
    shell_data->pwd = NULL;
    if (shell_data->user_data != NULL)
        shell_data->pwd = shell_data->user_data->user_homedir;
    shell_data->jobs = NULL;
    shell_data->shell_pgid = getpid();
    setpgid(shell_data->shell_pgid, shell_data->shell_pgid);
    return shell_data;
}

void sh_data_purge(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return;
    sh_prsent_destroy(shell_data->command_chain);
    if (shell_data->user_data != NULL) {
        free(shell_data->user_data->user_homedir);
        free(shell_data->user_data->hostname);
        free(shell_data->user_data->user);
        my_chardict_free_ext(shell_data->user_data->aliases);
        my_chardict_free_ext(shell_data->user_data->variables);
        my_tabfree((void **) shell_data->user_data->history);
        free(shell_data->user_data);
    }
    shell_data->tasks = NULL;
    my_chardict_free_ext(shell_data->env);
    free_jobs(shell_data->jobs);
    free(shell_data);
}
