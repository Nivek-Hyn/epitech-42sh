/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** my_getline
*/

#include "shell/parser.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void erase_line(tty_t *tty)
{
    for (int i = 0; i < (tty->size - tty->cursor); i++)
        write(1, "\033[C", 3);
    for (int i = 0; i < tty->size; i++)
        write(1, "\b \b", 3);
}

static void handle_back_to_buff(tty_t *tty, shell_data_t *data)
{
    erase_line(tty);
    free(tty->buffer);
    if (tty->history < data->user_data->history_len)
        (tty->history)++;
    tty->buffer = strdup(tty->current);
    tty->size = strlen(tty->buffer);
    tty->cursor = tty->size;
    write(1, tty->buffer, tty->size);
}

void handle_upper_arr(tty_t *tty, shell_data_t *data)
{
    erase_line(tty);
    free(tty->buffer);
    if (tty->history > 0)
        (tty->history)--;
    tty->buffer = strdup(data->user_data->history[tty->history]);
    tty->size = strlen(tty->buffer);
    tty->cursor = tty->size;
    write(1, tty->buffer, tty->size);
}

void handle_down_arr(tty_t *tty, shell_data_t *data)
{
    erase_line(tty);
    free(tty->buffer);
    if (tty->history < data->user_data->history_len - 1)
        (tty->history)++;
    tty->buffer = strdup(data->user_data->history[tty->history]);
    tty->size = strlen(tty->buffer);
    tty->cursor = tty->size;
    write(1, tty->buffer, tty->size);
}

void handle_history_arr(tty_t *tty, shell_data_t *shell_data, char c)
{
    if (c == 'A' && tty->history > 0)
        handle_upper_arr(tty, shell_data);
    if (c == 'B' && tty->history == shell_data->user_data->history_len - 1)
        handle_back_to_buff(tty, shell_data);
    else if (c == 'B' && tty->history < shell_data->user_data->history_len - 1)
        handle_down_arr(tty, shell_data);
}
