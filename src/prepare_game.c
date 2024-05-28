/*
** EPITECH PROJECT, 2024
** prepare_game.c
** File description:
** Prepare the structs
*/

#include <unistd.h>
#include <fcntl.h>
#include "../include/my.h"
#include "../include/navy.h"

static int insert_boat(n_board *board, n_boat *boat)
{
    tile pos = {boat->start.x, boat->start.y};
    tile vel = {boat->end.x - boat->start.x, boat->end.y - boat->start.y};

    if (vel.x * vel.y != 0)
        return (0);
    if (vel.x == 0)
        vel.y /= ABS(vel.y);
    else
        vel.x /= ABS(vel.x);
    while (pos.x - vel.x != boat->end.x || pos.y - vel.y != boat->end.y) {
        if (board->tiles[pos.y][pos.x] != '.')
            return (0);
        board->tiles[pos.y][pos.x] = '0' + boat->size;
        pos.x += vel.x;
        pos.y += vel.y;
    }
    return (1);
}

static int check_format(char **values)
{
    size_t i = 0;

    if (values == NULL)
        return (0);
    while (values[i])
        i ++;
    if (i != 3)
        return (0);
    return (my_strlen(values[1]) == 2 &&
        my_strlen(values[2]) == 2 + (values[2][2] == '\n'));
}

static n_boat parse_boat(char *line)
{
    n_boat boat = {{0, 0}, {0, 0}, 0};
    char **values = my_split(line, ':');

    free(line);
    if (!check_format(values)){
        free_string_array(values);
        return (boat);
    }
    boat.start.x = values[1][0] - 'A';
    boat.start.y = values[1][1] - '1';
    boat.end.x = values[2][0] - 'A';
    boat.end.y = values[2][1] - '1';
    boat.size = my_getnbr(values[0]);
    boat.size *= (size_t)my_intlen(boat.size) == my_strlen(values[0]);
    free_string_array(values);
    return (boat);
}

static int read_boat_file(n_board *board, char *path)
{
    size_t i = 0;
    int fd = open(path, O_RDONLY);
    char *line;
    n_boat b;

    do {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        b = parse_boat(line);
        if (b.size < 2)
            return (0);
        if (board->boats[b.size - 2].size != 0)
            return (0);
        board->boats[b.size - 2] = b;
        if (!insert_boat(board, &b))
            return (0);
        i ++;
    } while (line);
    return (i == BOATS);
}

static void clear_board(n_board *board)
{
    size_t i = 0;
    size_t j;

    while (i < BOARD_SIZE){
        j = 0;
        while (j < BOARD_SIZE){
            board->tiles[i][j] = '.';
            j ++;
        }
        i ++;
    }
    i = 0;
    while (i < BOATS){
        board->boats[i] = (n_boat){{0, 0}, {0, 0}, 0};
        i ++;
    }
}

static int stablish_connection(n_game *game, char *host)
{
    my_printf("my_pid: %d\n\n", getpid());
    if (game->host){
        my_printf("waiting for enemy...\n\n");
        game->pid = get_int();
        my_printf("enemy connected\n");
    } else {
        game->pid = my_getnbr(host);
        send_int(game->pid, getpid());
        my_printf("successfully connected\n");
    }
    send_int(game->pid, BOARD_SIZE);
    if (get_int() != BOARD_SIZE){
        my_printf("uncompatible enemy (board size differs)\n");
        return (0);
    }
    return (1);
}

int prepare_game(n_game *game, char *path, char *host)
{
    size_t max_size = BOATS + 1;

    game->host = host == NULL;
    game->possible_hits = ((max_size * max_size) + max_size) / 2 - 1;
    clear_board(&game->our);
    clear_board(&game->theirs);
    if (!read_boat_file(&game->our, path))
        return (0);
    return (stablish_connection(game, host));
}
