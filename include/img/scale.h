/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:54:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 00:12:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALE_H
#define SCALE_H

#include "img.h"

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
} t_crust_img_scale_algo;

/// @brief Generates a new image by scaling an existing image.
/// @param img The image to scale.
/// @param new_size The new size of the image.
/// @param algo The scaling algorithm to use.
/// @return A pointer to the new image, or NULL if an error occurred.
t_img *crust_img_scale(t_img *img, t_2d new_size,
											 t_crust_img_scale_algo algo);

/// @brief Scales the given image using nearest neighbor interpolation.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
__attribute__((visibility("hidden"))) t_img *crust_img_scale_nearest(t_img *img,
																																		 t_2d new_size);

/// @brief Scales the given image using bilinear interpolation.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
__attribute__((visibility("hidden"))) t_img *crust_img_scale_bilinear(t_img *img,
																																			t_2d new_size);

/// @brief Scales the given image using the Lanczos resampling method.
/// @param img A pointer to the source image to be scaled.
/// @param new_size The new dimensions (width and height) for the scaled image.
/// @return A pointer to the newly scaled image or NULL if scaling fails.
__attribute__((visibility("hidden"))) t_img *crust_img_scale_lanczos(t_img *img,
																																		 t_2d new_size);

#endif
