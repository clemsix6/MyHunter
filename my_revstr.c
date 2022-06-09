/*
** EPITECH PROJECT, 2021
** LIB
** File description:
** revstr
*/

int my_strlen (const char *);

char * my_revstr (char *str)
{
    int size = my_strlen(str);
    char copy[size];

    for (int i = 0; i < size; i++) {
        copy[i] = str[i];
    }
    for (int j = 0; j < size; j++) {
        str[size - j - 1] = copy[j];
    }
    return str;
}
