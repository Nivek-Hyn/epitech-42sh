/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** dark_hugo
*/

#include "shell/parser.h"
#include "shell/built_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int sh_builtin_dark_hugo(shell_data_t *shell_data, sh_tasker_t *task)
{
    char *filepath = "./src/ascii_art/dark_hugo.txt";
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;

    if (!shell_data || !task)
        return FUNC_FAILED;
    if (!file)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    while (getline(&line, &len, file) != FUNC_FAILED) {
        write(1, line, strlen(line));
    }
    free(line);
    fclose(file);
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
