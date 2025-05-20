/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters_p_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:35 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:43 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the letter 'P'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'P'
 * to the provided `src` array. The letter 'P' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'P'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'P' pattern.
 */
void	get_pattern_p(int src[5][3])
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
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 0;
}

/**
 * @brief Retrieves the pattern for the letter 'Q'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'Q'
 * to the provided `src` array. The letter 'Q' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'Q'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'q' pattern.
 */
void	get_pattern_q(int src[5][3])
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
	src[3][1] = 1;
	src[3][2] = 0;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'R'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'R'
 * to the provided `src` array. The letter 'R' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'R'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'R' pattern.
 */
void	get_pattern_r(int src[5][3])
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
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'S'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'S'
 * to the provided `src` array. The letter 'S' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'S'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'S' pattern.
 */
void	get_pattern_s(int src[5][3])
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
	src[3][0] = 0;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the letter 'T'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the letter 'T'
 * to the provided `src` array. The letter 'T' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the letter 'T'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the 'T' pattern.
 */
void	get_pattern_t(int src[5][3])
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
	src[4][0] = 0;
	src[4][1] = 1;
	src[4][2] = 0;
}
