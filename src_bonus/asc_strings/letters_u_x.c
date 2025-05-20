/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_u_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:33 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:52 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'U'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'U'
 * to the provided `src` array. The letter 'U' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'U'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'U' pattern.
 */
void	get_pattern_u(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 1;
	src[2][1] = 0;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'V'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'V'
 * to the provided `src` array. The letter 'V' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'V'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'V' pattern.
 */
void	get_pattern_v(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 1;
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
 * @brief Retrieves the pattern for the letter 'W'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'W'
 * to the provided `src` array. The letter 'W' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'W'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'W' pattern.
 */
void	get_pattern_w(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'X'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'X'
 * to the provided `src` array. The letter 'X' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'X'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'X' pattern.
 */
void	get_pattern_x(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 0;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}
