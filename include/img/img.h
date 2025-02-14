/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:02:09 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 18:45:47 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
#define IMG_H

#include "libft.h"
#include <stdint.h>

typedef struct s_2d
{
	int x;
	int y;
} t_2d;

typedef struct s_rgba
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} t_rgba;

typedef struct s_img
{
	/// @brief The height of the image.
	int height;
	/// @brief The width of the image.
	int width;

	void *mlx_ptr;
	void *img_ptr;
	void *data_ptr;
	/// @brief The number of bits per pixel.
	int bpp;
	/// @brief The size of a line in bytes.
	int size_line;
	/// @brief The endian of the image.
	int endian;
} t_img;

/// @brief Creates a new image.
/// @param mlx The mlx pointer.
/// @param width The width of the image.
/// @param height The height of the image.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img *crust_img_new(void *mlx, int width, int height);

/// @brief Reads an XPM image file to create an instance of t_img.
/// @param mlx The mlx pointer.
/// @param file_name The path to the file to load.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img *crust_img_from_xpm(void *mlx, char *file_name);

/// @brief Puts a pixel of a certain color at a certain position in an image.
/// @param img The image to modify.
/// @param pos The position of the pixel.
/// @param color The color of the pixel.
void crust_img_put_pixel(t_img *img, t_2d pos, t_rgba color);

/// @brief Gets the color of a pixel at a certain position in an image.
/// @param img The image to read.
/// @param pos The position of the pixel.
/// @return The color of the pixel.
t_rgba crust_img_get_pixel(t_img *img, t_2d pos);

/// @brief Creates a new image by cropping an existing image.
/// @param img The mlx pointer.
/// @param pos The position of the top-left corner of the new image.
/// @param size The size of the new image.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img *crust_img_crop(t_img *img, t_2d pos, t_2d size);

/// @brief Copies a portion of an image to another image.
/// @param dst The destination image.
/// @param src The source image.
/// @param pos The position of the top-left corner of the portion to copy.
/// @param size The size of the portion to copy.
void crust_img_cpy(t_img *dst, t_img *src, t_2d pos, t_2d size);

/// @brief Frees the memory allocated for an image.
/// @param img The image to free.
void crust_img_drop(t_img *img);

#endif
