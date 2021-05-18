#include "header.h"

/**
 * print_coord - Prints coordinates either 2d or 3d ones.
 * @grid: The grid structure.
 * @type: The type of coordinates to be printed, either 2D or 3D.
 */
void print_coord(grid_t *grid, char *type)
{
	long int r, c, counter, side;
	coord_3d_t **points_array;
	coord_2d_t **iso_points;

	points_array = grid->points_3d ? grid->points_3d : NULL;
	iso_points = grid->iso_2d ? grid->iso_2d : NULL;
	side = grid->side;

	if (strcmp(type, "3D") == 0 && points_array)
	{
		for (r = 0, counter = 1; r < side; r++)
			for (c = 0; c < side; c++)
			{
				printf("coord %ld: ", counter++);
				printf("x = %.2f ", points_array[r][c].x);
				printf("y = %.2f ", points_array[r][c].y);
				printf("z = %.2f\n", points_array[r][c].z);
			}
		return;
	}

	if (strcmp(type, "2D") == 0 && iso_points)
	{
		for (r = 0, counter = 1; r < side; r++)
			for (c = 0; c < side; c++)
			{
				printf("coord %ld: ", counter++);
				printf("x = %.2f ", iso_points[r][c].x);
				printf("y = %.2f\n", iso_points[r][c].y);
			}
		return;
	}
}

/**
 * rotate_grid - Rotates the grid in either axis (x, y or z).
 * @grid: The grid structure to calculate the new position of the rotated
 *        3d points.
 * @direction: The direction given as input (up, down, right or left, q or e).
 */
void rotate_grid(grid_t *grid, int direction)
{
	float angle, x_point, y_point, z_point, **darray, z_point_darray;
	long int r, c, side;
	coord_3d_t **points_array;

	side = grid->side;
	points_array = grid->points_3d;
	darray = grid->darray;

	angle = direction == SDLK_LEFT || direction == SDLK_UP ||
		direction == SDLK_e ?
		ROTATION_ANGLE * M_PI / 180 : ROTATION_ANGLE * -(M_PI / 180);

	if (direction == SDLK_LEFT || direction == SDLK_RIGHT)
	{
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
			{
				x_point = points_array[r][c].x;
				y_point = points_array[r][c].y;
				points_array[r][c].x = (x_point * cos(angle)) -
					(y_point * sin(angle));
				points_array[r][c].y = (x_point * sin(angle)) +
					(y_point * cos(angle));
			}
	}
	if (direction == SDLK_UP || direction == SDLK_DOWN)
	{
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
			{
				y_point = points_array[r][c].y;
				z_point = points_array[r][c].z;
				z_point_darray = darray[r][c];
				points_array[r][c].y = (y_point * cos(angle)) -
					(z_point * sin(angle));
				points_array[r][c].z = (y_point * sin(angle)) +
					(z_point * cos(angle));
				darray[r][c] = (y_point * sin(angle)) +
					(z_point_darray * cos(angle));
			}
	}
	if (direction == SDLK_e || direction == SDLK_q)
	{
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
			{
				x_point = points_array[r][c].x;
				z_point = points_array[r][c].z;
				z_point_darray = darray[r][c];
				points_array[r][c].x = (x_point * cos(angle)) -
					(z_point * sin(angle));
				points_array[r][c].z = (x_point * sin(angle)) +
					(z_point * cos(angle));
				darray[r][c] = (x_point * sin(angle)) +
					(z_point_darray * cos(angle));
			}
	}

	grid->points_3d = points_array;
	array_3d_coord_raise(grid);
}

/**
 * zoom_grid - Zooms grid in and out.
 * @grid: The grid structure to modify its dimensions to appear to be zooming.
 * @direction: The direction to be zooming (r = zoom in, f = zoom out).
 */
void zoom_grid(grid_t *grid, int direction)
{
	long int r, c, side;
	coord_3d_t **points_array;
	float **darray;

	side = grid->side;
	points_array = grid->points_3d;
	darray = grid->darray;

	for (r = 0; r < side; r++)
		for (c = 0; c < side; c++)
		{
			points_array[r][c].x *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
			points_array[r][c].y *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
			points_array[r][c].z *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
			darray[r][c] *= direction == SDLK_f ? ZOOM : 1 / ZOOM;
		}

	grid->points_3d = points_array;
	iso_2d_conv(grid);
}

/**
 * array_3d_coord_reinit - Reinitializes the array of 3d coordinates.
 * @grid: The grid structure.
 */
void array_3d_coord_reinit(grid_t *grid)
{
	long int r, c, side;
	coord_3d_t **points_array;
	float x_dist, y_dist, **darray, **darray_orig;

	side = grid->side;
	points_array = grid->points_3d;
	darray = grid->darray;
	darray_orig = grid->darray_orig;

	x_dist = WINDOW_WIDTH / (side + X_3D_DIST);
	y_dist = WINDOW_HEIGHT / (side + Y_3D_DIST);

	for (r = 0; r < side; r++)
	{
		for (c = 0; c < side; c++)
		{
			points_array[r][c].x = (x_dist * r) -
				((x_dist * side) / 2);
			points_array[r][c].y = (y_dist * c) -
				((y_dist * side) / 2);
			points_array[r][c].z = 0;
			darray[r][c] = darray_orig[r][c];
		}
	}

	grid->points_3d = points_array;
	grid->darray = darray;
	iso_2d_conv(grid);
}
