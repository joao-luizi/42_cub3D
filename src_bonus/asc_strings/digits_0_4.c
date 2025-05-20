/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_0_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:37:54 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:52:51 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the digit '0'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '0'
 * to the provided `src` array. The digit '0' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '0'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '0' pattern.
 */
void	get_pattern_zero(int src[5][3])
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

/**
 * @brief Retrieves the pattern for the digit '1'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '1'
 * to the provided `src` array. The digit '1' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '1'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '1' pattern.
 */
void	get_pattern_one(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 1;
	src[0][2] = 0;
	src[1][0] = 1;
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
 * @brief Retrieves the pattern for the digit '2'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '2'
 * to the provided `src` array. The digit '2' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '2'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '2' pattern.
 */
void	get_pattern_two(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 1;
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

/**
 * @brief Retrieves the pattern for the digit '3'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '3'
 * to the provided `src` array. The digit '3' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '3'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '3' pattern.
 */
void	get_pattern_three(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 1;
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
 * @brief Retrieves the pattern for the digit '4'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '4'
 * to the provided `src` array. The digit '4' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '4'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '4' pattern.
 */
void	get_pattern_four(int src[5][3])
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
	src[3][0] = 0;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 1;
}
