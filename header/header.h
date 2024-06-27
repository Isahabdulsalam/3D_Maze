#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 600
#define MAP_X 8
#define MAP_Y 8
#define MAP_S 64
#define PI 3.14159265
#define FOV (PI / 3)
#define NUM_RAYS 60

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

/**
 * struct SDL_Context - structure for SDL context
 * @window: SDL window
 * @renderer: SDL renderer
 *
 * Description: structure to manage SDL window and renderer
**/
typedef struct SDL_Context
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Context;

/**
 * struct Keys - structure for keyboard input
 * @up: move up
 * @left: move left
 * @right: move right
 * @down: move down
 * @open: open door
 * @exit: exit game
 *
 * Description: structure to manage keyboard inputs
 **/
typedef struct Keys
{
    int up, left, right, down, open, exit;
} Keys;

/**
 * struct Player - structure for the player
 * @x: the x coordinate position
 * @y: the y coordinate position
 * @width: the width of the player
 * @height: the height of the player
 * @angle: angle of the player
 * @dx: delta x of the player
 * @dy: delta y of the player
 **/
typedef struct Player
{
    float x, y, width, height, angle, dx, dy;
} Player;

extern Player player;
extern float distance_buffer[NUM_RAYS];

/** main.c **/
void initialize_game(void);
void game_loop(SDL_Context context);

/** input.c **/
int handle_events(SDL_Context context);
void on_key_down(SDL_Context context);
void on_key_up(SDL_Event event);
void handle_door_event(void);

/** window.c **/
int create_window(SDL_Context *context);
float normalize_angle(float angle);

/** render.c **/
void render_player(SDL_Context context);
void render_map(SDL_Context context);
void render_scene(SDL_Context context, int column, float wall_height, float ray_angle, float shade,
                  float ray_x, float ray_y, int texture);

/** raycasting.c **/
void perform_raycasting(SDL_Context context);
int detect_wall(float ray_x, float ray_y);
void handle_horizontal_collision(float ray_angle, float *distance, float *hit_x, float *hit_y, int *hit);
void handle_vertical_collision(float ray_angle, float *distance, float *hit_x, float *hit_y, int *hit);
float calculate_distance(float x1, float y1, float x2, float y2);

/** texture.c **/
float get_texture_coordinate(int index);

/** map.c **/
void update_map_value(int x, int y, int value);
int get_map_value(int x, int y);
void generate_maze(int maze[MAP_X][MAP_Y]);

/** memory.c **/
void free_allocated_memory(void);

#endif /* MAZE_GAME_H */

