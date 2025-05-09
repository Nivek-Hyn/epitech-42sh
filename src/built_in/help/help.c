/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** help
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell/config/data.h"

int sh_builtin_help(shell_data_t *shell_data, sh_tasker_t *task)
{
    char *filepath = "./src/ascii_art/help_prompt.txt";
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;

    if (!file || !shell_data || !task)
        return FUNC_FAILED;
    while (getline(&line, &len, file) != -1) {
        write(1, line, strlen(line));
    }
    free(line);
    fclose(file);
    return FUNC_SUCCESS;
}
