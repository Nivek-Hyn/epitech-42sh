/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** remove_job
*/

#include "shell/shell.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

void free_job(jobs_t **jobs, jobs_t **current, jobs_t **prev)
{
    jobs_t *to_delete = *current;

    if (*prev == NULL) {
        *jobs = (*current)->next;
        *current = *jobs;
    } else {
        (*prev)->next = (*current)->next;
        *current = (*current)->next;
    }
    if (to_delete->command_line)
        free(to_delete->command_line);
    my_tabfree((void **)to_delete->command);
    if (to_delete)
        free(to_delete);
    to_delete = NULL;
    g_jobs = *jobs;
}

void remove_job_by_id(shell_data_t *shell_data, int id)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *prev = NULL;

    while (current) {
        if (current->id == id) {
            free_job(&shell_data->jobs, &current, &prev);
            continue;
        }
        prev = current;
        current = current->next;
    }
}

void remove_job_by_pid(shell_data_t *shell_data, pid_t pid)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *prev = NULL;

    while (current) {
        if (current->pid == pid) {
            free_job(&shell_data->jobs, &current, &prev);
            continue;
        }
        prev = current;
        current = current->next;
    }
}

void remove_job_by_name(shell_data_t *shell_data, char *name)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *prev = NULL;

    while (current) {
        if (strcmp(current->command_line, name) == 0) {
            free_job(&shell_data->jobs, &current, &prev);
            continue;
        }
        prev = current;
        current = current->next;
    }
}

void remove_finished_jobs(shell_data_t *shell_data)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *prev = NULL;

    while (current != NULL) {
        if (current->status == DONE || current->status == TERMINATED) {
            free_job(&shell_data->jobs, &current, &prev);
            continue;
        }
        prev = current;
        current = current->next;
    }
    g_jobs = shell_data->jobs;
}
