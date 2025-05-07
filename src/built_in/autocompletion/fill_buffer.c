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
#include "shell/completion.h"

int fill_buffer(getline_t *gtln_s, char **all_path)
{
    int i = strlen(gtln_s->buff);
    gtln_s->tty->cursor = gtln_s->tty->size;

    for (int j = 0; all_path[j]; j++) {
        if (all_path[j][i] == '\0') {
            write(1, "\n", 1);
            return 1;
        }
        if (j > 0 && all_path[j - 1][i] != all_path[j][i]) {
            printf("La char %c est comparée à %c\n", all_path[j - 1][i], all_path[j][i]);
            return 0;
        }
        if (!all_path[j + 1]) {
            handle_regular_char(all_path[j][i], gtln_s->tty, gtln_s->data);
            j = -1;
            i++;
        }
    }
    return 0;
}

int fill_buffer_slash(getline_t *gtln_s, char **all_path)
{
    int i = 0;
    gtln_s->tty->cursor = gtln_s->tty->size;
    
    handle_regular_char('/', gtln_s->tty, gtln_s->data);
    for (int j = 0; all_path[j]; j++) {
        if (all_path[j][i] == '\0') {
            write(1, "\n", 1);
            return 1;
        }
        if (j > 0 && all_path[j - 1][i] != all_path[j][i])
            return 0;
        if (!all_path[j + 1]) {
            handle_regular_char(all_path[j][i], gtln_s->tty, gtln_s->data);
            j = -1;
            i++;
        }
    }
    return 0;
}