/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:33 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 18:34:21 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef enum e_wall
{
	NONE_WALL,
	NO_WALL,
	SO_WALL,
	WE_WALL,
	EA_WALL,
}						t_wall;

typedef struct s_img
{
	void				*img_ptr;
	char				*data_addr;
	int					size_line;
	int					bpp;
	int					endian;
	int					width;
	int					height;
	int					half_width;
	int					half_height;
}						t_img;

typedef struct s_anim
{
	t_img				frame;
	int					duration_ms;
}						t_anim;

typedef struct s_rgb
{
	int					red;
	int					green;
	int					blue;
}						t_rgb;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_vector
{
	double				x;
	double				y;
}						t_vector;

typedef struct s_speed
{
	double				linear;
	double				angular;
}						t_speed;

typedef struct s_map
{
	char				**map;
	t_point				range;
	t_point				player_position;
	t_point				player_direction;
	int					door_count;
	int					minimap_scale;

}						t_map;

typedef struct s_anim_slot
{
	t_point				map_point;
	int					current_frame;
	struct timeval		frame_start;
	t_anim				*anim_info;
	bool				is_started;
	bool				is_reversed;
	bool				is_start_requested;
}						t_anim_slot;

typedef struct s_config
{
	char				*normal_file_path;
	char				*door_anim;
	char				*face_anim;
	char				*no_tex;
	char				*so_tex;
	char				*we_tex;
	char				*ea_tex;
	char				*cl_tex;
	char				*fl_tex;
	t_map				map;
}						t_config;

typedef struct e_player
{
	t_vector			direction;
	t_vector			position;
	t_vector			plane;
	t_vector			rotation_factor_pos;
	t_vector			rotation_factor_neg;
	t_speed				speed;
	bool				***triangle_points;
	t_point				**fov_points;
	bool				shift_pressed;
	bool				alt_pressed;
	bool				up_pressed;
	bool				down_pressed;
	bool				left_pressed;
	bool				right_pressed;
	bool				turn_left_pressed;
	bool				turn_right_pressed;
}						t_player;

typedef struct s_graphics
{
	bool				fps;
	bool				face;
	bool				minimap;
	bool				fog;
	t_anim				*door_anim;
	t_anim				*face_anim;
	t_img				main_scene;
	t_img				tex_no;
	t_img				tex_so;
	t_img				tex_we;
	t_img				tex_ea;
	t_img				tex_fl;
	t_img				tex_cl;
}						t_graphics;

typedef struct s_obstacle
{
	double				half_height;
	double				dist;
	bool				flip_texture;
	float				blending_factor;
	t_vector			info;
	t_img				*current_tex;
	struct s_obstacle	*next;
}						t_obstacle;

typedef struct e_ray_info
{
	t_obstacle			*obstacles;
	t_vector			ray_dir;
	t_vector			delta_dist;
	t_point				map;
	t_point				step;
	t_vector			side_dist;
	t_wall				wall;
	int					wall_start;
	int					wall_end;
	double				ray_distance;
}						t_ray_info;

typedef struct s_args
{
	int					start_col;
	int					end_col;
	int					index;
	struct e_app_state	*st;
}						t_args;

typedef struct e_app_state
{
	void				*mlx;
	void				*win;
	long				core_count;
	t_args				*args;
	pthread_t			*threads;
	bool				mutex_initialized;
	bool				cond_initialized;
	bool				main_initialized;
	bool				exit_requested;
	bool				*thread_can_render;
	pthread_mutex_t		render_mutex;
	pthread_cond_t		render_cond;
	pthread_cond_t		main_cond;
	bool				render_ready;
	int					threads_done;
	t_graphics			g;
	t_map				*map;
	t_player			player;
	double				*normal_x;
	double				*normal_y;
	t_anim_slot			*anims;
	struct timeval		previous_time;
}						t_app_state;

#endif