/*
** EPITECH PROJECT, 2025
** bg
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/shell.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include <signal.h>
#include "shell/job.h"

void run_bg(jobs_t **current)
{
    (*current)->is_background = TRUE;
    (*current)->status = RUNNING;
    kill(-(*current)->pgid, SIGCONT);
    printf("[%d]    ", (*current)->id);
    print_job_command(*current);
    printf("\n");
}

int sh_builtin_bg(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, 1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    current = find_target_job(shell_data, task->args);
    if (current == NULL) {
        printf("bg: no such job\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    run_bg(&current);
    current->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
