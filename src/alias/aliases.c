/*
** EPITECH PROJECT, 2025
** alaises
** File description:
** 42sh
*/

#include <stdio.h>
#include "shell/config/data.h"

const sh_def_aliases_t sh_default_aliases[] = {
    {"ls", "ls --color=auto"},
    {"grep", "grep --color=auto"},
    {"ll", "ls -l"},
    {"gp", "git push"},
    {"gpull", "git pull"},
    {NULL, NULL}
};
