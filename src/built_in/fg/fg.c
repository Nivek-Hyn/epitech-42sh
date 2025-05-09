/*
** EPITECH PROJECT, 2025
** fg
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell/job.h"
#include "my_printf.h"

void run_fg(jobs_t **current)
{
    int status = 0;

    print_job_command(*current);
    my_printf("\n");
    (*current)->is_background = FALSE;
    (*current)->status = RUNNING;
    kill(-(*current)->pgid, SIGCONT);
    waitpid((*current)->pid, &status, WUNTRACED);
    if (WIFSTOPPED(status)) {
        my_printf("Suspended\n");
        (*current)->status = SUSPENDED;
    } else {
        (*current)->status = DONE;
    }
}

int sh_builtin_fg(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, -1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    g_jobs = shell_data->jobs;
    current = (my_tablen((const void **)task->args) > 1) ?
        find_target_job(shell_data, task->args[0]) :
        find_target_job(shell_data, NULL);
    if (current == NULL) {
        my_printf("fg: no such job\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    run_fg(&current);
    current->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    remove_finished_jobs(shell_data);
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
