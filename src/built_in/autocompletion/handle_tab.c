/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** handle_tab
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

void printeur(char *name, int *printed)
{
    printf("%-45s", name);
    fflush(stdout);
    (*printed)++;
    if ((*printed) == 4) {
        printf("\n");
        (*printed) = 0;
    }
}

static void print_every_names(completion_t *completion_s)
{
    for (int i = 0; completion_s->every_name
        && completion_s->every_name[i]; i++) {
        printeur(completion_s->every_name[i], &completion_s->printed);
    }
    printf("\n");
}

void check_this(char *prefix,
    completion_t *completion_s, tty_t *tty)
{
    DIR *dir = opendir(prefix);
    int count;
    int nb_rows = 0;

    if (!dir)
        return;
    count = sh_fill_completion_names(dir, completion_s);
    closedir(dir);
    for (int i = 0; i < count; i++) {
        if (strncmp(completion_s->every_name[i],
            completion_s->typed, strlen(completion_s->typed)) == 0)
            nb_rows++;
    }
    for (int i = 0; i < count; i++) {
        if (!completion_s->typed || strlen(completion_s->typed) == 0)
            continue;
        check_is_solo(nb_rows, completion_s, tty, i);
    }
}

static void check_path_slash(char **all_path, char *path,
    tty_t *tty, completion_t *completion_s)
{
    size_t total;
    char *concat;

    for (int i = 0; all_path[i] != NULL; i++) {
        total = strlen(all_path[i]) + strlen(path) + 2;
        concat = malloc(sizeof(char) * total);
        if (!concat)
            continue;
        snprintf(concat, total, "%s/%s", all_path[i], path);
        completion_s->concat = strdup(concat);
        check_this(all_path[i], completion_s, tty);
        free(concat);
        free(completion_s->concat);
    }
}

static void check_path_without_slash(completion_t *completion_s,
    char *path, tty_t *tty)
{
    DIR *dir = opendir(path);

    if (!dir)
        return;
    sh_fill_completion_names(dir, completion_s);
    closedir(dir);
    print_all_names(completion_s, tty);
}

void list_directory(char *path, char **all_path,
    completion_t *completion_s, tty_t *tty)
{
    if (!path || !completion_s || !tty)
        return;
    completion_s->typed = strdup(path);
    if (!completion_s->typed)
        return;
    completion_s->printed = 0;
    my_putchar('\n');
    if (path[0] != '/') {
        check_path_slash(all_path, path, tty, completion_s);
        if (completion_s->printed == 2)
            putchar('\n');
    } else
        check_path_without_slash(completion_s, path, tty);
    free(completion_s->typed);
    completion_s->typed = NULL;
}

void show_this_directory(completion_t *completion_s)
{
    DIR *dir = opendir(".");

    if (!dir)
        return;
    my_putchar('\n');
    sh_fill_completion_names(dir, completion_s);
    closedir(dir);
    print_every_names(completion_s);
}

static void launch_function(shell_data_t *shell_data,
    tty_t *tty, char *buff, char **all_path)
{
    completion_t *completion_s = malloc(sizeof(completion_t));

    if (!shell_data || !tty || !buff || !all_path || !completion_s)
        return;
    completion_s->every_name = NULL;
    completion_s->printed = 0;
    if (buff[0] == '\0')
        show_this_directory(completion_s);
    else
        list_directory(buff, all_path, completion_s, tty);
    sh_render_window(shell_data);
    my_putstr(tty->buffer);
    my_tabfree((void **) all_path);
    if (completion_s->every_name != NULL)
        my_tabfree((void **) completion_s->every_name);
    free(completion_s);
}

static void process_completion(shell_data_t *shell_data,
    tty_t *tty, char *buff)
{
    char *every_path = sh_env_get(shell_data->env, "PATH");
    char **all_path = NULL;

    if (!every_path)
        return;
    all_path = my_sepstr(every_path, ":");
    if (!all_path)
        return;
    launch_function(shell_data, tty, buff, all_path);
}

void handle_tab(tty_t *tty, shell_data_t *shell_data)
{
    char *buff = NULL;

    if (!tty)
        return;
    buff = extract_last_word(tty->buffer);
    if (!buff)
        return;
    process_completion(shell_data, tty, buff);
    free(buff);
}
