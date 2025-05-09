/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** kill_job
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

int kill_job_args_loop(shell_data_t *shell_data, sh_tasker_t *task,
    jobs_t **current)
{
    for (int i = 1; task->args[i] != NULL; i++) {
        (*current) = find_target_job(shell_data, task->args[i]);
        if ((*current) == NULL) {
            my_printf("kill_job: no such job\n");
            return EXIT_FAILURE;
        }
        remove_job_by_id(shell_data, (*current)->id);
    }
    return 0;
}

int sh_builtin_kill_job(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, -1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    g_jobs = shell_data->jobs;
    if (my_tablen((const void **)task->args) > 1) {
        if (kill_job_args_loop(shell_data, task, &current) == EXIT_FAILURE)
            return sh_builtin_fail(shell_data, EXIT_FAILURE);
    } else {
        my_printf("kill: Too few arguments.\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
