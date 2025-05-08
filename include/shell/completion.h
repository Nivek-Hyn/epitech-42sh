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
    char *typed;
    char *concat;
} completion_t;

int sh_fill_completion_names(DIR *dir, completion_t *completion_s);
char *extract_last_word(char *buffer);
void print_all_names(completion_t *completion_s, tty_t *tty);
void printeur(char *name, int *printed);
void check_is_solo(int nb_rows, completion_t *completion_s, tty_t *tty, int i);

#endif /* !COMPLETION_H_ */
