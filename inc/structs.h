#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;

}				t_rgb;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_map
{
	char		**map;
	t_point		range;
	t_point		player_position;
	t_point		player_direction;

}				t_map;

typedef struct s_config
{
	char	*normal_file_path;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	char 	*cl_tex;
	char	*fl_tex;
	t_map	map;
}			t_config;


#endif