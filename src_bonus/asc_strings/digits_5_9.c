/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_5_9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:37:54 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:03 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for the digit '5'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '5'
 * to the provided `src` array. The digit '5' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '5'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '5' pattern.
 */
void	get_pattern_five(int src[5][3])
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
 * @brief Retrieves the pattern for the digit '6'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '6'
 * to the provided `src` array. The digit '6' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '6'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '6' pattern.
 */
void	get_pattern_six(int src[5][3])
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
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the digit '7'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '7'
 * to the provided `src` array. The digit '7' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '7'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '7' pattern.
 */
void	get_pattern_seven(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 1;
	src[2][0] = 0;
	src[2][1] = 0;
	src[2][2] = 1;
	src[3][0] = 0;
	src[3][1] = 0;
	src[3][2] = 1;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the digit '8'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '8'
 * to the provided `src` array. The digit '8' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '8'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '8' pattern.
 */
void	get_pattern_eight(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
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
	src[4][1] = 1;
	src[4][2] = 1;
}

/**
 * @brief Retrieves the pattern for the digit '9'.
 *
 * This function assigns the correct 5x3 pattern
 *  representation for the digit '9'
 * to the provided `src` array. The digit '9' is 
 * represented as a grid where each element
 * is either 0 (empty) or 1 (filled). This pattern 
 * can be used for displaying the digit '9'
 * in a character display system.
 * 
 * @param src A 5x3 integer array to store the '9' pattern.
 */
void	get_pattern_nine(int src[5][3])
{
	src[0][0] = 1;
	src[0][1] = 1;
	src[0][2] = 1;
	src[1][0] = 1;
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
