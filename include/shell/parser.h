/*
** EPITECH PROJECT, 2025
** parser (Shell)
** File description:
** minishell2
*/

#include <stdio.h>
#include "config/data.h"

#ifndef SH_PARSER_H
    #define SH_PARSER_H

    #define MAX_LINE_SIZE 1024

typedef struct tty_s {
    int history;
    int cursor;
    int size;
    char *current;
    char *buffer;
} tty_t;


int sh_parse_entry(shell_data_t *shell_data);
sh_prsent_t *sh_parse_string(const char *string);
int read_stdin(tty_t *tty, int file, shell_data_t *shell_data);
int my_stdin_getline(char **buf, int file, shell_data_t *shell_data);
void handle_history_arr(tty_t *tty, shell_data_t *shell_data, char c);

#endif

#ifndef SH_PARSER_GET_H
    #define SH_PARSER_GET_H

char *sh_get_entry(int file, shell_data_t *shell_data);
int sh_get_prsent_len(sh_prsent_t *chain);
int sh_get_prsent_eltslen(sh_prsent_t *chain);
char *sh_get_prsent_index(sh_prsent_t *chain, int index);
sh_prsent_type_t sh_get_pipe_type(char *shard);
bool_t sh_parser_is_anypipe(sh_prsent_t *entry);
bool_t sh_parser_is_spipe(sh_prsent_t *entry);

#endif

#ifndef SH_PARSER_CHAINER_H
    #define SH_PARSER_CHAINER_H

sh_prsent_t *sh_prsent_create(char *entry, sh_prsent_type_t type);
int sh_prsent_chain(sh_prsent_t **start, sh_prsent_t *chain);
void sh_prsent_free(sh_prsent_t *chain);
void sh_prsent_destroy(sh_prsent_t *chain);

#endif

#ifndef SH_PARSER_CONVERTER_H
    #define SH_PARSER_CONVERTER_H

char *sh_prsent_to_char_ptr(sh_prsent_t *chain);
char **sh_prsent_to_char_tab(sh_prsent_t *chain);

#endif
