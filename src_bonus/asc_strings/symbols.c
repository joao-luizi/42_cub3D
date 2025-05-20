/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:37:54 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:24 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Sets the pattern for the 
 * hash symbol ('#').
 * 
 * This function fills a 5x3 integer 
 * array `src` with a pattern that represents the 
 * hash symbol ('#'). The array is populated 
 * with `1` for parts of the symbol and 
 * `0` for empty spaces, forming the correct
 *  visual representation.
 * 
 * @param src A 5x3 integer array where the
 *  hash symbol pattern will be stored.
 */
void	get_pattern_hash(int src[5][3])
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
	src[3][1] = 1;
	src[3][2] = 1;
	src[4][0] = 1;
	src[4][1] = 0;
	src[4][2] = 1;
}

/**
 * @brief Sets the pattern for the plus
 *  symbol ('+').
 * 
 * This function fills a 5x3 integer array
 *  `src` with a pattern that represents the 
 * plus symbol ('+'). The array is populated
 *  with `1` for parts of the symbol and 
 * `0` for empty spaces, forming the correct
 *  visual representation.
 * 
 * @param src A 5x3 integer array where the
 *  plus symbol pattern will be stored.
 */
void	get_pattern_plus(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 0;
	src[0][2] = 0;
	src[1][0] = 0;
	src[1][1] = 1;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 1;
	src[3][0] = 0;
	src[3][1] = 1;
	src[3][2] = 0;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 0;
}

/**
 * @brief Sets the pattern for the minus
 *  symbol ('-').
 * 
 * This function fills a 5x3 integer 
 * array `src` with a pattern that represents the 
 * minus symbol ('-'). The array is populated
 *  with `1` for parts of the symbol and 
 * `0` for empty spaces, forming the correct
 *  visual representation.
 * 
 * @param src A 5x3 integer array where the
 *  minus symbol pattern will be stored.
 */
void	get_pattern_minus(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 0;
	src[0][2] = 0;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 1;
	src[2][1] = 1;
	src[2][2] = 1;
	src[3][0] = 0;
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 0;
}

/**
 * @brief Sets the pattern for the dot
 *  symbol ('.').
 * 
 * This function fills a 5x3 integer 
 * array `src` with a pattern that represents the 
 * dot symbol ('.'). The array is populated 
 * with `1` for parts of the symbol and 
 * `0` for empty spaces, forming the correct
 *  visual representation.
 * 
 * @param src A 5x3 integer array where the 
 * dot symbol pattern will be stored.
 */
void	get_pattern_dot(int src[5][3])
{
	src[0][0] = 0;
	src[0][1] = 0;
	src[0][2] = 0;
	src[1][0] = 0;
	src[1][1] = 0;
	src[1][2] = 0;
	src[2][0] = 0;
	src[2][1] = 0;
	src[2][2] = 0;
	src[3][0] = 0;
	src[3][1] = 1;
	src[3][2] = 0;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 0;
}
