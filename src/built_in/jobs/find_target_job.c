/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** find_target_job
*/

#include "shell/shell.h"
#include "my.h"
#include "shell/job.h"
#include <string.h>
#include "shell/misc.h"

jobs_t *find_target_job(shell_data_t *shell_data, char **args)
{
    if (my_tablen((const void **)args) > 1 && args[1][0] == '%') {
        if (strcmp(&args[1][1], "+") == 0)
            return get_job_by_mark(shell_data, '+');
        if (strcmp(&args[1][1], "-") == 0)
            return get_job_by_mark(shell_data, '-');
        if (is_number(&args[1][1])) {
            return get_job_by_id(shell_data, my_atoi(&args[1][1]));
        } else {
            return get_job_by_name(shell_data, &args[1][1]);
        }
    } else {
        return get_job_by_mark(shell_data, '+');
    }
    return NULL;
}
