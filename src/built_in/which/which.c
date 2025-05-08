/*
** EPITECH PROJECT, 2025
** where
** File description:
** 42sh
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell/shell.h"

int sh_builtin_which(shell_data_t *shell_data, char **args)
{
    char **paths = NULL;
    char *path = NULL;
    int i = 0;
    size_t len;
    char *full;

    if (!args[1]) {
        fprintf(stderr, "which: missing argument\n");
        return 1;
    }
    if (sh_builtin_get(args[1]) != NULL) {
        printf("%s: shell built-in command.\n", args[1]);
        return 0;
    }
    path = sh_env_get(shell_data->env, "PATH");
    if (!path)
        return 1;
    paths = my_sepstr(path, ":");
    if (!paths)
        return 1;
    while (paths[i]) {
        len = strlen(paths[i]) + strlen(args[1]) + 2;
        full = malloc(len);
        if (!full) {
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return 1;
        }
        strcpy(full, paths[i]);
        strcat(full, "/");
        strcat(full, args[1]);
        if (access(full, X_OK) == 0) {
            printf("%s\n", full);
            free(full);
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return 0;
        }
        free(full);
        i++;
    }
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);
    printf("%s: Command not found.\n", args[1]);
    return 1;
}
