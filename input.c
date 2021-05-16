#include "header.h"

/**
 * check_token - Checks if a token is a number.
 * @token: The token to be checked.
 *
 * Return: 0 if number, 1 if not.
 */
short check_token(char *token)
{
	long int i = 0;

	for (i = 0; token[i]; i++)
		if (!(token[i] == '-' || token[i] == '.' ||
		      (token[i] >= '0' && token[i] <= '9')))
			return (1);
	return (0);
}

/**
 * print_darray - Prints the array of array of numbers stored from the file.
 * @grid: The grid.
 */
void print_darray(grid_t *grid)
{
	long int i, j, side;

	side = grid->side;
	for (i = 0; i < side; i++)
	{
		for (j = 0; j < side; j++)
			printf("%.2f ", grid->darray[i][j]);
		printf("\n");
	}
}

/**
 * free_grid - Frees everything malloc'ed in the grid's struct.
 * @grid: The grid.
 */
void free_grid(grid_t *grid)
{
	long int i, side;

	side = grid->side;
	for (i = 0; i < side; i++)
	{
		free(grid->darray[i]);
		free(grid->points_3d[i]);
		free(grid->iso_2d[i]);
	}
	free(grid->darray);
	free(grid->points_3d);
	free(grid->iso_2d);
	free(grid);
}

/**
 * darray_side - Determines the side of the array of arrays of numbers.
 * @file_path: The path of the file to calculate its side.
 * @grid: The grid structure to store its side.
 */
void darray_side(char *file_path, grid_t *grid)
{
	FILE *file = NULL;
	char *line = NULL, *token = NULL, *err;
	size_t line_length = 0;
	long int side = 0, elements = 0;

	err = "Error: grid side must be equal in width and height.\n";

	file = fopen(file_path, "r");
	if (!file)
	{
		fprintf(stderr, "Error opening file %s.\n", file_path);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &line_length, file) != -1)
	{
		side++;
		token = strtok(line, " ");
		if (token && check_token(token))
		{
			fprintf(stderr, "Error: number not valid.\n");
			free(line);
			fclose(file);
			exit(EXIT_FAILURE);
		}
		elements = token ? elements + 1 : elements;
		while (token)
		{
			token = strtok(NULL, " \n");
			if (token && check_token(token))
			{
				fprintf(stderr, "Error: number not valid.\n");
				free(line);
				fclose(file);
				exit(EXIT_FAILURE);
			}
			elements = token ? elements + 1 : elements;
		}
	}

	if (elements / side != side)
	{
		fprintf(stderr, "%s", err);
		exit(EXIT_FAILURE);
	}

	grid->side = side;

	free(line);
	fclose(file);
}

/**
 * darray_from_file - Copies the file's information and creates an array of
 *                    arrays of numbers, storing it in the grid structure.
 * @file_path: The path of the file to copy the information.
 * @grid: The grid structure to store the array.
 */
void darray_from_file(char *file_path, grid_t *grid)
{
	FILE *file = NULL;
	char *line = NULL, *token = NULL, *err;
	size_t line_length = 0;
	float **altitude_array = NULL;
	long int row = 0, column = 0;

	err = "Error: cannot allocate memory to array\n";

	darray_side(file_path, grid);

	altitude_array = malloc(sizeof(*altitude_array) * grid->side);
	if (!altitude_array)
	{
		fprintf(stderr, "%s", err);
		exit(EXIT_FAILURE);
	}

	file = fopen(file_path, "r");
	if (!file)
	{
		fprintf(stderr, "Error opening file %s\n", file_path);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &line_length, file) != -1)
	{
		altitude_array[row] = malloc(sizeof(**altitude_array) *
					     grid->side);
		if (!altitude_array[row])
		{
			fprintf(stderr, "%s", err);
			exit(EXIT_FAILURE);
		}
		column = 0;
		token = strtok(line, " \n");
		do {
			altitude_array[row][column++] = atof(token);
			token = strtok(NULL, " \n");
		} while (token);
		row++;
	}

	grid->darray = altitude_array;

	free(line);
	fclose(file);
}
