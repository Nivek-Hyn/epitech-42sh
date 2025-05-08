/*
** EPITECH PROJECT, 2025
** std_pipe
** File description:
** Minishell2
*/

#include <stdlib.h>
#include <glob.h>
#include "my.h"
#include "shell/shell.h"
#include "shell/pipes.h"
#include "shell/parser.h"
#include "shell/tasker.h"
#include "utils.h"

static void consume_next_argument(char *next_argument)
{
    if (next_argument == NULL)
        return;
}

static char **get_glob(const char *format)
{
    glob_t glob_buf;
    char **matches = NULL;
    char *temp = NULL;

    if (glob(format, GLOB_NOFLAGS | GLOB_NOCHECK,
        NULL, &glob_buf) != FUNC_SUCCESS)
        return NULL;
    matches = my_tabdup(glob_buf.gl_pathv);
    globfree(&glob_buf);
    if (matches != NULL)
        if (my_strcmp(matches[0], format) == CMP_EXACT) {
            temp = my_strchrdup(matches[0], '*');
            free(matches[0]);
            matches[0] = temp;
        }
    return matches;
}

int sh_tsk_intprt_globbing_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument)
{
    char *shard = (shard_ptr != NULL) ? *shard_ptr : NULL;
    char *all_globbings = NULL;
    char **globbers = NULL;

    if (task == NULL || shard == NULL ||
        shard_ptr == NULL)
        return FUNC_FAILED;
    globbers = get_glob(shard);
    all_globbings = my_tabtostr((const char **) globbers);
    if (all_globbings == NULL)
        all_globbings = my_strdup("<ERROR>");
    my_tabfree((void **) globbers);
    sh_parser_override(&task->parser_entry, sh_parse_string(all_globbings),
        shard_ptr);
    free(all_globbings);
    sh_tasker_patch(task);
    consume_next_argument(next_argument);
    return FUNC_SUCCESS;
}
