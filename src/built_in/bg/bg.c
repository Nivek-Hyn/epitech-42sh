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

int bg_args_loop(shell_data_t *shell_data, sh_tasker_t *task,
    jobs_t **current)
{
    for (int i = 1; task->args[i] != NULL; i++) {
        (*current) = find_target_job(shell_data, task->args[i]);
        if ((*current) == NULL) {
            printf("bg: no such job\n");
            return EXIT_FAILURE;
        }
        run_bg(&(*current));
        (*current)->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    }
    return 0;
}

static void consume_task(sh_tasker_t *task)
{
    if (task == NULL)
        return;
}

int bg_no_args(shell_data_t *shell_data, sh_tasker_t *task,
    jobs_t **current)
{
    consume_task(task);
    (*current) = find_target_job(shell_data, NULL);
    if ((*current) == NULL) {
        printf("bg: no such job\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    run_bg(&(*current));
    (*current)->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    return 0;
}

int sh_builtin_bg(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, -1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (my_tablen((const void **)task->args) > 1) {
        if (bg_args_loop(shell_data, task, &current) == EXIT_FAILURE)
            return sh_builtin_fail(shell_data, EXIT_FAILURE);
    } else {
        if (bg_no_args(shell_data, task, &current) == EXIT_FAILURE)
            return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
