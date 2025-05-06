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

static void is_current(tty_t *tty, shell_data_t *data)
{
    if (tty->history == data->user_data->history_len && tty->buffer[0]) {
        free(tty->current);
        tty->current = strdup(tty->buffer);
    }
}

static void write_char_cursor(char c, tty_t *tty, shell_data_t *data)
{
    if (tty->size >= MAX_LINE_SIZE - 1)
        return;
    tty->buffer = realloc(tty->buffer, tty->size + 2);
    for (int i = tty->size; i > tty->cursor; i--)
        (tty->buffer)[i] = (tty->buffer)[i - 1];
    (tty->buffer)[tty->cursor] = c;
    write(1, &c, 1);
    (tty->size)++;
    (tty->cursor)++;
    (tty->buffer)[tty->size] = '\0';
    write(1, tty->buffer + tty->cursor, tty->size - tty->cursor);
    for (int i = 0; i < (tty->size - tty->cursor); i++)
        write(1, "\033[D", 3);
    is_current(tty, data);
}

static void handle_delete(tty_t *tty, shell_data_t *data)
{
    char c = 0;
    int i = 0;

    if (read(STDIN_FILENO, &c, 1) != 1 || tty->cursor >= tty->size ||
        tty->cursor < 0)
        return;
    if (c == '~') {
        if (tty->cursor >= tty->size)
            return;
        for (i = tty->cursor; i < tty->size - 1; i++)
            (tty->buffer)[i] = (tty->buffer)[i + 1];
        (tty->size)--;
        (tty->buffer)[tty->size] = '\0';
        write(1, (tty->buffer) + tty->cursor, tty->size - tty->cursor);
        write(1, " ", 1);
        for (i = 0; i <= (tty->size - tty->cursor); i++)
            write(1, "\033[D", 3);
    }
    is_current(tty, data);
}

void handle_arrow_keys(char seq[2], tty_t *tty, shell_data_t *shell_data)
{
    if (seq[0] != '[')
        return;
    if (seq[1] == 'C' && tty->cursor < tty->size) {
        write(1, "\033[C", 3);
        (tty->cursor)++;
    }
    if (seq[1] == 'D' && tty->cursor > 0) {
        write(1, "\033[D", 3);
        (tty->cursor)--;
    }
    if (seq[1] == 'A' || seq[1] == 'B')
        handle_history_arr(tty, shell_data, seq[1]);
    if (seq[1] == '3' && tty->cursor < tty->size)
        handle_delete(tty, shell_data);
}

void handle_backspace(tty_t *tty, shell_data_t *data)
{
    if (tty->cursor > 0 && tty->size > 0) {
        for (int i = tty->cursor - 1; i < tty->size - 1; i++)
            (tty->buffer)[i] = (tty->buffer)[i + 1];
        (tty->size)--;
        (tty->cursor)--;
        write(1, "\b \b", 3);
        write(1, tty->buffer + tty->cursor, tty->size - tty->cursor);
        write(1, " ", 1);
        for (int j = 0; j <= (tty->size - tty->cursor); j++)
            write(1, "\033[D", 3);
    }
    (tty->buffer)[tty->size] = '\0';
    is_current(tty, data);
}

void handle_regular_char(char c, tty_t *tty, shell_data_t *data)
{
    if (tty->cursor != tty->size) {
        write_char_cursor(c, tty, data);
    } else {
        (tty->buffer) = realloc((tty->buffer), (tty->size) + 2);
        (tty->buffer)[tty->cursor] = c;
        (tty->cursor)++;
        (tty->size)++;
        (tty->buffer)[tty->size] = '\0';
        write(1, &c, 1);
    }
    is_current(tty, data);
}

void handle_input_char(char c, tty_t *tty, shell_data_t *shell_data)
{
    char seq[2];

    if (c == 27) {
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return;
        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return;
        handle_arrow_keys(seq, tty, shell_data);
    }
    if ((c == 8 || c == 127) && tty->size > 0)
        handle_backspace(tty, shell_data);
    if (c == 26)
        write(1, "test", 4);
    if (c == '\t')
        handle_tab(tty, shell_data);
    if (c != 27 && c != 8 && c != 127 && c != 26 && c != '\t')
        handle_regular_char(c, tty, shell_data);
}

int read_stdin(tty_t *tty, int file, shell_data_t *shell_data)
{
    char c = 0;

    tty->current[0] = '\0';
    while (tty->size < MAX_LINE_SIZE) {
        if (read(file, &c, 1) <= 0 || c == 4)
            return -1;
        if (c == '\n') {
            (tty->buffer)[tty->size] = '\0';
            (tty->size)++;
            write(1, "\n", 1);
            return tty->size;
        }
        handle_input_char(c, tty, shell_data);
    }
    free(tty->current);
    return tty->size;
}
