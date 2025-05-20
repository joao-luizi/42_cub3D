/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_f_j.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:42 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:26 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'F'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'F'
 * to the provided `src` array. The letter 'F' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'F'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'F' pattern.
 */
void	get_pattern_f(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 0;
}

/**
 * @brief Retrieves the pattern for the letter 'G'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'G'
 * to the provided `src` array. The letter 'G' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'G'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'G' pattern.
 */
void	get_pattern_g(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 0;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'H'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'H'
 * to the provided `src` array. The letter 'H' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'H'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'H' pattern.
 */
void	get_pattern_h(int src[5][3])
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
 * @brief Retrieves the pattern for the letter 'I'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'I'
 * to the provided `src` array. The letter 'I' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'I'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'I' pattern.
 */
void	get_pattern_i(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
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
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'J'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'J'
 * to the provided `src` array. The letter 'J' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'J'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'J' pattern.
 */
void	get_pattern_j(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 0;
	src[2][1] = 0;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}
