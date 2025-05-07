/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** completion
*/

#include "shell.h"
#include "config/data.h"
#include "my.h"

#ifndef COMPLETION_H_
    #define COMPLETION_H_

typedef struct completion_s {
    int printed;
    char **every_name;
} completion_t;

typedef struct getline_s {
    shell_data_t *data;
    tty_t *tty;
    char *buff;
} getline_t;

int sh_fill_completion_names(DIR *dir, completion_t *completion_s);
int fill_buffer(getline_t *gtln_s, char **all_path);
char *extract_last_word(char *buffer);
int fill_buffer(getline_t *gtln_s, char **all_path);
int fill_buffer_slash(getline_t *gtln_s, char **all_path);

#endif /* !COMPLETION_H_ */
