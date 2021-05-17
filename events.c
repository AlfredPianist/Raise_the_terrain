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
	SDL_Keycode key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key.keysym.sym;
			/* If 'Esc' is pressed */
			if (key == SDLK_ESCAPE)
				return (1);
			/* If right direction key or 'D' is pressed */
			if (key ==  SDLK_RIGHT || key == SDLK_d)
				return (SDLK_RIGHT);
			/* If left direction key or 'A' is pressed */
			if (key == SDLK_LEFT || key == SDLK_a)
				return (SDLK_LEFT);
			/* If up direction key or 'W' is pressed */
			if (key == SDLK_UP || key == SDLK_w)
				return (SDLK_UP);
			/* If down direction key or 'S' is pressed */
			if (key == SDLK_DOWN || key == SDLK_s)
				return (SDLK_DOWN);
			/* If 'Q' is pressed */
			if (key == SDLK_q)
				return (SDLK_q);
			/* If 'E' is pressed */
			if (key == SDLK_e)
				return (SDLK_e);
			/* If page up key or 'R' is pressed */
			if (key == SDLK_r || key == SDLK_PAGEUP)
				return (SDLK_r);
			/* If page down key or 'F' is pressed */
			if (key == SDLK_f || key == SDLK_PAGEDOWN)
				return (SDLK_f);
			/* If 'O' is pressed */
			if (key == SDLK_o)
				return (SDLK_o);
			/* If 'I' is pressed */
			if (key == SDLK_i)
				return (SDLK_i);
			/* If 'K' is pressed */
			if (key == SDLK_k)
				return (SDLK_k);
			/* If 'J' is pressed */
			if (key == SDLK_j)
				return (SDLK_j);
			/* If 'L' is pressed */
			if (key == SDLK_l)
				return (SDLK_l);
			break;
		}
	}

	return (0);
}
