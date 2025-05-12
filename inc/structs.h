#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_img
{
	void		*img_ptr;
	char		*data_addr;
	int			size_line;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

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

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_speed
{
	double		linear;
	double		angular;
}				t_speed;

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

typedef struct e_player
{
	t_vector	direction;
	t_vector	position;
	t_vector	plane;
	t_speed		speed;
	bool		shift_pressed;
	bool		alt_pressed;
	bool		up_pressed;
	bool		down_pressed;
	bool		left_pressed;
	bool		right_pressed;
}				t_player;



typedef struct s_graphics
{
	t_img		main_scene;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	t_rgb		floor;
	t_rgb		ceil;
}				t_graphics;

typedef struct e_app_state
{
	void		*mlx;
	void		*win;
	t_graphics	g;
	t_map		*map;
	t_player	player;

}				t_app_state;


#endif