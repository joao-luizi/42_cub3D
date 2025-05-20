/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_a_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:45 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:18 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'A'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'A'
 * to the provided `src` array. The letter 'A' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'A'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'A' pattern.
 */
void	get_pattern_a(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 1;
	src[0][2] = 0;
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
 * @brief Retrieves the pattern for the letter 'B'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'B'
 * to the provided `src` array. The letter 'B' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'B'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'B' pattern.
 */
void	get_pattern_b(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 0;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 0;
}

/**
 * @brief Retrieves the pattern for the letter 'C'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'C'
 * to the provided `src` array. The letter 'C' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'C'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'C' pattern.
 */
void	get_pattern_c(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 0;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'D'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'D'
 * to the provided `src` array. The letter 'D' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'D'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'D' pattern.
 */
void	get_pattern_d(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 0;
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
	src[4][2] = 0;
}

/**
 * @brief Retrieves the pattern for the letter 'E'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'E'
 * to the provided `src` array. The letter 'E' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'E'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'E' pattern.
 */
void	get_pattern_e(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}
