/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:50:35 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/06/03 13:51:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

bool	load_animation(t_app_state *st, char **split, t_anim *anim)
{
	char	*normal_file_path;

	normal_file_path = strtrim_dup(split[0]);
	if (!normal_file_path)
		return (false);
	if (!fill_texture(st->mlx, &anim->frame, normal_file_path))
		return (free(normal_file_path), false);
	anim->duration_ms = ft_atoi(split[1]);
	if (anim->duration_ms <= 0)
		return (free(normal_file_path),
			ft_putstr_fd("Error.\nInvalid frame time.\n", 2), false);
	return (free(normal_file_path), true);
}

static bool	load_animation_frames_util(t_app_state *st, t_anim **anim,
		int i[2], char **file_content)
{
	char	**split;

	split = ft_split(file_content[i[0]], ';');
	if (ft_str_array_len(split) != 2
		|| is_whitespace_line(split[0]) || is_whitespace_line(split[1]))
	{
		ft_putstr_fd("Error.\nInvalid animation line: ", 2);
		ft_putstr_fd(file_content[i[0]], 2);
		ft_putstr_fd("\n", 2);
		return (free_array(file_content), free_array(split), false);
	}
	if (i[1] > 3)
	{
		ft_putstr_fd("Error.\nToo many frames in animation.\n", 2);
		return (free_array(file_content), free_array(split), false);
	}
	if (!load_animation(st, split, &(*anim)[i[1]]))
		return (free_array(file_content), free_array(split), false);
	free_array(split);
	return (true);
}

static void	load_animation_frames_vars(int i[2])
{
	i[0] = -1;
	i[1] = 0;
}

bool	load_animation_frames(t_app_state *st, t_anim **anim,
		char *anim_file)
{
	char	**file_content;
	size_t	line_count;
	int		i[2];

	line_count = count_file_lines(anim_file);
	if (line_count == 0)
		return (false);
	if (!get_file_content(anim_file, line_count, &file_content))
		return (false);
	*anim = ft_calloc(4, sizeof(t_anim));
	if (!anim)
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	load_animation_frames_vars(i);
	while (file_content[++i[0]])
	{
		if (is_whitespace_line(file_content[i[0]]))
			continue ;
		if (!load_animation_frames_util(st, anim, i, file_content))
			return (false);
		i[1]++;
	}
	free_array(file_content);
	if (i[1] < 4)
		return (ft_putstr_fd(ERR_ANIM_FRAMES, 2), false);
	return (true);
}
