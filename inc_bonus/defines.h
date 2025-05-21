/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:28 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/21 12:41:59 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <threads.h>
# include <pthread.h>
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
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define FACE_X 10
# define FACE_Y 10
# define MAIN_WIDTH 1200
# define MAIN_HEIGHT 800
# define MAX_THREADS 8
# define PLAYER_ROT_SPEED 0.02
# define PLAYER_MOV_SPEED 0.04

# define MAX_BLEND_FACTOR 1.0f
# define MAX_DISTANCE 10.0f
# define F1_KEY 269025093
# define F2_KEY 269025094
# define F3_KEY 269025095
# define F4_KEY 269025096

# define SPACE_KEY 32
# define MAP_CHARS "01NESWD"
# define ERR_BORDER "Error.\nInvalid border detected.\n"
# define ERR_DUP_PLAYER "Error.\nDuplicate player position found.\n"
# define ERR_NO_PLAYER "Error.\nIndeterminate player position.\n"
# define ERR_ALLOC_FAIL "Error.\nAllocation failed.\n"
# define ERR_OPEN_FILE "Error.\nUnable to open file: "
# define ERR_EMPTY_CFG "Error.\nEmpty configuration file: "
# define ERR_LINE "Error.\nLine error on: '"
# define ERR_FIELDS "Error.\nMissing configurations fields.\n"
# define ERR_DUP_ID "Error.\nDuplicate ID found: "
# define ERR_MAP_DIM "Error.\nInvalid map dimensions.\n"
# define ERR_MAP_CHAR "Error.\nInvalid char detected.\n"
# define ERR_MISS_TEX "Error.\nMissing texture: "
# define ERR_COLOR_FORMAT "Error.\nIncorrect color format: "
# define ERR_MLX_INIT "Error.\nUnable to initialize mlx.\n"
# define ERR_EMPTY_ARG "Error.\nEmpty file argument.\n"
# define ERR_FILE_EXT "Error.\nWrong file extension. Expected '.cub'.\n"
# define ERR_LAST_ELE "Error.\nMap must be the last element in the file.\n"
# define ERR_MAP_LINE "Error.\nEmpty line on map.\n"
# define ERR_IMG_INIT "Error.\nUnable to initialize mlx image."
# define ERR_WIN_INIT "Error.\nUnable to initialize mlx window."
# define ERR_IMG_DA "Error.\nUnable to initialize mlx image data address."
# define ERR_MUTEX_INIT "Error.\nUnable to initialize mutex."
# define ERR_COND_INIT "Error.\nUnable to initialize condition variable."
# define ERR_MLX_DESTROY "Error.\nUnable to destroy mlx window."
# define ERR_THREAD_CREATE "Error.\nUnable to create thread."
#endif