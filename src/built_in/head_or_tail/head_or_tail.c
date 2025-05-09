/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** head_or_tail
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell/parser.h"

int sh_builtin_h_or_t(shell_data_t *shell_data, sh_tasker_t *task)
{
    int result = rand() % 2;

    if (!shell_data || !task)
        return -1;
    if (result == 0)
        printf("Pile\n");
    else
        printf("Face\n");
    return 0;
}
