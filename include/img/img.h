/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:02:09 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 12:21:54 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# include "libft.h"
# include <stdint.h>

typedef struct s_2d
{
	int		x;
	int		y;
}			t_2d;

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_rgba;

typedef struct s_img
{
	/// @brief The height of the image.
	int		height;
	/// @brief The width of the image.
	int		width;

	void	*mlx_ptr;
	void	*img_ptr;
	void	*data_ptr;
	/// @brief The number of bits per pixel.
	int		bpp;
	/// @brief The size of a line in bytes.
	int		size_line;
	/// @brief The endian of the image.
	int		endian;
}			t_img;

typedef struct s_bilinear_interpolate
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	double	dy;
	double	w1;
	double	w2;
	double	w3;
	double	w4;
	t_rgba	c00;
	t_rgba	c10;
	t_rgba	c01;
	t_rgba	c11;

	t_img	*new_img;
	double	scale_x;
	double	scale_y;
	int		x;
	int		y;
	double	gy;
	double	gx;
}			t_bilinear_interpolate;

/*
 * Add loop indices to the struct for clarity and correct control.
 */
typedef struct s_lanczos_interpolate
{
	t_img	*new_img;
	double	orig_x;
	double	orig_y;
	double	sum_r;
	double	sum_g;
	double	sum_b;
	double	sum_a;
	double	weight_sum;
	double	wx;
	double	wy;
	double	weight;
	t_2d	pos;
	t_rgba	c;
	t_rgba	new_color;

	int		m;
	int		n;
	int		m_start;
	int		m_end;
	int		n_start;
	int		n_end;
	int		x_new;
	int		y_new;
	int		new_width;
	int		new_height;
	double	scale_x;
	double	scale_y;
}			t_lanczos_interpolate;

/// @brief Creates a new image.
/// @param mlx The mlx pointer.
/// @param width The width of the image.
/// @param height The height of the image.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img		*crust_img_new(void *mlx, int width, int height);

/// @brief Reads an XPM image file to create an instance of t_img.
/// @param mlx The mlx pointer.
/// @param file_name The path to the file to load.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img		*crust_img_from_xpm(void *mlx, char *file_name);

/// @brief Puts a pixel of a certain color at a certain position in an image.
/// @param img The image to modify.
/// @param pos The position of the pixel.
/// @param color The color of the pixel.
void		crust_img_put_pixel(t_img *img, t_2d pos, t_rgba color);

/// @brief Gets the color of a pixel at a certain position in an image.
/// @param img The image to read.
/// @param pos The position of the pixel.
/// @return The color of the pixel.
t_rgba		crust_img_get_pixel(t_img *img, t_2d pos);

/// @brief Creates a new image by cropping an existing image.
/// @param img The mlx pointer.
/// @param pos The position of the top-left corner of the new image.
/// @param size The size of the new image.
/// @return A pointer to the created t_img, or NULL if an error occurred.
t_img		*crust_img_crop(t_img *img, t_2d pos, t_2d size);

/// @brief Copies a portion of an image to another image.
/// @param dst The destination image.
/// @param src The source image.
/// @param pos The position of the top-left corner of the portion to copy.
/// @param size The size of the portion to copy.
void		crust_img_cpy(t_img *dst, t_img *src, t_2d pos, t_2d size);

/// @brief Frees the memory allocated for an image.
/// @param img The image to free.
void		crust_img_drop(t_img *img);

#endif
