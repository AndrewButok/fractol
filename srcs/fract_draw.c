/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 12:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/13 12:12:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			put_menu(t_view *view)
{
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 10, 0xaaaa,
			"Choose your fractal");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 30, 0xaaaa,
			"1 - Mandelbrot");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 50, 0xaaaa,
			"2 - Julia");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 70, 0xaaaa,
			"3 - Newton");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 90, 0xaaaa,
			"4 - Interstellar");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 110, 0xaaaa,
			"5 - Burningship");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 130, 0xaaaa,
			"6 - Butterfly");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 150, 0xaaaa,
			"7 - Mandelbrot3");
	mlx_string_put(view->mlx, view->win, WIN_WIDTH - 200, 170, 0xaaaa,
			"8 - FabsJulia");
}

static void		put_help(t_view *view)
{
	mlx_string_put(view->mlx, view->win, 20, 10, 0xaaaa,
			"Use Q W E R T A to change the color");
	mlx_string_put(view->mlx, view->win, 20, 30, 0xaaaa,
			"Use F or RMB to freeze mouse cursor for Julia fractals");
	mlx_string_put(view->mlx, view->win, 20, 50, 0xaaaa,
			"Use mouse sphere to zoom or to change numbers iterations");
	mlx_string_put(view->mlx, view->win, 20, 70, 0xaaaa,
			"Use D to set default parameters");
}

static void		put_iterations(t_view *view)
{
	char *str;
	char *to_print;

	str = ft_itoa((int)view->param[0]);
	to_print = ft_strjoin("Number of iterations: ", str);
	ft_strdel(&str);
	mlx_string_put(view->mlx, view->win, 20,
			WIN_HEIGHT - 30, 0xaaaa, to_print);
	ft_strdel(&to_print);
}

void			fract_redraw(t_view *view)
{
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	cl_read_buffer(view);
	cl_run(view);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	put_help(view);
	put_menu(view);
	put_iterations(view);
}
