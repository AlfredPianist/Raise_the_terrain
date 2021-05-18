# Raise The Terrain

<div align="center">
  <p>
    Isometric projection of a square grid using the SDL2 Library and the C programming language.
  </p>
  <hr>
	<p>
		<img src="./gifs/0_Raise_the_terrain_demo_init.gif" alt="0_Raise_the_terrain_demo_init" style="zoom:25%;" />
		<img src="./gifs/1_Raise_the_terrain_demo_rot_z.gif" alt="1_Raise_the_terrain_demo_rot_z" style="zoom:25%;" />
	</p>
	<p>
		<img src="./gifs/2_Raise_the_terrain_demo_rot_y.gif" alt="2_Raise_the_terrain_demo_rot_y" style="zoom:25%;" />
		<img src="./gifs/3_Raise_the_terrain_demo_rot_x.gif" alt="3_Raise_the_terrain_demo_rot_x" style="zoom:25%;" />
	</p>
	<p>
		<img src="./gifs/4_Raise_the_terrain_demo_zoom_reinit.gif" alt="4_Raise_the_terrain_demo_zoom_reinit" style="zoom:25%;" />
	</p>
</div>
<hr>



[TOC]

## About

Projects a square grid isometrically and raises (or lowers) each z coordinate from 0 to the altitudes represented as an array given as an input from a file. Developed with the SDL2 graphic library and the C programming language.

## Compilation, usage and navigation

To compile this project you need to have the SDL2 library installed. If not, you can use the included shell script to install it. Change permissions to this file to run it if necessary:

```bash
sudo ./install_SDL2.sh
```

To compile this project on Linux, use this command:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -lm $(sdl2-config --cflags --libs) -o raise_the_terrain
```

To run the program on Linux, use the command:

```bash
./raise_the_terrain <file_name>
```

To interact with the grid, use the following control scheme:

|         Key          |                   Command                   |
| :------------------: | :-----------------------------------------: |
|         ESC          |                Quits program                |
|  W or Up Arrow key   |    Rotates grid clockwise in the x axis     |
| S or Down Arrow key  | Rotates grid counterclockwise in the x axis |
| D or Right Arrow key |    Rotates grid clockwise in the z axis     |
| A or Left Arrow key  | Rotates grid counterclockwise in the z axis |
|          E           |    Rotates grid clockwise in the y axis     |
|          Q           | Rotates grid counterclockwise in the y axis |
|   R or Page Up key   |                   Zoom in                   |
|  F or Page Down key  |                  Zoom out                   |
|          Z           |             Reinitializes view              |

# Author

## 👤 Alfredo Delgado Moreno

[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/AlfredPianist/) [![Twitter Badge](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/Alfred_Pianist) [![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alfredo-delgado-moreno-75b65290/)