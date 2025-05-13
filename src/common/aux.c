#include "../../inc/cub3d.h"

char	*strtrim_dup(char *ori)
{
	char	*result;
	int		start;
	int		end;
	int		k;

	start = 0;
	while (ori[start] && is_whitespace(ori[start]))
		start++;
	end = ft_strlen(ori) - 1;
	while (end >= start && is_whitespace(ori[end]))
		end--;
	result = ft_calloc(sizeof(char), (end - start + 2));
	if (!result)
		return (ft_putstr_fd("Error.\nAllocation failed.\n", 2), NULL);
	k = 0;
	while (start <= end)
		result[k++] = ori[start++];
	return (result);
}

bool	is_whitespace(char str)
{
	return (str == ' ' || str == '\t' || str == '\r' || str == '\n'
		|| str == '\v' || str == '\f');
}

bool	is_whitespace_line(const char *line)
{
	while (*line)
	{
		if (!is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

size_t	ft_str_array_len(char **str)
{
	size_t len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}