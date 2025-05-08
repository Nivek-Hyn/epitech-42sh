/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** free_jobs
*/

#include "shell/shell.h"
#include "my.h"
#include <stdlib.h>

void free_jobs(jobs_t *jobs)
{
    jobs_t *to_delete = NULL;

    while (jobs != NULL) {
        to_delete = jobs;
        jobs = jobs->next;
        if (to_delete->command_line)
            free(to_delete->command_line);
        my_tabfree((void **)to_delete->command);
        free(to_delete);
    }
}
