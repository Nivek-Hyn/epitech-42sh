/*
** EPITECH PROJECT, 2025
** sh_regin
** File description:
** 42sh
*/

#include <stdio.h>
#include <regex.h>
#include "my.h"
#include "utils.h"

bool_t sh_regin(const char *string, const char **string_list)
{
    regex_t regex;
    regmatch_t pmatch[1];

    if (string == NULL || string_list == NULL)
        return FALSE;
    for (int i = 0; string_list[i] != NULL; i++) {
        if (regcomp(&regex, string_list[i], REG_EXTENDED))
            return FALSE;
        if (regexec(&regex, string, sizeof(pmatch) / sizeof(pmatch[0]),
            pmatch, 0) == CMP_EXACT) {
            regfree(&regex);
            return TRUE;
        }
        regfree(&regex);
    }
    return FALSE;
}
