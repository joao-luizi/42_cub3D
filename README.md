# cub3d

## Summary
cub3d is a 3D graphics project inspired by Wolfenstein 3D, designed to build a first-person view of a maze using raycasting. It is one of the major projects in the 42 curriculum that introduces graphics programming, parsing, and game logic using C and the miniLibX graphics library.
---

https://github.com/user-attachments/assets/2bfc29d3-7c54-4823-87db-2dcc65504c37

## Table of Contents

- [Project Goals](#project-goals)
- [Features](#features)
- [Learning Highlights](#learning-highlights)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Compilation](#compilation)
- [Bonus](#bonus)
- [License](#license)

---

## Project Goals

The goal is to create a dynamic 3D view from a 2D .cub map file using raycasting principles.

### Core Requirements:
- Raycasting-based 3D rendering
- MiniLibX graphics window
- WASD movement & arrow key view rotation
- Wall textures by orientation (NO, SO, WE, EA)
- Floor and ceiling color rendering
- Clean program exit on ESC or window close
- Proper error handling and .cub parsing
 
## Features
|Feature	          |Description                              |
|-----------------------|-----------------------------------------|
|✅ Raycasting engine	    |Render walls and FOV using raycasting    |
|✅ Texture mapping	    |Different textures for each wall direction             |
|✅ Color fill	    |Floor & ceiling colors in RGB   |
|✅ Map parsing	|Custom .cub scene format            |
|✅ Movement	        |WASD + Arrow keys  |
|✅ Norm-compliant	  |42 Norm fully respected  |
|✅ Memory safe	    |No leaks, proper error handling     |

## Learning Highlights
- Applied raycasting to simulate 3D rendering in a 2D environment
- Built a robust parser to handle flexible .cub scene configurations
- Managed graphics events and rendering loops via miniLibX
- Implemented multithreading to optimize performance (e.g. parallel raycasts)
- Designed a obstacle detection system for vision through open doors or glass elements

## File Structure
```cpp
├── assets
|   ├── maps
|   |   └── *.cub
|   └── textures
|       ├── *.xpm
|       └── bonus/
|           ├── *.xpm
|           └── *.ani
├── inc
|   └── *.h
├── inc_bonus
|   └── *.h
├── lib
|   ├── libft/
|   └── minilibx/
├── src/
|   ├── common
|   |   └── *.c
|   ├── game
|   |   └── *.c
|   ├── render
|   |   └── *.c
|   └── setup
|        └── *.c
├── src_bonus/
|   ├── asc_strings
|   |   └── *.c
|   ├── common
|   |   └── *.c
|   ├── game
|   |   └── *.c
|   ├── render
|   |   └── *.c
|   └── setup
|        └── *.c
├── Makefile
```
## Usage
```c
./bin/cub3D assets/maps/test.cub
OR
./bin/cub3D_bonus assets/maps/test_bonus.cub
```

## Compilation
### Mandatory
```bash
make        # Builds the project
make bonus  # Builds with bonus features
make clean  # Cleans object files
make fclean # Cleans all build artifacts
make re     # Rebuilds everything
```


### Bonus Features
|Feature	          |Description                              |
|-----------------------|-----------------------------------------|
|✅ Minimap    |2D top-down view of map and player location   |
|✅  Wall collisions	    |Accurate movement restrictions against obstacles             |
|✅Doors	    |Openable/closeable doors in the map (D or other custom symbols)   |
|✅ Animated sprites	|Support for animations         |
|✅ Mouse rotation	        |Mouse support for smooth point-of-view turning  |
|✅ Multithreading	  |Performance-optimized raycasting using multiple threads  |
|✅ Transparent 	    |Ray nonblocking obstacle detection     |



### License
This project is licensed under the [MIT License](LICENSE).
