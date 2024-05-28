/*
** EPITECH PROJECT, 2024
** board_utils.c
** File description:
** Utils for the board
*/

#include "../include/my.h"
#include "../include/navy.h"

static void print_board_header(void)
{
    my_printf("%c|%.*s\n", ' ', BOARD_SIZE * 2 - 1,
        "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
    my_printf("%c+%.*s\n", '-', BOARD_SIZE * 2 - 1,
        "---------------------------------------------------");
}

void print_board(n_board *board)
{
    size_t i = 0;
    size_t j;
    size_t line_len = BOARD_SIZE * 2;
    char line[line_len];

    print_board_header();
    my_memset(line, ' ', line_len);
    line[line_len] = '\0';
    while (i < BOARD_SIZE){
        j = 0;
        while (j < BOARD_SIZE){
            line[j * 2] = board->tiles[i][j];
            j ++;
        }
        my_printf("%c|%.*s\n", i + '1', line_len - 1, line);
        i ++;
    }
}
