/*
** EPITECH PROJECT, 2025
** alias
** File description:
** 42sh
*/

#include "shell/config/data.h"

#ifndef SH_ALIAS_H
    #define SH_ALIAS_H

char_dict_t *sh_load_def_aliases(void);

extern const sh_def_aliases_t sh_default_aliases[];

#endif
