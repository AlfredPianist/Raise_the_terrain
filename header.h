#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Window properties */
#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)

/* Grid properties */
#define X_3D_DIST (16)
#define Y_3D_DIST (9)
#define X_ISO_OFFSET (WINDOW_WIDTH / 2)
#define Y_ISO_OFFSET (WINDOW_HEIGHT / 2)
#define X_INCLINATION (0.8)
#define Y_INCLINATION (0.7)
#define ROTATION_ANGLE (2)

/**
 * struct SDL_Instance - structure with an instance of SDL.
 * @window: The SDL Window.
 * @renderer: The SDL Renderer
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct coord_3d_s - structure with a set of 3d coordinates (x, y and z).
 * @x: The x coordinate.
 * @y: The y coordinate.
 * @z: The z coordinate.
 */
typedef struct coord_3d_s
{
	float x;
	float y;
	float z;
} coord_3d_t;

/**
 * struct coord_2d_s - structure with a set of 2d coordinates (x and y).
 * @x: The x coordinate.
 * @y: The y coordinate.
 */
typedef struct coord_2d_s
{
	float x;
	float y;
} coord_2d_t;

/**
 * struct grid_s - structure with the grid information to be operated and drawn
 *                 on the SDL Instance.
 * @side: The side of the grid.
 * @darray: The array of arrays of numbers taken from the file. These represent
 *          the altitudes of each point (the z coordinate in 3d).
 * @points_3d: The array of 3d coordinates calculated after storing the
 *             altitudes array.
 * @iso_2d: The array of 2d coordinates which represent the isometric
 *          projection of the 3d ones.
 */
typedef struct grid_s
{
	long int side;
	float **darray;
	coord_3d_t **points_3d;
	coord_2d_t **iso_2d;
} grid_t;

/* SDL Instance manipulation - instance.c */
int init_instance(SDL_Instance *instance);
void destroy_instance(SDL_Instance *instance);

/* Event coordination - events.c */
int poll_events(void);

/* File reading and manipulation - input.c */
short check_token(char *token);
void print_darray(grid_t *grid);
void free_grid(grid_t *grid);
void darray_side(char *file_path, grid_t *grid);
void darray_from_file(char *file_path, grid_t *grid);

/* Grid calculation, transformation and projection - draw_grid.c */
void print_coord(grid_t *grid, char *type);
void array_3d_coord(grid_t *grid);
void rotate_grid(grid_t *grid, int direction);
void iso_2d_conv(grid_t *grid);
void draw_grid(grid_t *grid, SDL_Instance *instance);

#endif
