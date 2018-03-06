/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:24:00 by abutok            #+#    #+#             */
/*   Updated: 2017/12/05 00:44:44 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			img_pixel_put(t_view *view, int x, int y, t_color color)
{
	t_color			colorb;
	int				*scene;

	if (view->endian == 1)
	{
		colorb.spectrum.alpha = color.spectrum.blue;
		colorb.spectrum.red = color.spectrum.green;
		colorb.spectrum.green = color.spectrum.red;
		colorb.spectrum.blue = color.spectrum.alpha;
	}
	else
		colorb.color = color.color;
	scene = (int*)view->scene;
	if (x >= view->x || y >= view->y ||
			x < 0 || y < 0)
		return ;
	scene[(y * view->size_line / 4) + x] = colorb.color;
}
