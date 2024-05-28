/*
** EPITECH PROJECT, 2024
** navy.h
** File description:
** Navy tools
*/

#ifndef NAVY_H_
    #define NAVY_H_
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #ifndef BOARD_SIZE
        #define BOARD_SIZE 8
    #endif
    #ifndef BOATS
        #define BOATS (BOARD_SIZE - 4)
    #endif
    #if (BOARD_SIZE < 5) || (BOARD_SIZE >= 10)
        #error "The board size must be between 5 and 9."
    #endif

typedef struct signaling_buffer {
    int buffer[10];
    int used;
    size_t readed;
    int head;
} signaling;

typedef struct tile_container {
    ssize_t x;
    ssize_t y;
} tile;

typedef struct boat_container {
    tile start;
    tile end;
    size_t size;
} n_boat;

typedef struct board_container {
    char tiles[BOARD_SIZE][BOARD_SIZE];
    n_boat boats[BOATS];
} n_board;

typedef struct game_container {
    n_board our;
    n_board theirs;
    bool host;
    int pid;
    int my_hits;
    int possible_hits;
} n_game;

int prepare_game(n_game *game, char *path, char *host);
void print_board(n_board *board);
void setup_signals(void);
int get_int(void);
void send_int(int pid, int data);
int gameloop(n_game *game);

#endif
