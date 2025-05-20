/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_y_z.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:29 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:03 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'Y'.
 *
 * This function assigns the correct 5x3 pattern 
 * representation for the letter 'Y'
 * to the provided `src` array. The letter 'Y' is
 *  represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern
 *  can be used for displaying the letter 'Y'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 
 * 'Y' pattern.
 */
void	get_pattern_y(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 1;
	src[1][2] = 0;
	src[2][0] = 0;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 0;
	src[3][1] = 1;
	src[3][2] = 0;
	src[4][0] = 0;
	src[4][1] = 1;
	src[4][2] = 0;
}

/**
 * @brief Retrieves the pattern for the letter 'Z'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'Z'
 * to the provided `src` array. The letter 'Z' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'Z'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'Z' pattern.
 */
void	get_pattern_z(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 0;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}
