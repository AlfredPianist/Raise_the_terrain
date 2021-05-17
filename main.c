#include "header.h"

/**
 * main - Raise the Terrain
 * @argc: The argument count.
 * @argv: The argument vector.
 *
 * Description: Raise the Terrain reads a file with grid point altitudes and
 *              proceeds to display said altitudes in an isometric
 *              projection. It can also rotate the grid left, right, up or down
 *              with the direction keys or WASD keys.
 * Return: 0 if success, 1 if failure
 */
int main(int argc, char *argv[])
{
	SDL_Instance instance;
	grid_t *grid;
	int key;

	if (argc != 2)
	{
		fprintf(stdout, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* File opening, reading and grid generation */
	grid = malloc(sizeof(*grid));
	darray_from_file(argv[1], grid);
	array_3d_coord_init(grid);

	/* SDL Instance creation */
	if (init_instance(&instance) != 0)
		exit(EXIT_FAILURE);

	/* Infinite loop: drawing and event coordination */
	while (1)
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);

		array_3d_coord_raise(grid);
		key = poll_events();

		/* Exit program */
		if (key == 1)
			break;
		/* Rotate grid */
		if (key == SDLK_RIGHT || key == SDLK_LEFT ||
		    key == SDLK_UP || key == SDLK_DOWN ||
		    key == SDLK_q || key == SDLK_e)
			rotate_grid(grid, key);
		/* Zoom grid */
		if (key == SDLK_r || key == SDLK_f)
			zoom_grid(grid, key);

		SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF,
				       0XFF, 0XFF);
		draw_grid(grid, &instance);
		SDL_RenderPresent(instance.renderer);
	}

	/* SDL Instance destruction */
	destroy_instance(&instance);

	/* Grid freeing */
	free_grid(grid);

	exit(EXIT_SUCCESS);
}
