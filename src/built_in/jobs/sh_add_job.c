/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** sh_add_job
*/

#include "shell/shell.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>
#include "shell/job.h"

int job_id_exist(jobs_t *jobs, int id)
{
    jobs_t *current = jobs;

    while (current) {
        if (current->id == id)
            return 1;
        current = current->next;
    }
    return 0;
}

int get_lowest_unoccupied_job_id(jobs_t *jobs)
{
    int id = 1;

    while (job_id_exist(jobs, id) == 1)
        id++;
    return id;
}

void initialize_new_job(shell_data_t *shell_data, sh_tasker_t *task,
    pid_t pid, jobs_t **new_job)
{
    (*new_job)->id = 0;
    (*new_job)->pid = pid;
    (*new_job)->pgid = getpgid(pid);
    (*new_job)->command_line = strdup(shell_data->line);
    (*new_job)->command = my_tabdup(task->args);
    (*new_job)->is_background = task->pipes.background;
    (*new_job)->status = RUNNING;
    (*new_job)->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    (*new_job)->marker = ' ';
    (*new_job)->next = NULL;
}

void sh_add_job(shell_data_t *shell_data, sh_tasker_t *task, pid_t pid)
{
    jobs_t *new_job = malloc(sizeof(jobs_t));
    jobs_t *current = shell_data->jobs;

    if (new_job == NULL)
        return;
    initialize_new_job(shell_data, task, pid, &new_job);
    if (shell_data->jobs == NULL) {
        new_job->id = 1;
        shell_data->jobs = new_job;
    } else {
        while (current->next != NULL)
            current = current->next;
        new_job->id = get_lowest_unoccupied_job_id(shell_data->jobs);
        current->next = new_job;
    }
}
