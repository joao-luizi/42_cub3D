/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:38:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/22 12:23:59 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"


/**
 * @brief Paints a square of pixels at the given
 *  position with the specified color.
 * 
 * This function paints a square of pixels
 *  (pixel_size x pixel_size) on the specified
 * image section at the given position. The
 *  color of the square is determined by
 * the `color` parameter.
 *
 * @param section Pointer to the image section
 *  where the pixels will be painted.
 * @param pixel_size The size of each square
 *  pixel.
 * @param pos The position (top-left corner) 
 * where the square will be painted.
 * @param color The color to paint the square 
 * pixels.
 */
void	paint_pixel(t_img *section, int pixel_size, t_point pos, int color)
{
	int	py;
	int	px;
	int	*data;

	data = (int *)section->data_addr;
	py = 0;
	while (py < pixel_size)
	{
		px = 0;
		while (px < pixel_size)
		{
			data[(pos.y + py) * section->width + (pos.x + px)] = color;
			px++;
		}
		py++;
	}
}

/**
 * @brief Draws a character on the specified 
 * image section using a 5x3 pixel map.
 * 
 * This function draws a character on the
 *  image section by mapping a 5x3 matrix 
 * of pixels to the section. The pixels are
 *  either black (0x00000000) or white 
 * (0xFFFFFFFF) depending on the character map. The position of the character 
 * is determined by the offset values.
 *
 * @param offset_x The x-offset for the 
 * character's position.
 * @param offset_y The y-offset for the 
 * character's position.
 * @param section Pointer to the image section
 *  where the character will be drawn.
 * @param char_map A 5x3 matrix representing 
 * the pixel map of the character.
 */
void	draw_char_to_image(int offset_x, int offset_y, t_img *section,
		int char_map[5][3])
{
	t_point		pos;
	int			pixel_size;
	int			j;
	int			i;

	pixel_size = 3;
	j = 0;
	while (j < 5)
	{
		i = 0;
		while (i < 3)
		{
			pos.x = offset_x + (i * pixel_size);
			pos.y = offset_y + (j * pixel_size);
			if (char_map[j][i] == 1)
				paint_pixel(section, pixel_size, pos, 0x000000);
			i++;
		}
		j++;
	}
}

/**
 * @brief Initializes a 5x3 array to 
 * represent an empty letter pattern.
 * 
 * This function sets all elements of
 *  the 5x3 array `src` to zero, effectively creating 
 * an empty letter pattern. The array
 *  is intended to represent a character in a 5x3 grid, 
 * and this function ensures the grid
 *  is cleared before use.
 * 
 * @param src A 5x3 integer array representing
 *  the letter's pattern to be cleared.
 */
void	empty_letter(int src[5][3])
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
	src[3][1] = 0;
	src[3][2] = 0;
	src[4][0] = 0;
	src[4][1] = 0;
	src[4][2] = 0;
}

/**
 * @brief Prints a 5x3 letter pattern to the console for debugging purposes.
 * 
 * This function takes a 5x3 matrix representing a character's pixel map
 * and prints it to the console. Each `1` in the matrix is represented
 * by a `#`, and each `0` is represented by a space.
 * 
 * @param letter A 5x3 integer array representing the letter's pattern.
 */
void	debug_print_letter(int letter[5][3])
{
    int	row;
    int	col;

    row = 0;
    while (row < 5)
    {
        col = 0;
        while (col < 3)
        {
            if (letter[row][col] == 1)
                printf("#");
            else
                printf(" ");
            col++;
        }
        printf("\n"); // Move to the next row
        row++;
    }
    printf("\n"); // Add a blank line after the letter for readability
}

/**
 * @brief Writes a string of characters to an 
 * image at a specified position.
 * 
 * This function iterates over the input string
 *  `str` and writes each character to an image 
 * at the given `x` and `y` coordinates. Each 
 * character is represented using a 5x3 pattern, 
 * which is fetched by the `get_character_pattern`
 *  function and then drawn onto the image 
 * using the `draw_char_to_image` function. The 
 * characters are placed side by side with a 
 * horizontal spacing of 10 pixels.
 * 
 * @param str The string of characters to be written
  to the image.
 * @param x The x-coordinate of the starting position
  for writing the string.
 * @param y The y-coordinate of the starting position
  for writing the string.
 * @param section A pointer to the `t_img` structure
  that represents the image section 
 *                where the string will be drawn.
 */
void	lib_x_write_string(char *str, int x, int y, t_img *section)
{
	int	i;
	int	letter[5][3];

	empty_letter(letter);
	i = 0;
	while (str[i])
	{
		get_character_pattern(str[i], letter);
		draw_char_to_image(x + (i * 10), y, section, letter);
		i++;
	}
}
