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

static char *build_new_typed(char *typed)
{
    char *new_typed = NULL;
    size_t len = strlen(typed);

    if (typed[len - 1] != '/') {
        new_typed = malloc(len + 2);
        if (!new_typed)
            return NULL;
        strcpy(new_typed, typed);
        strcat(new_typed, "/");
    } else {
        new_typed = strdup(typed);
    }
    return new_typed;
}

char *build_final_path(completion_t *completion_s, int i)
{
    char *new_typed = build_new_typed(completion_s->typed);
    char *final_path = NULL;

    if (!new_typed)
        return NULL;
    final_path = malloc(strlen(new_typed) +
        strlen(completion_s->every_name[i]) + 1);
    if (!final_path) {
        free(new_typed);
        return NULL;
    }
    strcpy(final_path, new_typed);
    strcat(final_path, completion_s->every_name[i]);
    free(new_typed);
    return final_path;
}

static void change_buff(completion_t *completion_s, tty_t *tty, int i)
{
    char *final_path = NULL;

    if (!completion_s || !tty || !completion_s->typed ||
        !completion_s->every_name || !completion_s->every_name[i])
        return;
    final_path = build_final_path(completion_s, i);
    if (!final_path)
        return;
    free(tty->buffer);
    tty->buffer = strdup(final_path);
    tty->size = strlen(tty->buffer);
    tty->cursor = tty->size;
    free(final_path);
}

void print_all_names(completion_t *completion_s, tty_t *tty)
{
    int nb_rows = 0;
    int has_printed = 0;

    if (!completion_s || !tty || !completion_s->every_name)
        return;
    for (int i = 0; completion_s->every_name[i]; i++)
        nb_rows++;
    for (int i = 0; completion_s->every_name[i]; i++) {
        if (nb_rows == 1)
            change_buff(completion_s, tty, i);
        else {
            printeur(completion_s->every_name[i], &completion_s->printed);
            has_printed = 1;
        }
    }
    if (has_printed || nb_rows == 1)
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

static void clean_everyname(completion_t *completion_s)
{
    if (completion_s == NULL)
        return;
    if (completion_s->every_name != NULL)
        my_tabfree((void **) completion_s->every_name);
    completion_s->every_name = NULL;
}

static int fill_entries(DIR *dir, completion_t *completion_s, int count)
{
    struct dirent *entry;
    int index = 0;

    if (!dir || !completion_s)
        return 0;
    clean_everyname(completion_s);
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
