/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousekeys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 12:27:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/10 12:27:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		do_mouse(int button, int x, int y, t_view *view)
{
	if (button == 4)
		view->param[1] /= 1.01;
	if (button == 5)
		view->param[1] *= 1.01;
	if (button == 6)
		view->param[0] += view->param[0] == 10000 ? 0 : 100;
	if (button == 7)
		view->param[0] -= view->param[0] == 100 ? 0 : 100;
	if (button == 1 || button == 5 || button == 4)
	{
		view->is_pressed = button == 1 ? 1 : 0;
		view->param[4] += (x - WIN_WIDTH / 2) /
				(2 * view->param[1] * WIN_WIDTH / 2);
		view->param[5] += (y - WIN_HEIGHT / 2) /
				(2 * view->param[1] * WIN_HEIGHT / 2);
		view->x = x;
		view->y = y;
	}
	fract_redraw(view);
	return (1);
}

int		do_mouse_m(int x, int y, t_view *view)
{
	if (view->is_pressed)
	{
		view->param[4] += (view->x - x) / (100 * view->param[1]);
		view->param[5] += (view->y - y) / (100 * view->param[1]);
		view->x = x;
		view->y = y;
	}
	if (!view->freeze)
	{
		view->param[7] = x;
		view->param[8] = y;
	}
	fract_redraw(view);
	return (1);
}

int		unpress(int key, int x, int y, t_view *view)
{
	if (key == 1)
		view->is_pressed = 0;
	return (1);
}
