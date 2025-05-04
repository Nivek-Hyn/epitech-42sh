/*
** EPITECH PROJECT, 2025
** get
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell/parser.h"
#include "getline.h"
#include "my.h"
#include "utils.h"

sh_prsent_type_t sh_get_pipe_type(char *shard)
{
    if (shard == NULL)
        return SH_PARSER_UNKNOWN;
    if (my_strcmp(shard, ";") == CMP_EXACT
    || my_strcmp(shard, "&&") == CMP_EXACT)
        return SH_PARSER_STOP_PIPE;
    if (my_strcmp(shard, "&") == CMP_EXACT)
            return SH_PARSER_BACKGROUND_PIPE;
    if (my_strcmp(shard, "|") == CMP_EXACT
        || my_strcmp(shard, "||") == CMP_EXACT)
        return SH_PARSER_PROG_PIPE;
    return SH_PARSER_PIPE;
}

int sh_get_prsent_eltslen(sh_prsent_t *chain)
{
    int total_len = 0;

    for (; chain != NULL; chain = chain->next) {
        if (sh_parser_is_anypipe(chain) == TRUE)
            return total_len;
        if (my_strcmp(chain->entry, "") == CMP_EXACT)
            continue;
        total_len += my_strlen(chain->entry);
    }
    return total_len;
}

int sh_get_prsent_len(sh_prsent_t *chain)
{
    int total_len = 0;

    for (; chain != NULL; chain = chain->next) {
        if (sh_parser_is_anypipe(chain) == TRUE)
            return total_len;
        if (my_strcmp(chain->entry, "") == CMP_EXACT)
            continue;
        total_len += 1;
    }
    return total_len;
}

char *sh_get_prsent_index(sh_prsent_t *chain, int index)
{
    int curr_index = 0;

    for (; chain != NULL; chain = chain->next) {
        if (my_strcmp(chain->entry, "") == CMP_EXACT)
            continue;
        if (curr_index == index && sh_parser_is_anypipe(chain) == FALSE)
            return chain->entry;
        if (sh_parser_is_anypipe(chain) == TRUE)
            return NULL;
        curr_index++;
    }
    return NULL;
}

static int cust_getline(char **line, int file_no,
    shell_data_t *shell_data, FILE *file)
{
    size_t size = 0;

    if (line == NULL || file_no < 0 || file == NULL)
        return FUNC_FAILED;
    if (isatty(STDIN) == TRUE) {
        if (my_stdin_getline(line, file_no, shell_data) == FUNC_FAILED) {
            free(*line);
            return FUNC_FAILED;
        }
    } else {
        if (getline(line, &size, file) == FUNC_FAILED) {
            free(*line);
            return FUNC_FAILED;
        }
    }
    return FUNC_SUCCESS;
}

char *sh_get_entry(int file, shell_data_t *shell_data)
{
    char *line = NULL;
    char *ret_line = NULL;
    char *newline = NULL;

    if (cust_getline(&line, file, shell_data, stdin) == FUNC_FAILED)
        return NULL;
    newline = my_strstr(line, "\n");
    if (newline != NULL)
        *newline = '\0';
    ret_line = my_strdup(line);
    free(line);
    return ret_line;
}
