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

static void enable_raw_mode(struct termios *oldt)
{
    struct termios newt;

    tcgetattr(STDIN_FILENO, oldt);
    newt = *oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    signal(SIGTSTP, sigtstp_handler);
}

static void disable_raw_mode(struct termios *oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    signal(SIGTSTP, SIG_DFL);
}

static void write_char_cursor(char c, char **buffer, int *size, int *cursor)
{
    if (*size >= MAX_LINE_SIZE - 1)
        return;
    for (int i = *size; i > *cursor; i--)
        (*buffer)[i] = (*buffer)[i - 1];
    (*buffer)[*cursor] = c;
    write(1, &c, 1);
    (*size)++;
    (*cursor)++;
    (*buffer)[*size] = '\0';
    write(1, *buffer + *cursor, *size - *cursor);
    for (int i = 0; i < (*size - *cursor); i++)
        write(1, "\033[D", 3);
}

static void handle_arrow_keys(char seq[2], int *cursor, int size)
{
    if (seq[0] != '[')
        return;
    if (seq[1] == 'C' && *cursor < size) {
        write(1, "\033[C", 3);
        (*cursor)++;
    }
    if (seq[1] == 'D' && *cursor > 0) {
        write(1, "\033[D", 3);
        (*cursor)--;
    }
}

static void handle_backspace(char **buffer, int *size, int *cursor)
{
    int j = 0;

    if (*cursor > 0 && *size > 0) {
        for (int i = *cursor - 1; i < *size - 1; i++)
            (*buffer)[i] = (*buffer)[i + 1];
        (*size)--;
        (*cursor)--;
        write(1, "\b \b", 3);
        write(1, *buffer + *cursor, *size - *cursor);
        write(1, " ", 1);
        for (j = 0; j <= (*size - *cursor); j++)
            write(1, "\033[D", 3);
    }
}

static void handle_regular_char(char c, char **buffer, int *size, int *cursor)
{
    if (*cursor != *size) {
        write_char_cursor(c, buffer, size, cursor);
    } else {
        (*buffer)[*cursor] = c;
        (*cursor)++;
        (*size)++;
        write(1, &c, 1);
    }
}

static void handle_input_char(char c, char **buffer, int *size, int *cursor)
{
    char seq[2];

    if (c == 27) {
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return;
        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return;
        handle_arrow_keys(seq, cursor, *size);
    }
    if (c == 8 || c == 127)
        handle_backspace(buffer, size, cursor);
    if (c == 26)
        write(1, "test", 4);
    if (c != 27 && c != 8 && c != 127 && c != 26)
        handle_regular_char(c, buffer, size, cursor);
}

static int read_stdin(int *size, char **buffer, int file)
{
    int cursor = 0;
    char c = 0;

    while (*size < MAX_LINE_SIZE) {
        if (read(file, &c, 1) <= 0 || c == 4)
            return -1;
        if (c == '\n') {
            (*buffer)[*size] = '\0';
            (*size)++;
            write(1, "\n", 1);
            return *size;
        }
        handle_input_char(c, buffer, size, &cursor);
    }
    return *size;
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
