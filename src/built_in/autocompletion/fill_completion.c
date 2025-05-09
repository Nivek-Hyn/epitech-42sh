/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** fill_completion
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

void check_is_solo(int nb_rows, completion_t *completion_s, tty_t *tty, int i)
{
    if (nb_rows == 1 && strncmp(completion_s->every_name[i],
        completion_s->typed, strlen(completion_s->typed)) == 0) {
        free(tty->buffer);
        tty->buffer = strdup(completion_s->every_name[i]);
        tty->size = strlen(tty->buffer);
        tty->cursor = tty->size;
    }
    if (nb_rows != 1 && strncmp(completion_s->every_name[i],
        completion_s->typed, strlen(completion_s->typed)) == 0)
        printeur(completion_s->every_name[i], &completion_s->printed);
}

static void change_buff(completion_t *completion_s, tty_t *tty, int i)
{
    free(tty->buffer);
    if (completion_s->typed[strlen(completion_s->typed) - 1] != '/')
        completion_s->typed = strcat(completion_s->typed, "/");
    tty->buffer = strdup(strcat(completion_s->typed,
        completion_s->every_name[i]));
    tty->size = strlen(tty->buffer);
    tty->cursor = tty->size;
}

void print_all_names(completion_t *completion_s, tty_t *tty)
{
    int nb_rows = 0;
    int has_printed = 0;

    for (int i = 0; completion_s->every_name &&
        completion_s->every_name[i]; i++) {
        nb_rows++;
    }
    for (int i = 0; completion_s->every_name &&
        completion_s->every_name[i]; i++) {
        if (nb_rows == 1) {
            change_buff(completion_s, tty, i);
        } else {
            printeur(completion_s->every_name[i], &completion_s->printed);
            has_printed = 1;
        }
    }
    if (has_printed)
        printf("\n");
    completion_s->printed = 0;
}

char *extract_last_word(char *buffer)
{
    char **splitted = my_sepstr(buffer, " ");
    int len = my_tablen((const void **)splitted);
    char *last = NULL;

    if (!splitted || len == 0) {
        my_tabfree((void **)splitted);
        return NULL;
    }
    last = strdup(splitted[len - 1]);
    my_tabfree((void **)splitted);
    return last;
}

static int count_valid_entries(DIR *dir)
{
    struct dirent *entry;
    int count = 0;

    if (!dir)
        return 0;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.')
            count++;
        entry = readdir(dir);
    }
    rewinddir(dir);
    return count;
}

static int fill_entries(DIR *dir, completion_t *completion_s, int count)
{
    struct dirent *entry;
    int index = 0;

    if (!dir || !completion_s)
        return 0;
    completion_s->every_name = malloc(sizeof(char *) * (count + 1));
    if (!completion_s->every_name)
        return 0;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.') {
            completion_s->every_name[index] = strdup(entry->d_name);
            index++;
        }
        entry = readdir(dir);
    }
    completion_s->every_name[index] = NULL;
    return index;
}

int sh_fill_completion_names(DIR *dir, completion_t *completion_s)
{
    int count = count_valid_entries(dir);

    return fill_entries(dir, completion_s, count);
}
