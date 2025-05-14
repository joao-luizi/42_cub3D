/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:19 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:22 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	fill_texture(void *mlx, t_img *tex, char *file)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx, file, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		ft_putstr_fd(ERR_MISS_TEX, 2);
		ft_putstr_fd(file, 2);
		return (ft_putstr_fd("\n", 2), false);
	}
	tex->data_addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->data_addr)
	{
		mlx_destroy_image(mlx, tex->img_ptr);
		tex->img_ptr = NULL;
		{
			ft_putstr_fd(ERR_MISS_TEX, 2);
			ft_putstr_fd(file, 2);
			return (ft_putstr_fd("\n", 2), false);
		}
	}
	return (true);
}

bool	get_file_content(char *path, size_t line_count, char ***file_content)
{
	char	*line;
	int		fd;
	int		i;

	*file_content = ft_calloc(sizeof(char *), line_count + 1);
	if (!(*file_content))
		return (ft_putstr_fd(ERR_ALLOC_FAIL, 2), false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(ERR_OPEN_FILE, 2), ft_putstr_fd(ERR_OPEN_FILE, 2),
			ft_putstr_fd(path, 2), ft_putstr_fd("\n", STDERR_FILENO), false);
	i = 0;
	line = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		(*file_content)[i] = line;
		i++;
	}
	close(fd);
	return (true);
}

size_t	count_file_lines(char *path)
{
	size_t	i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_OPEN_FILE, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		return (ft_putstr_fd("\n", STDERR_FILENO), i);
	}
	line = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	close(fd);
	if (i == 0)
		ft_putstr_fd(ERR_EMPTY_CFG, STDERR_FILENO);
	return (i);
}

bool	is_allowed(char c, char *allowed)
{
	int	i;

	i = -1;
	while (allowed[++i])
	{
		if (allowed[i] == c)
			return (true);
	}
	return (false);
}

bool	is_map_line(const char *line)
{
	int	j;
	int	allowed_count;
	int	not_allowed_count;

	j = -1;
	allowed_count = 0;
	not_allowed_count = 0;
	while (line[++j])
	{
		if (line[j] == ' ')
			continue ;
		if (is_allowed(line[j], MAP_CHARS))
			allowed_count++;
		else
			not_allowed_count++;
	}
	if (allowed_count > 0 && not_allowed_count == 0)
		return (true);
	else
		return (false);
}
