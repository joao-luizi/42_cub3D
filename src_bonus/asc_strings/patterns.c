/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:38:09 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

/**
 * @brief Retrieves the pattern for digits 0-9.
 *
 * This function assigns the correct pattern
 *  for digits '0' through '9'
 * to the provided `letter` array. Each digit
 *  is represented by a 5x3 grid
 * pattern, where each element in the array is
 *  either 0 (empty) or 1 (filled).
 * 
 * @param c The character representing the digit
 *  (0-9).
 * @param letter A 5x3 integer array to store 
 * the character pattern.
 */
void	get_character_pattern_zero_nine(char c, int letter[5][3])
{
	if (c == '0')
		get_pattern_zero(letter);
	if (c == '1')
		get_pattern_one(letter);
	if (c == '2')
		get_pattern_two(letter);
	if (c == '3')
		get_pattern_three(letter);
	if (c == '4')
		get_pattern_four(letter);
	if (c == '5')
		get_pattern_five(letter);
	if (c == '6')
		get_pattern_six(letter);
	if (c == '7')
		get_pattern_seven(letter);
	if (c == '8')
		get_pattern_eight(letter);
	if (c == '9')
		get_pattern_nine(letter);
}

/**
 * @brief Retrieves the pattern for letters 
 * 'a' through 'k' (or 'A' through 'K').
 *
 * This function assigns the correct pattern 
 * for the letters 'a' through 'k'
 * (or 'A' through 'K') to the provided 
 * `letter` array. Each letter is represented
 * by a 5x3 grid pattern, where each element
 *  in the array is either 0 (empty) or 1 (filled).
 * 
 * @param c The character representing the 
 * letter (a-k or A-K).
 * @param letter A 5x3 integer array to store
 *  the character pattern.
 */
void	get_character_pattern_a_k(char c, int letter[5][3])
{
	if (c == 'a' || c == 'A')
		get_pattern_a(letter);
	if (c == 'b' || c == 'B')
		get_pattern_b(letter);
	if (c == 'c' || c == 'C')
		get_pattern_c(letter);
	if (c == 'd' || c == 'D')
		get_pattern_d(letter);
	if (c == 'e' || c == 'E')
		get_pattern_e(letter);
	if (c == 'f' || c == 'F')
		get_pattern_f(letter);
	if (c == 'g' || c == 'G')
		get_pattern_g(letter);
	if (c == 'h' || c == 'H')
		get_pattern_h(letter);
	if (c == 'i' || c == 'I')
		get_pattern_i(letter);
	if (c == 'j' || c == 'J')
		get_pattern_j(letter);
	if (c == 'k' || c == 'K')
		get_pattern_k(letter);
}

/**
 * @brief Retrieves the pattern for 
 * letters 'l' through 'v' (or 'L' through 'V').
 *
 * This function assigns the correct 
 * pattern for the letters 'l' through 'v'
 * (or 'L' through 'V') to the provided `letter` array. 
 * Each letter is represented
 * by a 5x3 grid pattern, where each element in the array
 *  is either 0 (empty) or 1 (filled).
 * 
 * @param c The character representing
 *  the letter (l-v or L-V).
 * @param letter A 5x3 integer array 
 * to store the character pattern.
 */
void	get_character_pattern_l_v(char c, int letter[5][3])
{
	if (c == 'l' || c == 'L')
		get_pattern_l(letter);
	if (c == 'm' || c == 'M')
		get_pattern_m(letter);
	if (c == 'n' || c == 'N')
		get_pattern_n(letter);
	if (c == 'o' || c == 'O')
		get_pattern_o(letter);
	if (c == 'p' || c == 'P')
		get_pattern_p(letter);
	if (c == 'q' || c == 'Q')
		get_pattern_q(letter);
	if (c == 'r' || c == 'R')
		get_pattern_r(letter);
	if (c == 's' || c == 'S')
		get_pattern_s(letter);
	if (c == 't' || c == 'T')
		get_pattern_t(letter);
	if (c == 'u' || c == 'U')
		get_pattern_u(letter);
	if (c == 'v' || c == 'V')
		get_pattern_v(letter);
}

/**
 * @brief Retrieves the pattern for letters
 *  'w' through 'z' (or 'W' through 'Z').
 *
 * This function assigns the correct 
 * pattern for the letters 'w' through 'z'
 * (or 'W' through 'Z') to the provided 
 * `letter` array. Each letter is represented
 * by a 5x3 grid pattern, where each 
 * element in the array is either 0 (empty) or 1 (filled).
 * 
 * @param c The character representing 
 * the letter (w-z or W-Z).
 * @param letter A 5x3 integer array to 
 * store the character pattern.
 */
void	get_character_pattern_w_z(char c, int letter[5][3])
{
	if (c == 'w' || c == 'W')
		get_pattern_w(letter);
	if (c == 'x' || c == 'X')
		get_pattern_x(letter);
	if (c == 'y' || c == 'Y')
		get_pattern_y(letter);
	if (c == 'z' || c == 'Z')
		get_pattern_z(letter);
}

/**
 * @brief Retrieves the pattern for any 
 * valid character (letters a-z, A-Z, digits 0-9, and symbols).
 *
 * This function determines which group the 
 * given character belongs to (letters a-k, l-v, w-z, digits 0-9, or symbols)
 * and delegates the task of retrieving the 
 * appropriate pattern to the respective function. 
 * It handles all characters from 'a' to 'z'
 *  (both uppercase and lowercase), '0' to '9', 
 * as well as special symbols like '+', '-', 
 * '.', and '#'. For unsupported characters, 
 * an empty letter pattern is returned.
 * 
 * @param c The character to retrieve the 
 * pattern for.
 * @param letter A 5x3 integer array to store 
 * the character pattern.
 */
void	get_character_pattern(char c, int letter[5][3])
{
	if ((c >= 'a' && c <= 'k') || (c >= 'A' && c <= 'K'))
		get_character_pattern_a_k(c, letter);
	if ((c >= 'l' && c <= 'v') || (c >= 'L' && c <= 'V'))
		get_character_pattern_l_v(c, letter);
	if ((c >= 'w' && c <= 'z') || (c >= 'W' && c <= 'Z'))
		get_character_pattern_w_z(c, letter);
	if (c >= '0' && c <= '9')
		get_character_pattern_zero_nine(c, letter);
	if (c == '+')
		get_pattern_plus(letter);
	if (c == '-')
		get_pattern_minus(letter);
	if (c == '.')
		get_pattern_dot(letter);
	if (c == '#')
		get_pattern_hash(letter);
	if (c == ' ')
		empty_letter(letter);
}
