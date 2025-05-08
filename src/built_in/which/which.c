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

static int print_command_path(char **paths, char *cmd)
{
    size_t len;
    char *full_path;

    for (int i = 0; paths[i]; i++) {
        len = strlen(paths[i]) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (!full_path)
            return 1;
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            free(full_path);
            return 0;
        }
        free(full_path);
    }
    return 1;
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

int sh_builtin_which(shell_data_t *shell_data, char **args)
{
    char **paths = NULL;

    if (!args[1]) {
        fprintf(stderr, "which: missing argument\n");
        return 1;
    }
    paths = get_paths_from_env(shell_data);
    if (!paths)
        return 1;
    if (print_command_path(paths, args[1]) == 0) {
        free_paths(paths);
        return 0;
    }
    free_paths(paths);
    printf("%s: Command not found.\n", args[1]);
    return 1;
}
