/*
** EPITECH PROJECT, 2025
** exec_redirection
** File description:
** minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "shell/built_in.h"
#include "shell/shell.h"
#include "shell/env.h"
#include "shell/misc.h"
#include "shell/exec.h"

static int pipe_and_redirect(const char *filename,
    sh_tasker_redir_type_t type, int fd, int fd_to_replace)
{
    int new_fd = FUNC_FAILED;
    int ret_stat = FUNC_FAILED;
    int flags = O_CREAT | O_RDWR | O_TRUNC;

    if (fd_to_replace < 0)
        return FUNC_FAILED;
    if (type == SH_REDIR_RIGHT_APPEND)
        flags = O_CREAT | O_RDWR | O_APPEND;
    if (type == SH_REDIR_LEFT || type == SH_REDIR_LEFT_APPEND)
        flags = O_RDONLY;
    if (filename != NULL) {
        new_fd = open(filename, flags, 0644);
        if (new_fd < 0)
            return FUNC_FAILED;
        ret_stat = dup2(new_fd, fd_to_replace);
        close(new_fd);
        return ret_stat;
    }
    return dup2(fd, fd_to_replace);
}

static int assign_pipes(sh_tasker_pipes_t *rd, int p_fd[2])
{
    if (rd == NULL || p_fd == NULL)
        return FUNC_FAILED;
    if (rd->stdin_fd != -1)
        return SH_STDIN_REX(rd) ?
        pipe_and_redirect(SH_STDIN_RFN(rd), rd->redir_type, -1, STDIN) :
        pipe_and_redirect(SH_STDIN_RFN(rd), rd->redir_type, p_fd[0], STDIN);
    if (rd->stdout_fd != -1)
        return SH_STDOUT_REX(rd) ?
        pipe_and_redirect(SH_STDOUT_RFN(rd), rd->redir_type, -1, STDOUT) :
        pipe_and_redirect(SH_STDOUT_RFN(rd), rd->redir_type, p_fd[0], STDOUT);
    if (rd->stderr_fd != -1)
        return SH_STDERR_REX(rd) ?
        pipe_and_redirect(SH_STDERR_RFN(rd), rd->redir_type, -1, STDERR) :
        pipe_and_redirect(SH_STDERR_RFN(rd), rd->redir_type, p_fd[0], STDERR);
    return FUNC_SUCCESS;
}

int sh_exec_redirect(sh_tasker_t *task, int pipe_fd[2])
{
    if (task == NULL)
        return FUNC_FAILED;
    if (assign_pipes(&task->pipes, pipe_fd) == FUNC_FAILED)
        return FUNC_FAILED;
    sh_vclose(2, pipe_fd[0], pipe_fd[1]);
    return FUNC_SUCCESS;
}
