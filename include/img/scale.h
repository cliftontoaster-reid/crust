/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:54:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:49:40 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALE_H
# define SCALE_H

# include "img.h"

# define LANCZOS_A 3
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/// @brief Enumeration of image scaling algorithms.
///
/// This enumeration defines various algorithms used for scaling images.
/// Each algorithm offers a different balance between computational efficiency
/// and output quality. Choose the algorithm that best suits your application's
/// performance and visual quality requirements.
typedef enum s_crust_img_scale_algo
{
	/// @brief Nearest neighbor interpolation.
	CRUST_IMG_SCALE_NEAREST,
	/// @brief Bilinear interpolation.
	CRUST_IMG_SCALE_BILINEAR,
	/// @brief Lanczos interpolation.
	CRUST_IMG_SCALE_LANCZOS,
}						t_crust_img_scale_algo;

typedef struct s_bilinear_context
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	double				dy;
	double				w1;
	double				w2;
	double				w3;
	double				w4;
	t_rgba				c00;
	t_rgba				c10;
	t_rgba				c01;
	t_rgba				c11;
	double				dx;

	t_img				*new_img;
	double				scale_x;
	double				scale_y;
	int					x;
	int					y;
	double				gy;
	double				gx;
}						t_bilinear_context;

typedef struct s_lanczos_context
{
	t_img				*new_img;
	double				orig_x;
	double				orig_y;
	double				sum_r;
	double				sum_g;
	double				sum_b;
	double				sum_a;
	double				weight_sum;
	double				wx;
	double				wy;
	double				weight;
	t_2d				pos;
	t_rgba				c;
	t_rgba				new_color;
}						t_lanczos_context;

typedef struct s_process_row_args
{
	t_lanczos_context	*l;
	t_img				*img;
	int					y_new;
	t_2d				new_size;
	double				scale_x;
	double				scale_y;
}						t_process_row_args;

/// @brief Generates a new image by scaling an existing image.
/// @param img The image to scale.
/// @param new_size The new size of the image.
/// @param algo The scaling algorithm to use.
/// @return A pointer to the new image, or NULL if an error occurred.
t_img					*crust_img_scale(t_img *img, t_2d new_size,
							t_crust_img_scale_algo algo);

/// @brief Scales the given image using nearest neighbor interpolation.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
t_img					*crust_img_scale_nearest(t_img *img, t_2d new_size);

/// @brief Scales the given image using bilinear interpolation.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
t_img					*crust_img_scale_bilinear(t_img *img, t_2d new_size);

/// @brief Scales the given image using the Lanczos resampling method.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
t_img					*crust_img_scale_lanczos(t_img *img, t_2d new_size);
void					laz_loop_one(t_lanczos_context *l, t_img *img);

#endif
