#include "../../inc/cub3d.h"

bool	get_file_content(char *path, size_t line_count, char ***file_content)
{
	char	*line;
	int		fd;
	int		i;

	*file_content = ft_calloc(sizeof(char *), line_count + 1);
	if (!(*file_content))
		return (ft_putstr_fd("Error.\nAllocation failed.\n", 2), false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error.\nUnable to open file: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		return (ft_putstr_fd("\n", STDERR_FILENO), false);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		
		line[ft_strlen(line) - 1] = '\0'; //remove the ending newline (this is guarranteed to be there)
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
		ft_putstr_fd("Error.\nUnable to open file: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		return (ft_putstr_fd("\n", STDERR_FILENO), i);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	close(fd);
	if (i == 0)
		ft_putstr_fd("Error.\nEmpty configuration file.", STDERR_FILENO);
	return (i);
}



bool	is_map_line(const char *line, char *allowed)
{
	int	i;
	int	j;
	int	allowed_count;

	j = -1;
	allowed_count = 0;
	while (line[++j])
	{
		if (line[j] == ' ')
			continue ;
		i = -1;
		while (allowed[++i])
		{
			if (line[j] == allowed[i])
			{
				allowed_count++;
				break ;
			}
		}
		if (!allowed[i])
			return (false);
	}
	return (allowed_count != 0);
}

