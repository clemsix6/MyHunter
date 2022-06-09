/*
** EPITECH PROJECT, 2021
** MyHunter
** File description:
** my_hunter.h
*/

#ifndef MYHUNTER_MY_HUNTER_H
#define MYHUNTER_MY_HUNTER_H

#include <SFML/Graphics.h>
#include <stdbool.h>

const int max_object_count = 1024;
sfText *text;
int score = 0;
bool started = false;

struct s_sprite{
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    bool has_animation;
    sfVector2i offset;
    sfVector2i max_sheet_size;
    float next_animation_time;
    float animation_delta_time;
    bool destroy_on_end;
};

struct s_object{
    struct s_sprite sprite;
    int type_id;
    sfVector2f position;
    sfVector2f base_position;
    sfVector2f scale;
    sfVector2f rotation;
};
typedef struct s_object object;

#endif //MYHUNTER_MY_HUNTER_H
