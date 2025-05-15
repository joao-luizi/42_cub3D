/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:19 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 12:39:10 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Loads a texture from a file and initializes the texture structure.
 * 
 * @param mlx The MiniLibX instance used to load the texture.
 * @param tex The texture structure to initialize.
 * @param file The path to the texture file.
 * @return true if the texture was successfully loaded, false otherwise.
 */
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

/**
 * @brief Reads the content of a file and stores it in a dynamically 
 * allocated array of strings.
 * 
 * @param path The path to the file to read.
 * @param line_count The number of lines in the file.
 * @param file_content Pointer to the array of strings to store the file content.
 * @return true if the file was successfully read, false otherwise.
 */
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

/**
 * @brief Counts the number of lines in a file.
 * 
 * @param path The path to the file to count lines in.
 * @return The number of lines in the file, or 0 if the 
 * file could not be opened or is empty.
 */
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

/**
 * @brief Checks if a character is in the allowed set of characters.
 * 
 * @param c The character to check.
 * @param allowed A string containing the allowed characters.
 * @return true if the character is allowed, false otherwise.
 */
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

/**
 * @brief Determines if a line is a valid map line based on allowed characters.
 * 
 * @param line The line to check.
 * @return true if the line is a valid map line, false otherwise.
 */
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
