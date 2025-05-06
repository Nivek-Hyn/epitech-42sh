/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** fill_buffer
*/

#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <stdlib.h>
#include "shell/shell.h"
#include "shell/render.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include "shell/shell.h"
#include "shell/env.h"

void fill_buffer(shell_data_t *data, tty_t *tty, char *buff, char **all_path)
{
    int i = strlen(buff);
    tty->cursor = tty->size;

    for (int j = 0; all_path[j]; j++) {
        if (all_path[j][i] == '\0') {
            return;
        }
        if (j > 0 && all_path[j - 1][i] != all_path[j][i])
            return;
        if (!all_path[j + 1]) {
            handle_regular_char(all_path[j][i], tty, data);
            j = -1;
            i++;
        }
    }
}
