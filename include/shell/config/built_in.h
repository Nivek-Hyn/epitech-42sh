/*
** EPITECH PROJECT, 2025
** built-in (Config)
** File description:
** minishell2
*/

#include <stdio.h>
#include "data.h"
#include "../built_in.h"

#ifndef SH_CONFIG_BUILTIN_H
    #define SH_CONFIG_BUILTIN_H

typedef struct {
    char *command;
    int (*builtin_f)(shell_data_t *, sh_tasker_t *);
} sh_builtin_conf_t;

    #define SH_BUILTINS_LIST "cd", "env", "setenv", "unsetenv", NULL

    #define SH_BLTN_BLANK NULL, NULL
    #define SH_BLTN_CLS "clear", sh_builtin_clear
    #define SH_BLTN_RETURN "return", sh_builtin_return
    #define SH_BLTN_EXIT "exit", sh_builtin_exit
    #define SH_BLTN_CD "cd", sh_builtin_cd
    #define SH_BLTN_ENV "env", sh_builtin_env
    #define SH_BLTN_SETENV "setenv", sh_builtin_setenv
    #define SH_BLTN_UNSETENV "unsetenv", sh_builtin_unsetenv
    #define SH_BLTN_SHELLCUSTOM "shellcustom", sh_builtin_shellcustom
    #define SH_BLTN_BG "bg", sh_builtin_bg
    #define SH_BLTN_FG "fg", sh_builtin_fg
    #define SH_BLTN_ALIAS "alias", sh_builtin_alias
    #define SH_BLTN_HISTORY "history", sh_builtin_history
    #define SH_BLTN_H_OR_T "pileouface", sh_builtin_h_or_t
    #define SH_BLTN_DARK_HUGO "dark_hugo", sh_builtin_dark_hugo


extern const sh_builtin_conf_t sh_builtins[];

#endif
