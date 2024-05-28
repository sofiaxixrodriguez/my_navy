/*
** EPITECH PROJECT, 2024
** navy.c
** File description:
** Blow some ships up
*/

#include "../include/my.h"
#include "../include/navy.h"

static int print_usage(void)
{
    my_putstr("USAGE\n\t./my_navy [first_player_pid] navy_positions\n");
    my_putstr("DESCRIPTION\n\tfirst_player_pid: only for the 2nd ");
    my_putstr("player. pid of the first player.\n\tnavy_positions: ");
    my_putstr("file representing the positions of the ships.\n");
    return (0);
}

int main(int argc, char **argv)
{
    n_game game;
    int code = -1;

    if (argc == 2 && my_strcmp("-h", argv[1]) == 0)
        return (print_usage());
    setup_signals();
    if (argc != 2 && argc != 3) {
        my_dprintf(2, "Incorrect amount of arguments\n");
        return (84);
    } else if (argc == 3)
        code = prepare_game(&game, argv[2], argv[1]);
    else
        code = prepare_game(&game, argv[1], NULL);
    if (code == 0){
        my_dprintf(2, "Error preparing the board\n");
        return (84);
    }
    return (gameloop(&game));
}
