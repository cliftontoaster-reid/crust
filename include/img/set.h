/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:00:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/13 15:19:19 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

# include "img.h"
# include "libft.h"

typedef struct s_set
{
	t_2d	tile_size;
	t_img	*img;
	void	*mlx_ptr;
}			t_set;

/// @brief Creates a new set of images from an XPM file.
/// @param mlx The mlx pointer.
/// @param file_name The path to the file to load.
/// @param tile_size The size of the tiles in the set.
/// @return A pointer to the created t_set, or NULL if an error occurred.
t_set		*crust_set_from_xpm(void *mlx, char *file_name, t_2d tile_size);

/// @brief Gets an image from a set by its index.
/// @param set The set to get the image from.
/// @param idx The index of the image to get.
/// @return A pointer to the image, or NULL if an error occurred.
t_img		*crust_set_get_img(t_set *set, long idx);

/// @brief Gets an image from a set by its position.
/// @param set The set to get the image from.
/// @param pos The position of the image to get.
/// @return A pointer to the image, or NULL if an error occurred.
t_img		*crust_set_get_img_by_pos(t_set *set, t_2d pos);

/// @brief Gets a set of images from a set by their indices.
/// @param set The set to get the images from.
/// @param start The start index.
/// @param end The end index.
/// @return A pointer to the image, or NULL if an error occurred.
t_img		*crust_set_get_imgs(t_set *set, long start, long end);

/// @brief Gets a set of images from a set by their positions.
/// @param set The set to get the images from.
/// @param start The start position.
/// @param end The end position.
/// @return A pointer to the image, or NULL if an error occurred.
t_img		*crust_set_get_imgs_by_pos(t_set *set, t_2d start, t_2d end);

/// @brief Gets a set/tile of a set that does not follow the grid.
/// @param set The set to get the image from.
/// @param pos The position of the image to get.
/// @param size The size of the image to get.
/// @return A pointer to the image, or NULL if an error occurred.
t_img		*crust_set_get_img_offgrid(t_set *set, t_2d pos, t_2d size);

/// @brief Drops a set of images.
/// @param set The set to drop.
void		crust_set_drop(t_set *set);

#endif
