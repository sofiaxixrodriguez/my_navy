/*
** EPITECH PROJECT, 2024
** signaling.c
** File description:
** Comunicate processes
*/

#include <signal.h>
#include "../include/navy.h"
#include "../include/my.h"

signaling sigs = {{}, 0, 0, 0};

static void receive_data(int sig)
{
    sigs.head = sigs.head << 1;
    sigs.head += sig == SIGUSR2;
    sigs.readed ++;
    if (sigs.readed != sizeof(int) * 8)
        return;
    sigs.readed = 0;
    if (sigs.used >= 10)
        return;
    sigs.buffer[sigs.used] = sigs.head;
    sigs.used ++;
}

void send_int(int pid, int data)
{
    size_t i = 0;

    while (i < sizeof(int) * 8){
        if (data & 0b10000000000000000000000000000000)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(100);
        data = data << 1;
        i ++;
    }
}

int get_int(void)
{
    int result;

    while (sigs.used == 0)
        usleep(10000000);
    result = sigs.buffer[0];
    my_memmove(sigs.buffer, sigs.buffer + (sizeof(int) * sigs.used),
        sizeof(int) * sigs.used);
    sigs.used --;
    return (result);
}

void setup_signals(void)
{
    signal(SIGUSR1, &receive_data);
    signal(SIGUSR2, &receive_data);
}
