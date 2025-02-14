/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_from_xpm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:17:46 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 15:49:57 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "mlx.h"
#include <stdint.h>
#include <stdlib.h>

t_img	*crust_img_from_xpm(void *mlx, char *file_name)
{
	t_img	*img;

	if (!mlx || !file_name)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_img));
	img->mlx_ptr = mlx;
	img->img_ptr = mlx_xpm_file_to_image(mlx, file_name, &img->width,
			&img->height);
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	img->data_ptr = (int32_t *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data_ptr)
	{
		mlx_destroy_image(mlx, img->img_ptr);
		free(img);
		return (NULL);
	}
	return (img);
}
