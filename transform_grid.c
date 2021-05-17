#include "header.h"

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

	side = grid->side;
	points_array = grid->points_3d;

	for (r = 0; r < side; r++)
		for (c = 0; c < side; c++)
		{
			points_array[r][c].x *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
			points_array[r][c].y *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
			points_array[r][c].z *=
				direction == SDLK_f ? ZOOM : 1 / ZOOM;
		}

	grid->points_3d = points_array;
	iso_2d_conv(grid);
}

/**
 * move_camera - Moves the camera in the x and y axis.
 * @grid: The grid structure to modify its position to appear to be moving
 *        the camera.
 * @direction: The direction of the camera movement (i = up, k = down,
 *             j = left, l = right).
 */
void move_camera(grid_t *grid, int direction)
{
	long int r, c, side;
	coord_2d_t **iso_points;

	side = grid->side;
	iso_points = grid->iso_2d;

	if (direction == SDLK_i)
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
				iso_points[r][c].y -= CAM_MOVEMENT;

	if (direction == SDLK_k)
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
				iso_points[r][c].y += CAM_MOVEMENT;

	if (direction == SDLK_j)
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
				iso_points[r][c].x -= CAM_MOVEMENT;

	if (direction == SDLK_l)
		for (r = 0; r < side; r++)
			for (c = 0; c < side; c++)
				iso_points[r][c].x += CAM_MOVEMENT;

	grid->iso_2d = iso_points;
}
