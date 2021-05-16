#include "header.h"

/**
 * poll_events - The event coordination (keyboard actions).
 *
 * Return: The key value pressed, or 1 if 'Esc' key pressed or closed
 *         the SDL Window.
 */
int poll_events(void)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			/* If 'Esc' is pressed */
			if (key.keysym.sym == SDLK_ESCAPE)
				return (1);
			/* If right direction key or 'D' is pressed */
			if (key.keysym.sym ==  SDLK_RIGHT ||
			    key.keysym.sym == SDLK_d)
				return (SDLK_RIGHT);
			/* If left direction key or 'A' is pressed */
			if (key.keysym.sym == SDLK_LEFT ||
			    key.keysym.sym == SDLK_a)
				return (SDLK_LEFT);
			/* If up direction key or 'W' is pressed */
			if (key.keysym.sym == SDLK_UP ||
			    key.keysym.sym == SDLK_w)
				return (SDLK_UP);
			/* If down direction key or 'S' is pressed */
			if (key.keysym.sym == SDLK_DOWN ||
			    key.keysym.sym == SDLK_s)
				return (SDLK_DOWN);
			break;
		}
	}

	return (0);
}
