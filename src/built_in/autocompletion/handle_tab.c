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
#include <stdlib.h>
#include "shell/shell.h"
#include "shell/render.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include "shell/shell.h"
#include "shell/env.h"

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

void check_this(char *prefix, char *typed, int *printed)
{
    DIR *dir = opendir(prefix);
    struct dirent *entry;

    if (!dir) {
        return;
    }
    entry = readdir(dir);
    while (entry != NULL) {
        if (!typed || strlen(typed) == 0)
            continue;
        if (strncmp(entry->d_name, typed, strlen(typed)) == 0)
            printeur(entry->d_name, printed);
        entry = readdir(dir);
    }
    closedir(dir);
    return;
}

static void check_path_slash(char **all_path, char *path,
    char *typed, int printed)
{
    size_t total;
    char *concat;

    for (int i = 0; all_path[i] != NULL; i++) {
        total = strlen(all_path[i]) + strlen(path) + 2;
        concat = malloc(sizeof(char) * total);
        if (!concat)
            continue;
        snprintf(concat, total, "%s/%s", all_path[i], path);
        check_this(all_path[i], typed, &printed);
        free(concat);
    }
}

static void check_path_without_slash(int printed,
    char *path)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir)
        return;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.') {
            printeur(entry->d_name, &printed);
        }
        entry = readdir(dir);
    }
    closedir(dir);
}

void list_directory(char *path, char **all_path)
{
    char *typed = strdup(path);
    int printed = 0;

    if (!typed)
        return;
    my_putchar('\n');
    if (path[0] != '/') {
        check_path_slash(all_path, path, typed, printed);
    } else {
        check_path_without_slash(printed, path);
    }
    free(typed);
    printf("\n");
}

void show_this_directory(void)
{
    DIR *dir;
    struct dirent *entry;
    int printed = 0;

    my_putchar('\n');
    dir = opendir(".");
    if (!dir)
        return;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] != '.') {
            printeur(entry->d_name, &printed);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    printf("\n");
}

static void lauch_function(shell_data_t *shell_data,
    tty_t *tty, char *buff, char **all_path)
{
    if (buff[0] == '\0') {
        show_this_directory();
    } else
        list_directory(buff, all_path);
    sh_render_window(shell_data);
    my_putstr(tty->buffer);
    my_tabfree((void **)all_path);
}

void handle_tab(tty_t *tty, shell_data_t *shell_data)
{
    int len = my_tablen((const void **)my_sepstr(tty->buffer, " "));
    char *buff = strdup(my_sepstr(tty->buffer, " ")[len - 1]);
    char *every_path;
    char **all_path;

    if (!tty || !buff)
        return;
    every_path = sh_env_get(shell_data->env, "PATH");
    if (!every_path)
        return;
    all_path = my_sepstr(every_path, ":");
    if (!all_path) {
        free(every_path);
        return;
    }
    lauch_function(shell_data, tty, buff, all_path);
}
