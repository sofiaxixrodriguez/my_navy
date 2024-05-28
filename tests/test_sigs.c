/*
** EPITECH PROJECT, 2024
** test_sigs.c
** File description:
** main to test sigs
*/

#include "../include/my.h"
#include "../include/navy.h"

int main(int argc, char **argv)
{
    setup_signals();
    my_printf("PID: %d\n", getpid());
    if (argc == 1)
        while (1)
            my_printf("Received: %d\n--------------------\n", get_int());
    else
        while (1)
            send_int(my_getnbr(argv[1]), my_getnbr(get_next_line(0)));
    return (0);
}
