/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** my_getline
*/

#include "shell/parser.h"
#include "my.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "my_printf.h"

static void sigtstp_handler(int signo)
{
    (void)signo;
    if (g_jobs == NULL)
        return;
    for (jobs_t *current = (jobs_t *)g_jobs;
            current; current = current->next) {
        if (current->is_background == FALSE) {
            kill(-current->pgid, SIGSTOP);
            my_printf("\n");
        }
    }
}

void enable_raw_mode(struct termios *oldt)
{
    struct termios newt;

    tcgetattr(STDIN_FILENO, oldt);
    newt = *oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    signal(SIGTSTP, sigtstp_handler);
}

void disable_raw_mode(struct termios *oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    signal(SIGTSTP, sigtstp_handler);
}

static int get_tty_struct(tty_t **tty, shell_data_t *shell_data)
{
    if (tty == NULL || shell_data == NULL)
        return FUNC_FAILED;
    *tty = malloc(sizeof(tty_t));
    if (*tty == NULL)
        return FUNC_FAILED;
    (*tty)->buffer = malloc(sizeof(char) * 1);
    (*tty)->size = 0;
    (*tty)->cursor = 0;
    (*tty)->current = malloc(sizeof(char) * 1);
    (*tty)->buffer[0] = '\0';
    (*tty)->history = shell_data->user_data->history_len;
    if ((*tty)->buffer == NULL || (*tty)->current == NULL) {
        my_vfree(3, (*tty)->buffer, (*tty)->current, (*tty));
        return FUNC_SEMFAIL;
    }
    return FUNC_SUCCESS;
}

int my_stdin_getline(char **buf, int file, shell_data_t *shell_data)
{
    struct termios oldt;
    tty_t *tty = NULL;
    int res = 0;

    if (buf == NULL || file < 0 || shell_data == NULL)
        return FUNC_FAILED;
    if (get_tty_struct(&tty, shell_data) == FUNC_FAILED)
        return FUNC_FAILED;
    enable_raw_mode(&oldt);
    res = read_stdin(tty, file, shell_data);
    disable_raw_mode(&oldt);
    if (res <= 0) {
        my_vfree(3, tty->buffer, tty->current, tty);
        return res;
    }
    res = tty->size;
    *buf = realloc(tty->buffer, res + 1);
    my_vfree(2, tty->current, tty);
    return (!*buf) ? FUNC_FAILED : res;
}
