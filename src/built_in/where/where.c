/*
** EPITECH PROJECT, 2025
** where
** File description:
** 42sh
*/

#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <stdio.h>
#include "shell/shell.h"
#include "shell/render.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include "shell/env.h"
#include "shell/completion.h"

static void print_found_path(char **paths, char *cmd)
{
    size_t len;
    char *full;

    for (int i = 0; paths[i]; i++) {
        len = strlen(paths[i]) + strlen(cmd) + 2;
        full = malloc(len);
        if (!full)
            return;
        strcpy(full, paths[i]);
        strcat(full, "/");
        strcat(full, cmd);
        if (access(full, X_OK) == 0) {
            printf("%s\n", full);
            free(full);
        } else
            free(full);
    }
}

static void free_paths(char **paths)
{
    for (int i = 0; paths[i]; i++)
        free(paths[i]);
    free(paths);
}

static char **get_paths_from_env(shell_data_t *shell_data)
{
    char *path = sh_env_get(shell_data->env, "PATH");

    if (!path)
        return NULL;
    return my_sepstr(path, ":");
}

int sh_builtin_where(shell_data_t *shell_data, sh_tasker_t *task)
{
    char **paths = NULL;
    int found = 0;
    char **args = (task != NULL) ? task->args : NULL;

    if (!args[1]) {
        fprintf(stderr, "where: missing argument\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    paths = get_paths_from_env(shell_data);
    if (!paths)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    print_found_path(paths, args[1]);
    found = sh_builtin_fail(shell_data, EXIT_FAILURE);
    free_paths(paths);
    if (found == 0)
        sh_builtin_fail(shell_data, EXIT_FAILURE);
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
