/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:16:07 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 16:28:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"


static void	scan_triangle_line(t_player *player, int i, int y, int cell_size)
{
	int		start_x;
	int		end_x;
	int		dy;
	double	base_at_y;

	dy = y - ((MINIMAP_HEIGHT / 2) - (cell_size / 2));
	base_at_y = (double)dy / cell_size * cell_size;
	start_x = (MINIMAP_WIDTH / 2) - (base_at_y / 2);
	end_x = (MINIMAP_WIDTH / 2) + (base_at_y / 2);
	while (start_x <= end_x)
	{
		player->triangle_points[i][y][start_x] = true;
		start_x++;
	}
}

static void	fill_player_points(t_player *player)
{
	int	i;
	int	y;
	int	cell_size;

	i = -1;
	while (++i < 3)
	{
		cell_size = i * 10 + 10;
		y = 0;
		while (y < MINIMAP_HEIGHT)
		{
			if (y >= (MINIMAP_HEIGHT / 2 - cell_size / 2)
				&& y <= (MINIMAP_HEIGHT / 2 + cell_size / 2))
				scan_triangle_line(player, i, y, cell_size);
			y++;
		}
	}
}

bool	init_player_points(t_player *player)
{
	int	i;
	int	j;

	i = -1;
	player->triangle_points = ft_calloc(3, sizeof(bool **));
	if (!player->triangle_points)
		return (false);
	while (++i < 3)
	{
		player->triangle_points[i] = ft_calloc(MINIMAP_HEIGHT, sizeof(bool *));
		if (!player->triangle_points[i])
			return (false);
		j = -1;
		while (++j < MINIMAP_HEIGHT)
		{
			player->triangle_points[i][j] = ft_calloc(MINIMAP_WIDTH,
					sizeof(bool));
			if (!player->triangle_points[i][j])
				return (false);
		}
	}
	fill_player_points(player);
	return (true);
}

bool	init_fov_points(t_player *player)
{
	int		i;
	int		j;
	double	angle;

	player->fov_points = ft_calloc(FOV * 2, sizeof(t_point *));
	if (!player->fov_points)
		return (false);
	i = -1;
	while (++i < FOV * 2)
	{
		player->fov_points[i] = ft_calloc(FOV_D, sizeof(t_point));
		if (!player->fov_points[i])
			return (false);
		j = -1;
		while (++j < FOV_D)
		{
			angle = (i * 0.5) * (M_PI / 180.0) + M_PI + M_PI / 3;
			player->fov_points[i][j].x = MINIMAP_WIDTH / 2 + j * cos(angle);
			player->fov_points[i][j].y = MINIMAP_HEIGHT / 2 + j * sin(angle);
		}
	}
	return (true);
}