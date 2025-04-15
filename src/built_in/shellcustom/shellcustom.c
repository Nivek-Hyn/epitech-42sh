/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** shellcustom
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "shell/env.h"
#include "utils.h"

int sh_builtin_shellcustom(shell_data_t *shell_data, sh_tasker_t *task)
{
    my_putstr("Coucou shellcustom !\n");
    return FUNC_SUCCESS;
}
