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
        }
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

int sh_builtin_where(shell_data_t *shell_data, char **args)
{
    char **paths = NULL;
    int found = 0;

    if (!args[1]) {
        fprintf(stderr, "where: missing argument\n");
        return 1;
    }
    paths = get_paths_from_env(shell_data);
    if (!paths)
        return 1;
    print_found_path(paths, args[1]);
    found = 1;
    free_paths(paths);
    return found ? 0 : 1;
}
