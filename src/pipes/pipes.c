/*
** EPITECH PROJECT, 2025
** pipes
** File description:
** Minishell2
*/

#include "shell/shell.h"
#include "shell/pipes.h"
#include "utils.h"

const sh_pipe_info_t sh_pipe_info[] = {
    {SH_PARSER_PIPE,
        (char *[]) {
            PIPE_R_REDIR, PIPE_R_AREDIR, PIPE_L_REDIR,
            PIPE_L_AREDIR, NULL
        },
        sh_tsk_intprt_std_pipe
    },
    {SH_PARSER_PROG_PIPE,
        (char *[]) {
            PIPE_PROG, NULL
        },
        NULL
    },
    {SH_PARSER_STOP_PIPE,
        (char *[]) {
            PIPE_SEP, PIPE_AND, PIPE_OR, NULL
        },
        sh_tsk_intprt_stop_pipe
    },
    {SH_PARSER_BACKGROUND_PIPE,
        (char *[]) {
            PIPE_BG, NULL
        },
        sh_tsk_intprt_bg_pipe
    },
    {SH_PARSER_HISTORY_PIPE,
        (char *[]) {
            PIPE_HIST, PIPE_HIST_NUM, NULL
        },
        sh_tsk_intprt_history_pipe
    },
    {SH_PARSER_GLOBBING_PIPE,
        (char *[]) {
            PIPE_GLOB_NUM, NULL
        },
        sh_tsk_intprt_globbing_pipe
    },
    {SH_PARSER_VAR_PIPE,
        (char *[]) {
            PIPE_VAR, NULL
        },
        sh_tsk_intprt_var_pipe
    },
    {SH_PARSER_UNKNOWN,
        NULL,
        NULL
    }
};
