/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** check_jobs
*/

#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include <sys/wait.h>
#include "shell/job.h"

int check_if_job_done(shell_data_t *shell_data,
    jobs_t **current, jobs_t **prev, int status)
{
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        (*current)->status = DONE;
        if ((*current)->is_background == TRUE) {
            printf("[%d]  %c Done\t\t\t\t",
                (*current)->id, (*current)->marker);
            print_job_command(*current);
            printf("\n");
        }
        free_job(&shell_data->jobs, current, prev);
        return 1;
    }
    return 0;
}

int check_if_job_changed_state(shell_data_t *shell_data,
    jobs_t **current, jobs_t **prev)
{
    pid_t result;
    int status = 0;

    if ((*current)->status == RUNNING) {
        result = waitpid((*current)->pid, &status, WNOHANG);
        if (result == (*current)->pid) {
            return check_if_job_done(shell_data, current, prev, status);
        }
    }
    return 0;
}

void check_jobs(shell_data_t *shell_data)
{
    jobs_t *current = shell_data->jobs;
    jobs_t *prev = NULL;

    while (current) {
        if (check_if_job_changed_state(shell_data, &current, &prev) == 1)
            continue;
        prev = current;
        current = current->next;
    }
}
