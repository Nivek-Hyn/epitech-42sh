/*
** EPITECH PROJECT, 2025
** repeat
** File description:
** 42sh
*/

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/wait.h>
#include "shell/shell.h"
#include "shell/render.h"
#include "shell/built_in.h"
#include "my.h"
#include "utils.h"
#include "shell/env.h"
#include "shell/completion.h"

static int check_repeat_args(char **args)
{
    if (!args[1] || !args[2]) {
        fprintf(stderr, "repeat: usage: repeat <n> <command>\n");
        return 1;
    }
    return 0;
}

static int validate_repeat_count(char *count_str)
{
    int count = atoi(count_str);

    if (count <= 0 || count > INT_MAX) {
        fprintf(stderr, "repeat: invalid repeat count: %s\n", count_str);
        return -1;
    }
    return count;
}

static int execute_command(shell_data_t *shell_data, char **args)
{
    int pid = fork();

    if (pid == 0) {
        execvp(args[2], &args[2]);
        perror("execvp");
        sh_shelldata_destroy(shell_data);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    }
    return pid;
}

static void wait_for_child(int pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
}

int sh_builtin_repeat(shell_data_t *shell_data, sh_tasker_t *task)
{
    int count = 0;
    int pid = 0;
    int i = 0;
    char **args = (task != NULL) ? task->args : NULL;

    if (shell_data == NULL || task == NULL)
        return FUNC_FAILED;
    if (check_repeat_args(args))
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    count = validate_repeat_count(args[1]);
    if (count == -1)
        return sh_builtin_fail(shell_data, EXIT_FAILURE);
    while (i < count) {
        pid = execute_command(shell_data, args);
        if (pid < 0)
            return sh_builtin_fail(shell_data, EXIT_FAILURE);
        wait_for_child(pid);
        i++;
    }
    return sh_builtin_success(shell_data, EXIT_SUCCESS);
}
