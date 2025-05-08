/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** print_command
*/

#include "shell/shell.h"

void print_job_command(jobs_t *job)
{
    for (int i = 0; job->command[i] != NULL; i++) {
        printf("%s", job->command[i]);
        if (job->command[i + 1] != NULL)
            printf(" ");
    }
}
