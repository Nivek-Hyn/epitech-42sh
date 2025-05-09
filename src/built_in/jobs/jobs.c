/*
** EPITECH PROJECT, 2025
** jobs
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>
#include "shell/job.h"
#include "my_printf.h"

void print_job(jobs_t *job)
{
    my_printf("[%d]  %c ", job->id, job->marker);
    switch (job->status) {
        case RUNNING:
            my_printf("%s\t\t\t\t", "Running");
            break;
        case SUSPENDED:
            my_printf("%s\t\t\t\t", "Suspended");
            break;
        case TERMINATED:
            my_printf("%s\t\t\t\t", "Terminated");
            break;
        default:
            break;
    }
    print_job_command(job);
    my_printf("\n");
}

int sh_builtin_jobs(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, 1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    while (current) {
        print_job(current);
        current = current->next;
    }
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
