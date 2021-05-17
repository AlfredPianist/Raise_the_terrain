#include "header.h"

/**
 * init_instance - Initializes an SDL instance.
 * @instance: The SDL Instance to be initialized.
 *
 * Return: 0 if successful, 1 if errors are present.
 */
int init_instance(SDL_Instance *instance)
{
	Uint32 renderer_flags = SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n",
			SDL_GetError());
		return (1);
	}

	/* Create a new Window instance */
	instance->window = SDL_CreateWindow("Raise the terrain",
					    SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!instance->window)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* Create a new Renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						renderer_flags);
	if (!instance->renderer)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (1);
	}

	return (0);
}

/**
 * destroy_instance - Cleans and quits SDL.
 * @instance: The SDL instance to be destroyed.
 */
void destroy_instance(SDL_Instance *instance)
{
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	SDL_Quit();
}
