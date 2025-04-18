/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** my_getline
*/

#include "shell/parser.h"
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

int my_stdin_getline(char **buf, int file)
{
    struct termios oldt;
    char *buffer = malloc(sizeof(char) * MAX_LINE_SIZE);
    int size = 0;
    int res = 0;

    enable_raw_mode(&oldt);
    res = read_stdin(&size, &buffer, file);
    disable_raw_mode(&oldt);
    if (res <= 0) {
        free(buffer);
        return res;
    }
    *buf = realloc(buffer, size);
    if (!*buf)
        return -1;
    return size;
}
