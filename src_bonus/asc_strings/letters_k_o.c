/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_k_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:38 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:34 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'K'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'K'
 * to the provided `src` array. The letter 'K' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'K'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'K' pattern.
 */
void	get_pattern_k(int src[5][3])
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
 * @brief Retrieves the pattern for the letter 'L'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'L'
 * to the provided `src` array. The letter 'L' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'L'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'L' pattern.
 */
void	get_pattern_l(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 0;
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
 * @brief Retrieves the pattern for the letter 'M'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'M'
 * to the provided `src` array. The letter 'M' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'M'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'M' pattern.
 */
void	get_pattern_m(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 1;
	src[1][2] = 1;
	src[2][0] = 1;
	src[2][1] = 0;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'N'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'N'
 * to the provided `src` array. The letter 'N' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'N'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'N' pattern.
 */
void	get_pattern_n(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 0;
	src[0][2] = 1;
	src[1][0] = 1;
	src[1][1] = 1;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 0;
	src[2][2] = 1;
	src[3][0] = 1;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'O'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'O'
 * to the provided `src` array. The letter 'O' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'O'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'O' pattern.
 */
void	get_pattern_o(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
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
