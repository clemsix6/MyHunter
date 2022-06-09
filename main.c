#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System/Clock.h>
#include <math.h>
#include <stdio.h>
#include "my_hunter.h"

void my_itoa(int nbr, char *buffer, int index);

double fabs(double x)
{
    if (x < 0)
        return -x;
    return x;
}

bool insert_object(object **objects, object *obj)
{
    for (int i = 0; i < max_object_count; i++) {
        if (objects[i] == NULL) {
            objects[i] = obj;
            return true;
        }
    }
    return false;
}

bool push_object(object **objects, object *obj)
{
    for (int i = max_object_count - 1; i >= 0; i--) {
        if (objects[i] == NULL) {
            objects[i] = obj;
            return true;
        }
    }
    return false;
}

object *create_object(const char *file_path, sfVector2f position,
                   sfIntRect rect)
{
    object *obj = malloc(sizeof(struct s_object));
    obj->sprite.sprite = sfSprite_create();
    obj->sprite.texture = sfTexture_createFromFile(file_path, NULL);
    obj->sprite.next_animation_time = 0;
    obj->position = position;
    obj->sprite.rect = rect;
    obj->base_position = position;
    obj->sprite.has_animation = false;
    sfSprite_setTexture(obj->sprite.sprite, obj->sprite.texture, sfTrue);
    return obj;
}

void destroy_object(object *obj, object **objects)
{
    for (int i = 0; i < max_object_count; i++) {
        if (objects[i] != NULL && objects[i] == obj)
            objects[i] = NULL;
    }
    sfSprite_destroy(obj->sprite.sprite);
    sfTexture_destroy(obj->sprite.texture);
    free(obj);
}

void destroy_menu(object **objects)
{
    object *obj;

    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj != NULL && (obj->type_id == 5 || obj->type_id == 6))
            destroy_object(obj, objects);
    }
}

void destroy_planes(object **objects)
{
    object *obj;

    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj != NULL && obj->type_id < 2)
            destroy_object(obj, objects);
    }
}

void move_plane(object *obj, object **objects, float delta_time)
{
    if (obj->type_id == 0) {
        obj->position.x += 500 * delta_time;
        if (obj->position.x > 1600)
            destroy_object(obj, objects);
    } else {
        obj->position.x -= 500 * delta_time;
        if (obj->position.x < -450)
            destroy_object(obj, objects);
    }
    obj->position.y = obj->base_position.y + cosf(obj->position.x * 0.05f) * 35;
}

void move_animation_rect(object **objects, object *obj,
                         sfVector2i offset, sfVector2i max_value)
{
    obj->sprite.rect.left += offset.x;
    if (obj->sprite.rect.left >= max_value.x) {
        obj->sprite.rect.left = 0;
        obj->sprite.rect.top += offset.y;
        if (obj->sprite.rect.top >= max_value.y) {
            obj->sprite.rect.left = 0;
            obj->sprite.rect.top = 0;
            if (obj->sprite.destroy_on_end)
                destroy_object(obj, objects);
        }
    }
}

void update_animation(object **objects, object *obj, float total_time)
{
    if (!obj->sprite.has_animation)
        return;
    if (obj->sprite.next_animation_time < total_time) {
        obj->sprite.next_animation_time += obj->sprite.animation_delta_time;
        move_animation_rect(objects, obj, obj->sprite.offset,
                            obj->sprite.max_sheet_size);
    }
}

void update_text()
{
    char buffer[16] = "Score : ";
    my_itoa(score, buffer, 8);

    sfText_setString(text, buffer);
}

void update(object **objects, float delta_time,
            __attribute__((unused)) float total_time)
{
    object *obj;

    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj == NULL)
            continue;
        if (obj->type_id == 0 || obj->type_id == 1)
            move_plane(obj, objects, delta_time);
        update_animation(objects, obj, total_time);
    }
    update_text();
}

void render(sfRenderWindow *win ,object **objects)
{
    object *obj;

    sfRenderWindow_drawText(win, text, NULL);
    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj != NULL) {
            sfSprite_setTextureRect(obj->sprite.sprite, obj->sprite.rect);
            sfSprite_setScale(obj->sprite.sprite, obj->scale);
            sfSprite_setPosition(obj->sprite.sprite, obj->position);
            sfRenderWindow_drawSprite(win, obj->sprite.sprite, NULL);
        }
    }
}

void create_main_menu(object **objects)
{
    sfVector2f scale = {1, 1};
    sfVector2f play_position = {1600 / 2 - 471 / 2, 300};
    sfVector2f quit_position = {1600 / 2 - 471 / 2, 500};
    sfIntRect rect = {0, 0, 471, 126};
    object *play = create_object("play.png", play_position, rect);
    object *quit = create_object("quit.png", quit_position, rect);

    play->type_id = 5;
    play->scale = scale;
    quit->type_id = 6;
    quit->scale = scale;
    insert_object(objects, play);
    insert_object(objects, quit);
}

void create_explosion(sfVector2f position, object **objects)
{
    sfVector2f scale = {1, 1};
    sfIntRect rect = {0, 0, 128, 128};
    sfVector2i offset = {128, 128};
    sfVector2i max_value = {512, 512};
    object *obj = create_object("explosion.png", position, rect);

    position.x += 200;
    obj->scale = scale;
    obj->sprite.has_animation = true;
    obj->sprite.destroy_on_end = true;
    obj->sprite.animation_delta_time = 0.5f;
    obj->sprite.offset = offset;
    obj->sprite.max_sheet_size = max_value;
    obj->type_id = 4;
    insert_object(objects, obj);
}

void on_click(sfMouseButtonEvent event, object **objects, sfRenderWindow *window)
{
    object *obj;

    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj == NULL)
            continue;
        if (event.y >= (int)obj->position.y &&
            event.y <= (int)obj->position.y +
            fabs(obj->sprite.rect.height * obj->scale.x) &&
            event.x >= (int)obj->position.x &&
            event.x <= (int)obj->position.x +
            fabs((float)obj->sprite.rect.width * obj->scale.y)) {
            if (obj->type_id < 2) {
                create_explosion(obj->position, objects);
                destroy_object(obj, objects);
                sfMusic *music = sfMusic_createFromFile("boom.wav");
                sfMusic_play(music);
                score++;
            } else if (obj->type_id == 5) {
                destroy_menu(objects);
                started = true;
            } else if (obj->type_id == 6) {
                sfRenderWindow_close(window);
            }
        }
    }
}

void update_ui(sfMouseMoveEvent event, object **objects)
{
    object *obj;
    sfColor hover_color = {190, 190, 190, 255};

    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj != NULL && (obj->type_id == 5 || obj->type_id == 6))
            sfSprite_setColor(obj->sprite.sprite, sfWhite);
    }
    for (int i = 0; i < max_object_count; i++) {
        obj = objects[i];
        if (obj == NULL)
            continue;
        if (event.y >= (int)obj->position.y &&
            event.y <= (int)obj->position.y +
                       abs(obj->sprite.rect.height) &&
            event.x >= (int)obj->position.x &&
            event.x <= (int)obj->position.x +
                       abs(obj->sprite.rect.width)) {
            if (obj->type_id == 5 || obj->type_id == 6) {
                sfSprite_setColor(obj->sprite.sprite, hover_color);
            }
        }
    }
}

void move_cursor(sfMouseMoveEvent event, object **objects)
{
    for (int i = 0; i < max_object_count; i++) {
        if (objects[i] != NULL && objects[i]->type_id == 2) {
            object *obj = objects[i];
            float size = obj->sprite.rect.width;
            float scale = obj->scale.x;
            obj->position.x = event.x - size / 2 * scale;
            obj->position.y = event.y - size / 2 * scale;
        }
    }
}

void analyse_events(sfRenderWindow *window, object **objects, sfEvent event)
{
    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(window);
    } else if (event.type == sfEvtMouseButtonPressed) {
        on_click(event.mouseButton, objects, window);
    } else if (event.type == sfEvtMouseMoved) {
        move_cursor(event.mouseMove, objects);
        update_ui(event.mouseMove, objects);
    } else if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyEscape && started) {
            started = false;
            destroy_planes(objects);
            create_main_menu(objects);
        }
    }
}

void process_events(sfRenderWindow *win, object **objects)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        analyse_events(win, objects, event);
    }
}

void spawn_plane(object **objects)
{
    int type = rand() % 2;
    sfVector2f position = {-150, rand() % 1100};
    sfVector2i offset = {10, 150};
    sfVector2i max_value = {1, 600};
    sfIntRect rect = {0, 0, 423, 150};
    sfVector2f scale = {0.6f, 0.6f};

    if (type == 1) {
        position.x = 1600;
    }
    if (type == 1) {
        rect.left = rect.width;
        rect.width = -rect.width;
    }
    object *obj = create_object("helicopter.png", position, rect);
    obj->sprite.offset = offset;
    obj->sprite.max_sheet_size = max_value;
    obj->scale = scale;
    obj->type_id = type;
    obj->sprite.has_animation = true;
    obj->sprite.destroy_on_end = false;
    obj->sprite.animation_delta_time = 0.2f;
    sfMusic *music = sfMusic_createFromFile("vroum.wav");
    sfMusic_play(music);
    insert_object(objects, obj);
}

void add_background(object **objects)
{
    sfVector2f position = {0, 0};
    sfVector2f scale = {3, 3.2f};
    sfIntRect rect = {0, 0, 683, 384};

    object *obj = create_object("background.png", position, rect);
    obj->scale = scale;
    obj->type_id = 3;
    insert_object(objects, obj);
}

void add_cursor(object **objects)
{
    sfVector2f position = {300, 300};
    sfVector2f scale = {0.1f, 0.1f};
    sfIntRect rect = {0, 0, 512, 512};

    object *obj = create_object("reticule.png", position, rect);
    obj->scale = scale;
    obj->type_id = 2;
    insert_object(objects, obj);
}

void add_text()
{
    sfVector2f position = {25, 15};
    sfFont *font = sfFont_createFromFile("hugie.ttf");

    text = sfText_create();
    sfText_setCharacterSize(text, 96);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, "Score : ");
    sfText_setPosition(text, position);
    sfText_setFont(text, font);
}

void start(object **objects)
{
    add_background(objects);
    create_main_menu(objects);
    add_cursor(objects);
    add_text();
}

void init()
{
    sfVideoMode mode = {1600, 1200, 32};
    sfRenderWindow *win;
    object **objects = malloc(sizeof(object) * max_object_count);
    sfClock *clock;
    sfTime time;
    float delta_time = 0;
    float total_time = 0;
    float next_update = 0;

    clock = sfClock_create();
    win = sfRenderWindow_create(mode, "My Hunter", sfResize | sfClose, NULL);
    if (win == NULL) {
        exit(84);
    }
    start(objects);
    sfRenderWindow_setMouseCursorVisible(win, false);
    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        time = sfClock_getElapsedTime(clock);
        delta_time = time.microseconds / 1000000.0;
        sfClock_restart(clock);
        process_events(win, objects);
        total_time += delta_time;
        update(objects, delta_time, total_time);
        if (next_update < total_time) {
            next_update += 2 - ((float)score * 0.01f);
            if (started)
                spawn_plane(objects);
        }
        sfRenderWindow_clear(win, sfBlack);
        render(win, objects);
        if (started) sfRenderWindow_drawText(win, text, NULL);
        sfRenderWindow_display(win);
    }
    sfClock_destroy(clock);
    sfRenderWindow_destroy(win);
    free(objects);
}

int main(void)
{
    init();
}