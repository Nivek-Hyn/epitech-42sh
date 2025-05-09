/*
** EPITECH PROJECT, 2025
** colors
** File description:
** colors
*/

#ifndef COLORS_H
    #define COLORS_H

    #define ESC_CHAR        "\x1B"

    // Regular
    #define COL_REG         "0"
    // Bold
    #define COL_BOLD        "1"
    // High Intensity Background
    #define COL_HIBK        "4"
    // High Intensity Text
    #define COL_HITX        "0"
    // High Intensity Bold Text
    #define COL_HIBT        "1"

    // Black
    #define COL_BLK ESC_CHAR "[" COL_REG ";30m"
    // Red
    #define COL_RED ESC_CHAR "[" COL_REG ";31m"
    // Green
    #define COL_GRN ESC_CHAR "[" COL_REG ";32m"
    // Yellow
    #define COL_YEL ESC_CHAR "[" COL_REG ";33m"
    // Blue
    #define COL_BLU ESC_CHAR "[" COL_REG ";34m"
    // Magenta
    #define COL_MAG ESC_CHAR "[" COL_REG ";35m"
    // Cyan
    #define COL_CYN ESC_CHAR "[" COL_REG ";36m"
    // White
    #define COL_WHT ESC_CHAR "[" COL_REG ";37m"

    // Black (Bold)
    #define COL_BLK_B ESC_CHAR "[" COL_BOLD ";30m"
    // Red (Bold)Z
    #define COL_RED_B ESC_CHAR "[" COL_BOLD ";31m"
    // Green (Bold)
    #define COL_GRN_B ESC_CHAR "[" COL_BOLD ";32m"
    // Yellow (Bold)
    #define COL_YEL_B ESC_CHAR "[" COL_BOLD ";33m"
    // Blue (Bold)
    #define COL_BLU_B ESC_CHAR "[" COL_BOLD ";34m"
    // Magenta (Bold)
    #define COL_MAG_B ESC_CHAR "[" COL_BOLD ";35m"
    // Cyan (Bold)
    #define COL_CYN_B ESC_CHAR "[" COL_BOLD ";36m"
    // White (Bold)
    #define COL_WHT_B ESC_CHAR "[" COL_BOLD ";37m"

    // Reset
    #define COL_RESET       ESC_CHAR "[0m"

#endif
