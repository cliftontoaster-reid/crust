/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crust_img_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:49:10 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/13 12:38:54 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "mlx.h"

void	crust_img_drop(t_img *img)
{
	if (!img)
		return ;
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	ft_bzero(img, sizeof(t_img));
	free(img);
}
