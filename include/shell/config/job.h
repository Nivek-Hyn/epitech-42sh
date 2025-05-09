/*
** EPITECH PROJECT, 2025
** B-PSU-200-MAR-2-1-42sh-hugo.sorgues
** File description:
** job
*/

#include <sys/types.h>

#ifndef SH_JOB_STRUCT_H
    #define SH_JOB_STRUCT_H

typedef enum job_status {
    RUNNING,
    SUSPENDED,
    TERMINATED,
    DONE,
} job_status_t;

typedef struct jobs_s {
    int id;
    pid_t pid;
    pid_t pgid;
    char *command_line;
    char **command;
    bool_t is_background;
    job_status_t status;
    int last_used;
    char marker;
    struct jobs_s *next;
} jobs_t;

extern const jobs_t *g_jobs;

#endif
