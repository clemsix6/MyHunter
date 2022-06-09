/*
** EPITECH PROJECT, 2021
** Bistromatic
** File description:
** my_itoa.c
*/

#include <stdbool.h>
#include <stdlib.h>

void my_itoa(int nb, char *buffer, int index)
{
    int units;

    if (nb < 0) {
        buffer[index++] = ('-');
        nb = nb * (-1);
    }
    if (nb < 10) {
        buffer[index++] = (nb + 48);
    }
    else {
        units = (nb % 10);
        nb = (nb - units) / 10;
        buffer[index++] = (nb + 48);
        buffer[index++] = (units + 48);
    }
}
