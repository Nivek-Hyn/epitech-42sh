/*
** EPITECH PROJECT, 2025
** exec_utils
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "kill.h"
#include "shell/built_in.h"
#include "shell/shell.h"
#include "shell/env.h"
#include "shell/misc.h"
#include "shell/job.h"
#include "my_printf.h"

void sh_exec_print_crash(int status)
{
    if (WTERMSIG(status) == SIGFPE)
        my_putstr_fd("Floating exception", STDERR);
    else
        my_putstr_fd(strsignal(WTERMSIG(status)), STDERR);
    if (WCOREDUMP(status) != 0)
        my_putstr_fd(" (core dumped)", STDERR);
    my_putstr_fd("\n", STDERR);
}

void sh_exec_print_execerror(const char *program, int errcode)
{
    my_putstr_fd(program, STDERR);
    if (errcode == ENOEXEC) {
        my_putstr_fd(": Exec format error. Wrong Architecture.\n",
            STDERR);
        return;
    }
    if (errcode == ENOENT) {
        my_putstr_fd(": Command not found.\n", STDERR);
        return;
    }
    my_putstr_fd(": ", STDERR);
    my_putstr_fd(strerror(errcode), STDERR);
    my_putstr_fd(".\n", STDERR);
}

int sh_exec_check_access(const char *program, bool_t show_msg)
{
    if (program == NULL)
        return FUNC_FAILED;
    if (access(program, X_OK) == FUNC_FAILED) {
        if (show_msg == TRUE)
        sh_exec_print_execerror(program, errno);
        return FUNC_FAILED;
    }
    return FUNC_SUCCESS;
}

void sh_sigtstp_manager(shell_data_t *shell_data, pid_t child_pid, int status)
{
    jobs_t *job = NULL;

    if (WIFSTOPPED(status)) {
        my_printf("\nSuspended\n");
        job = get_job_by_pid(shell_data, child_pid);
        job->status = SUSPENDED;
        job->is_background = TRUE;
    } else {
        remove_job_by_pid(shell_data, child_pid);
    }
}
