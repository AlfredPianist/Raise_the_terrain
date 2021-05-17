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
 * array_3d_coord_init - Creates the array of 3d coordinates from the
 *                       calculation of the side of the grid.
 * @grid: The grid structure.
 */
void array_3d_coord_init(grid_t *grid)
{
	long int r, c, side;
	coord_3d_t **points_array;
	float x_dist, y_dist;
	char *err;

	side = grid->side;
	err = "Error: cannot allocate memory to array\n";

	points_array = malloc(sizeof(*points_array) * side);
	if (!points_array)
	{
		fprintf(stderr, "%s", err);
		exit(EXIT_FAILURE);
	}

	x_dist = WINDOW_WIDTH / (side + X_3D_DIST);
	y_dist = WINDOW_HEIGHT / (side + Y_3D_DIST);

	for (r = 0; r < side; r++)
	{
		points_array[r] = malloc(sizeof(**points_array) *
					 side);
		if (!points_array[r])
		{
			fprintf(stderr, "%s", err);
			exit(EXIT_FAILURE);
		}
		for (c = 0; c < side; c++)
		{
			points_array[r][c].x = (x_dist * r) -
				((x_dist * side) / 2);
			points_array[r][c].y = (y_dist * c) -
				((y_dist * side) / 2);
			points_array[r][c].z = 0;
		}
	}

	grid->points_3d = points_array;
	iso_2d_conv(grid);
}

/**
 * array_3d_coord_raise - Projects the z value to the altitude specified in
 *                        the file stored in the darray array of arrays.
 * @grid: The grid structure.
*/
void array_3d_coord_raise(grid_t *grid)
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
			if (points_array[r][c].z < darray[r][c])
				points_array[r][c].z += Z_RAISE_INCREMENT;
			if (points_array[r][c].z > darray[r][c])
				points_array[r][c].z -= Z_RAISE_INCREMENT;
		}

	grid->points_3d = points_array;
	iso_2d_conv(grid);
}

/**
 * iso_2d_conv - Converts the array of 3d coordinates to an isometric
 *               projection of 2d coordinates and stores that array into
 *               the grid structure.
 * @grid: The grid structure.
 */
void iso_2d_conv(grid_t *grid)
{
	long int r, c, side;
	coord_3d_t **points_array;
	coord_2d_t **iso_points;
	char *err;

	side = grid->side;
	points_array = grid->points_3d;
	err = "Error: cannot allocate memory to array\n";

	iso_points = malloc(sizeof(*iso_points) * side);
	if (!iso_points)
	{
		fprintf(stderr, "%s", err);
		exit(EXIT_FAILURE);
	}

	for (r = 0; r < side; r++)
	{
		iso_points[r] = malloc(sizeof(**iso_points) * side);
		if (!iso_points[r])
		{
			fprintf(stderr, "%s", err);
			exit(EXIT_FAILURE);
		}
		for (c = 0; c < side; c++)
		{
			iso_points[r][c].x = X_ISO_OFFSET +
				(X_INCLINATION *
				(points_array[r][c].y - points_array[r][c].x));
			iso_points[r][c].y = Y_ISO_OFFSET +
				(((1 - Y_INCLINATION) *
				(points_array[r][c].y + points_array[r][c].x)) -
				 points_array[r][c].z);
		}
	}

	grid->iso_2d = iso_points;
}

/**
 * draw_grid - Draws the calculated isometric 2d projection to the SDL
 *             Instance.
 * @grid: The grid structure.
 * @instance: The SDL instance.
 */
void draw_grid(grid_t *grid, SDL_Instance *instance)
{
	long int r, c, side;
	coord_2d_t **iso_points;

	side = grid->side;
	iso_points = grid->iso_2d;

	for (r = 0; r < side; r++)
		for (c = 0; c < side; c++)
		{
			if (r + 1 < side)
			{
				/* Vertical Lines */
				SDL_RenderDrawLine(instance->renderer,
						   iso_points[r][c].x,
						   iso_points[r][c].y,
						   iso_points[r + 1][c].x,
						   iso_points[r + 1][c].y);
			}
			if (c + 1 < side)
			{
				/* Horizontal Lines */
				SDL_RenderDrawLine(instance->renderer,
						   iso_points[r][c].x,
						   iso_points[r][c].y,
						   iso_points[r][c + 1].x,
						   iso_points[r][c + 1].y);
			}
		}
}
