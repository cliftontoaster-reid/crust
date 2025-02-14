/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:40:07 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/14 14:50:55 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "mlx.h"

static void	get_imgdata(t_img *img)
{
	img->data_ptr = (int32_t *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data_ptr)
	{
		mlx_destroy_image(img->mlx_ptr, img->img_ptr);
		free(img);
		return (NULL);
	}
}

t_img	*crust_img_new(void *mlx, int width, int height)
{
	t_img	*img;

	if (!mlx || width <= 0 || height <= 0)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_img));
	img->mlx_ptr = mlx;
	img->img_ptr = mlx_new_image(mlx, width, height);
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	get_imgdata(img);
	return (img);
}
