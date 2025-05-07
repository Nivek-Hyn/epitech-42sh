/*
** EPITECH PROJECT, 2025
** job
** File description:
** minishell2
*/

#include "shell/shell.h"
#include <sys/types.h>

#ifndef SH_JOB_FUNC_H
    #define SH_JOB_FUNC_H

// Jobs:
void sh_add_job(shell_data_t *shell_data, sh_tasker_t *task, pid_t pid);
void check_jobs(shell_data_t *shell_data);
void update_jobs_marker(shell_data_t *shell_data);
jobs_t *find_target_job(shell_data_t *shell_data, char **args);

// Get Job:
jobs_t *get_last_job(shell_data_t *shell_data);
jobs_t *get_job_by_id(shell_data_t *shell_data, int id);
jobs_t *get_job_by_pid(shell_data_t *shell_data, pid_t pid);
jobs_t *get_job_by_name(shell_data_t *shell_data, char *name);
jobs_t *get_job_by_mark(shell_data_t *shell_data, char marker);

// Remove Job:
void remove_finished_jobs(shell_data_t *shell_data);
void remove_job_by_id(shell_data_t *shell_data, int id);
void remove_job_by_pid(shell_data_t *shell_data, pid_t pid);
void remove_job_by_name(shell_data_t *shell_data, char *name);
void free_job(jobs_t **jobs, jobs_t **current, jobs_t **prev);
void free_jobs(jobs_t *jobs);

// Utility:
int get_job_max_last_used(jobs_t *jobs);
void print_job_command(jobs_t *job);

#endif
