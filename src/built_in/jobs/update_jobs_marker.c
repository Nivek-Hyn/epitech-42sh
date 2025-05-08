/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** update_jobs_marker
*/

#include "shell/shell.h"
#include "my.h"

void update_plus_and_minus(jobs_t **current, jobs_t **plus, jobs_t **minus)
{
    if (!(*plus) || (*current)->last_used > (*plus)->last_used) {
        (*minus) = (*plus);
        (*plus) = (*current);
    } else if (!(*minus) || (*current)->last_used > (*minus)->last_used) {
        (*minus) = (*current);
    }
}

void update_jobs_marker(shell_data_t *shell_data)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *plus = NULL;
    jobs_t *minus = NULL;

    while (current) {
        if (current->status == RUNNING || current->status == SUSPENDED)
            update_plus_and_minus(&current, &plus, &minus);
        current = current->next;
    }
    for (current = shell_data->jobs; current; current = current->next)
        current->marker = ' ';
    if (plus)
        plus->marker = '+';
    if (minus)
        minus->marker = '-';
}
