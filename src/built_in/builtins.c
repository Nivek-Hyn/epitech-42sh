/*
** EPITECH PROJECT, 2025
** builtins
** File description:
** minishell2
*/

#include "shell/config/built_in.h"

const sh_builtin_conf_t sh_builtins[] = {
    {SH_BLTN_CLS},
    {SH_BLTN_EXIT},
    {SH_BLTN_CD},
    {SH_BLTN_ENV},
    {SH_BLTN_SETENV},
    {SH_BLTN_UNSETENV},
    {SH_BLTN_RETURN},
    {SH_BLTN_BG},
    {SH_BLTN_FG},
    {SH_BLTN_SHELLCUSTOM},
    {SH_BLTN_ALIAS},
    {SH_BLTN_HISTORY},
    {SH_BLTN_NOTHING},
    {SH_BLTN_WHICH},
    {SH_BLTN_WHERE},
    {SH_BLTN_REPEAT},
    {SH_BLTN_BLANK}
};
