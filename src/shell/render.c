/*
** EPITECH PROJECT, 2025
** render
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"
#include "shell/shell.h"
#include "colors.h"
#include "shell/misc.h"
#include "utils.h"

static int update_datas(shell_data_t *shell_data)
{
    if (shell_data == NULL)
        return FUNC_FAILED;
    free(shell_data->pwd);
    shell_data->pwd = sh_get_pwd_color();
    return FUNC_SUCCESS;
}

int sh_render_window(shell_data_t *shell_data)
{
    const char *usr_string = COL_GRN_B "%s" COL_MAG_B " @ " COL_CYN_B "%s ";

    if (shell_data == NULL)
        return FUNC_FAILED;
    if (isatty(STDIN) == FALSE || shell_data->user_data == NULL)
        return FUNC_FAILED;
    update_datas(shell_data);
    my_printf((char *) usr_string, shell_data->user_data->user,
        shell_data->user_data->hostname, shell_data->pwd);
    if (shell_data->last_excode > 0)
        my_printf(COL_RED_B "(%s%d) ", shell_data->last_excode == 0 ?
            "✔ " : "✘ ", shell_data->last_excode);
    my_printf(COL_MAG_B "> " COL_BLU_B "%s" COL_RESET "$ ", shell_data->pwd);
    return FUNC_SUCCESS;
}
