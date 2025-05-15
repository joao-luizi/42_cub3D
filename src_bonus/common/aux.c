/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:54:06 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/15 13:05:42 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Trims leading and trailing whitespace from a string and duplicates it.
 *
 * @param ori The original string to be trimmed and duplicated.
 * @return A newly allocated string without leading and trailing whitespace,
 *         or NULL if memory allocation fails.
 */
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

/**
 * @brief Checks if a character is a whitespace character.
 *
 * @param str The character to check.
 * @return true if the character is a whitespace character, false otherwise.
 */
bool	is_whitespace(char str)
{
	return (str == ' ' || str == '\t' || str == '\r' || str == '\n'
		|| str == '\v' || str == '\f');
}

/**
 * @brief Checks if a string consists entirely of whitespace characters.
 *
 * @param line The string to check.
 * @return true if the string contains only whitespace characters,
	false otherwise.
 */
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

/**
 * @brief Calculates the length of a null-terminated array of strings.
 *
 * @param str The array of strings.
 * @return The number of strings in the array.
 */
size_t	ft_str_array_len(char **str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

/**
 * @brief Counts the occurrences of a specific character in a string.
 *
 * @param count Pointer to an integer where the count will be stored.
 * @param c The character to count.
 * @param str The string in which to count occurrences of the character.
 */
void	count_char(int *count, char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			(*count)++;
		i++;
	}
}
