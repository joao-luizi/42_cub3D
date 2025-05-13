#ifndef DEFINES_H
# define DEFINES_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define FOV 60
# define MAP_CHARS "01NESW"
# define ERR_BORDER "Error.\nInvalid border detected.\n"
# define ERR_DUP_PLAYER "Error.\nDuplicate player position found.\n"
# define ERR_NO_PLAYER  "Error.\nIndeterminate player position.\n"
# define ERR_ALLOC_FAIL "Error.\nAllocation failed.\n"
# define ERR_OPEN_FILE "Error.\nUnable to open file: "
# define ERR_EMPTY_CFG "Error.\nEmpty configuration file: "
# define ERR_LINE "Error.\nLine error on: '"
# define ERR_FIELDS "Error.\nMissing configurations fields.\n"
# define ERR_DUP_ID "Error.\nDuplicate ID found: "
# define ERR_MAP_DIM "Error.\nInvalid map dimensions.\n"
# define ERR_MISS_TEX "Error.\nMissing texture: "
# define ERR_COLOR_FORMAT "Error.\nIncorrect color format: "
# define ERR_MLX_INIT "Error.\nUnable to initialize mlx.\n"
# define ERR_EMPTY_ARG "Error.\nEmpty file argument.\n"
# define ERR_FILE_EXT "Error.\nWrong file extension. Expected '.cub'.\n"
# define ERR_LAST_ELE "Error.\nMap must be the last element in the file.\n"
# define ERR_MAP_LINE "Error.\nEmpty line on map.\n"
#endif