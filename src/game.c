/*
** EPITECH PROJECT, 2024
** game.c
** File description:
** game itself
*/

#include "../include/my.h"
#include "../include/navy.h"

static void print_both_boards(n_game *game)
{
    my_printf("my_navy:\n");
    print_board(&game->our);
    my_printf("\nenemy navy:\n");
    print_board(&game->theirs);
    my_putstr("\n");
}

static int check_coords(n_game *game, int *x, int *y)
{
    if (x[0] >= 0 && x[0] < BOARD_SIZE && y[0] >= 0 && y[0] < BOARD_SIZE)
        if (game->theirs.tiles[y[0]][x[0]] == '.')
            return (1);
    return (0);
}

static void get_coords(n_game *game, int *x, int *y)
{
    char *line = NULL;
    int first = 1;

    while (true){
        if (first)
            first = 0;
        else
            my_printf("wrong position\n\n");
        my_printf("attack: ");
        line = get_next_line(0);
        my_printf("\n\n");
        if (my_strlen(line) != 3)
            continue;
        x[0] = line[0] - 'A';
        y[0] = line[1] - '1';
        free(line);
        if (check_coords(game, x, y))
            break;
    }
}

static void print_result(int x, int y, int hit)
{
    my_printf("result: %c%c:", x + 'A', y + '1');
    if (hit)
        my_printf("hit\n\n");
    else
        my_printf("missed\n\n");
}

static void add_attack(n_board *board, int x, int y, int hit)
{
    board->tiles[y][x] = hit ? 'x' : 'o';
}

static int attack(n_game *game)
{
    int x;
    int y;
    int hit;

    get_coords(game, &x, &y);
    send_int(game->pid, x);
    send_int(game->pid, y);
    hit = get_int();
    game->my_hits += hit;
    add_attack(&game->theirs, x, y, hit);
    print_result(x, y, hit);
    send_int(game->pid, game->my_hits == game->possible_hits);
    return (game->my_hits == game->possible_hits);
}

static int defend(n_game *game)
{
    int x;
    int y;
    int hit;

    my_printf("waiting for enemy's attack...\n\n");
    x = get_int();
    y = get_int();
    hit = game->our.tiles[y][x] != '.';
    add_attack(&game->our, x, y, hit);
    print_result(x, y, hit);
    send_int(game->pid, hit);
    return (get_int());
}

static int turn(n_game *game)
{
    if (game->host){
        if (attack(game))
            return (0);
        if (defend(game))
            return (1);
    } else {
        if (defend(game))
            return (1);
        if (attack(game))
            return (0);
    }
    return (-1);
}

int gameloop(n_game *game)
{
    int code;

    game->my_hits = 0;
    while (true){
        print_both_boards(game);
        code = turn(game);
        if (code == 0)
            my_printf("I won\n");
        if (code == 1)
            my_printf("Enemy won\n");
        if (code != -1)
            return (code);
    }
}
