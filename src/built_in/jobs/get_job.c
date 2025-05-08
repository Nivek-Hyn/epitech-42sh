/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** get_job
*/

#include "shell/shell.h"
#include "my.h"
#include <string.h>

jobs_t *get_job_by_mark(shell_data_t *shell_data, char marker)
{
    jobs_t *current = shell_data->jobs;

    while (current) {
        if (current->marker == marker)
            return current;
        current = current->next;
    }
    return NULL;
}

jobs_t *get_job_by_name(shell_data_t *shell_data, char *name)
{
    jobs_t *current = shell_data->jobs;

    while (current) {
        if (strcmp(current->command_line, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

jobs_t *get_job_by_pid(shell_data_t *shell_data, pid_t pid)
{
    jobs_t *current = shell_data->jobs;

    while (current) {
        if (current->pid == pid)
            return current;
        current = current->next;
    }
    return NULL;
}

jobs_t *get_job_by_id(shell_data_t *shell_data, int id)
{
    jobs_t *current = shell_data->jobs;

    while (current) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

jobs_t *get_last_job(shell_data_t *shell_data)
{
    jobs_t *current = shell_data->jobs;

    while (current->next)
        current = current->next;
    return current;
}
