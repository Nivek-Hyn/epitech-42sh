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

static void sigtstp_handler(int signo)
{
    (void)signo;
    write(1, "test\n", 5);
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
    signal(SIGTSTP, SIG_DFL);
}

int my_stdin_getline(char **buf, int file, shell_data_t *shell_data)
{
    struct termios oldt;
    tty_t *tty = malloc(sizeof(tty_t));
    int res = 0;

    tty->buffer = malloc(sizeof(char) * 1);
    tty->size = 0;
    tty->cursor = 0;
    tty->current = malloc(sizeof(char) * 1);
    tty->history = shell_data->user_data->history_len;
    enable_raw_mode(&oldt);
    res = read_stdin(tty, file, shell_data);
    disable_raw_mode(&oldt);
    if (res <= 0) {
        free(tty->buffer);
        return res;
    }
    *buf = realloc(tty->buffer, tty->size);
    if (!*buf)
        return -1;
    return tty->size;
}
