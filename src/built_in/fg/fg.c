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

void run_fg(jobs_t **current)
{
    int status = 0;

    (*current)->is_background = FALSE;
    (*current)->status = RUNNING;
    tcsetpgrp(STDIN_FILENO, (*current)->pgid);
    kill(-(*current)->pgid, SIGCONT);
    waitpid((*current)->pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgid(0));
    if (WIFSTOPPED(status)) {
        printf("Suspended\n");
        (*current)->status = SUSPENDED;
    } else {
        (*current)->status = DONE;
    }
}

int sh_builtin_fg(shell_data_t *shell_data, sh_tasker_t *task)
{
    sh_bltin_verify_t prerequisites = {-1, 1};
    jobs_t *current = shell_data->jobs;

    if (shell_data == NULL || task == NULL)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    if (sh_builtin_verify(task->parser_entry, prerequisites) == FUNC_FAILED)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    current = find_target_job(shell_data, task->args);
    if (current == NULL) {
        printf("fg: no such job\n");
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    }
    run_fg(&current);
    current->last_used = get_job_max_last_used(shell_data->jobs) + 1;
    remove_finished_jobs(shell_data);
    task = NULL;
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
