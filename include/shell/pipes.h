/*
** EPITECH PROJECT, 2025
** pipes
** File description:
** Minishell2
*/

#include "shell/config/data.h"
#include "utils.h"

#ifndef SH_PIPES_H
    #define SH_PIPES_H

    #define REG_START       "^"
    #define REG_END         "$"
    #define PIPE_R_REDIR    REG_START "([0-2]?)>" REG_END
    #define PIPE_L_REDIR    REG_START "([0-2]?)<" REG_END
    #define PIPE_R_AREDIR   REG_START "([0-2]?)>>" REG_END
    #define PIPE_L_AREDIR   REG_START "([0-2]?)<<" REG_END
    #define PIPE_PROG       REG_START "\\|" REG_END
    #define PIPE_SEP        REG_START ";" REG_END
    #define PIPE_AND        REG_START "&&" REG_END
    #define PIPE_OR         REG_START PIPE_PROG PIPE_PROG REG_END
    #define PIPE_BG         REG_START "&" REG_END
    #define PIPE_HIST       REG_START "(.*[!])" REG_END
    #define PIPE_HIST_NUM   REG_START "(.*[0-9])!" REG_END
    #define PIPE_GLOB_NUM   REG_START "(.*\\*)" REG_END

    #define GLOB_NOFLAGS    0

bool_t sh_pipe_is(const char *shard, sh_prsent_type_t type);
sh_prsent_type_t sh_pipe_type(const char *shard);
bool_t sh_is_pipe(const char *shard);

int sh_pipe_consume(sh_tasker_t *tasker, sh_prsent_t **parser_ent);
int sh_p_pipe_consume(sh_tasker_t *tasker, sh_prsent_t **parser_ent);
int sh_pipes_interpret(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);
int sh_tsk_intprt_std_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);
int sh_tsk_intprt_stop_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);
int sh_tsk_intprt_bg_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);
int sh_tsk_intprt_history_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);
int sh_tsk_intprt_globbing_pipe(sh_tasker_t *task, char **shard_ptr,
    char *next_argument);

extern const sh_pipe_info_t sh_pipe_info[];

#endif

#ifndef SH_PIPESFD_H
    #define SH_PIPESFD_H

int sh_pipesfd_len(sh_tasker_t *tasks);
int **sh_pipesfd_generate(sh_tasker_t *tasks);
void sh_pipesfd_free(int **pipesfd);
void sh_pipesfd_close_all(int **pipesfd);
void sh_pipesfd_close_free(int **pipesfd);

#endif
