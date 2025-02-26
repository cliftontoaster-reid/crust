/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:00:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/26 12:12:57 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include <math.h>

/// @brief Limit a value between a minimum and a maximum
/// @param value The value to clamp
/// @param min The minimum value
/// @param max The maximum value
/// @return The clamped value
int		clamp(int value, int min, int max);

/// @brief Compute the sinc function
/// @param x The value to compute the sinc function
/// @return The sinc value
double	sinc(double x);

/// @brief Compute the Lanczos kernel
/// @param x The value to compute the Lanczos kernel
/// @param a The kernel size
/// @return The Lanczos kernel value
double	lanczos(double x, int a);

#endif
