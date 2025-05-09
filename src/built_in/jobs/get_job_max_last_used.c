/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** get_job_max_last_used
*/

#include "shell/shell.h"

int get_job_max_last_used(jobs_t *jobs)
{
    jobs_t *current = jobs;
    int max = 0;

    while (current) {
        if (current->last_used > max)
            max = current->last_used;
        current = current->next;
    }
    return max;
}
