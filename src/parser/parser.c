/*
** EPITECH PROJECT, 2025
** parser
** File description:
** minishell
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/parser.h"

static char *get_final_quote(char *line, char **last_stop, int i)
{
    if (line == NULL || last_stop == NULL || i < 0)
        return NULL;
    *last_stop = &line[i + 1];
    if (line[i + 1] == ' ' || line[i + 1] == '\t')
        *last_stop = &line[i + 2];
    return my_strptrdup(&line[1], &line[i]);
}

static char *get_quote_shard(char *line, char **last_stop, char quote,
    bool_t *parser_run)
{
    int i = 1;

    if (line == NULL || last_stop == NULL || quote == '\0' ||
        parser_run == NULL)
        return NULL;
    if (line[0] == '\0')
        return NULL;
    for (; line[i] != '\0'; i++) {
        if (line[i] == quote)
            return get_final_quote(line, last_stop, i);
    }
    fprintf(stderr, "Unmatched '%c'.\n", quote);
    *parser_run = FALSE;
    *last_stop = "";
    return NULL;
}

static char *get_shard(char *line, char **last_stop, bool_t *parser_run)
{
    if (line == NULL || last_stop == NULL || parser_run == NULL)
        return NULL;
    if (line[0] == '\0')
        return NULL;
    if (line[0] == ';' || line[0] == '&') {
        *last_stop = &line[1];
        return my_chrdup(line[0]);
    }
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == ';' ||
            line[i] == '&') {
            *last_stop = (line[i] != ';' && line[i] != '&') ?
                &line[i + 1] : &line[i];
            return my_strptrdup(line, &line[i]);
        }
        if (line[i] == '"' || line[i] == '\'')
            return get_quote_shard(line, last_stop, line[i], parser_run);
    }
    *last_stop = "";
    return my_strdup(line);
}

static bool_t is_supported_pipe(const char *shard)
{
    const char *supported_pipes[] = {";", ">", ">>", "<",
        "<<", "|", "||", "&&", "&", NULL};

    if (shard == NULL)
        return FALSE;
    if (shard[0] == '0' || shard[0] == '1' || shard[0] == '2')
        return my_isin(&shard[1], supported_pipes);
    return my_isin(shard, supported_pipes);
}

static int get_arguments(sh_prsent_t **chain, char *line)
{
    char *shard = NULL;
    char *last_stop = line;
    sh_prsent_t *curr_chain = NULL;
    bool_t argument_parser_run = TRUE;

    if (chain == NULL || line == NULL)
        return FUNC_FAILED;
    while (argument_parser_run) {
        shard = get_shard(last_stop, &last_stop, &argument_parser_run);
        if (shard == NULL)
            return (argument_parser_run) ? FUNC_SUCCESS : FUNC_SEMFAIL;
        if (is_supported_pipe(shard) == TRUE)
            curr_chain = sh_prsent_create(shard, sh_get_pipe_type(shard));
        else
            curr_chain = sh_prsent_create(shard, SH_PARSER_COMMAND);
        if (sh_prsent_chain(chain, curr_chain) == FUNC_FAILED)
            return FUNC_FAILED;
        shard = last_stop;
    }
    return FUNC_FAILED;
}

int sh_parse_entry(shell_data_t *shell_data)
{
    int parse_status = FUNC_FAILED;
    char *line = NULL;

    if (shell_data == NULL)
        return FUNC_FAILED;
    line = sh_get_entry(STDIN, shell_data);
    if (line == NULL)
        return FUNC_FAILED;
    if (line[0] == '\0') {
        free(line);
        shell_data->last_excode = EXIT_SUCCESS;
        return FUNC_SEMFAIL;
    }
    sh_write_into_history(shell_data, line);
    parse_status = get_arguments(&shell_data->command_chain, line);
    free(line);
    if (parse_status != FUNC_SUCCESS)
        return sh_builtin_spestat(shell_data, EXIT_FAILURE, parse_status);
    return FUNC_SUCCESS;
}
