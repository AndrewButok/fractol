/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:59:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/04 10:59:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_fract(void)
{
	ft_putendl("usage: ./fractol [fractal_name]");
	ft_putendl("fractals:");
	ft_putendl("\t\t\t Mandelbrot");
	ft_putendl("\t\t\t Julia");
	ft_putendl("\t\t\t Newton");
	ft_putendl("\t\t\t Interstellar");
	ft_putendl("\t\t\t Burningship");
	ft_putendl("\t\t\t Butterfly");
	ft_putendl("\t\t\t Mandelbrot3");
	ft_putendl("\t\t\t Julia3");
}

int		do_mouse(int button, int x,int y, t_view *view)
{
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	if (button == 4)
		view->param[1] /= 1.01;
	if (button == 5)
		view->param[1]*= 1.01;
	if (button == 1 || button == 5 || button ==4)
	{
		view->param[4] += (x - WIN_WIDTH / 2) / (2 * view->param[1] * WIN_WIDTH / 2);
		view->param[5] += (y - WIN_HEIGHT / 2) / (2 * view->param[1] * WIN_HEIGHT / 2);
	}
	cl_read_buffer(view);
	cl_run(view);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	return (1);
}

int		do_mouse_m(int x,int y, t_view *view)
{
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	view->param[7] = x;
	view->param[8] = y;
	cl_read_buffer(view);
	cl_run(view);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	return (1);
}

t_view	*view_init(char *frac)
{
	t_view *view;
	int i;
	int j;
	int *arr;

	errno = 0;
	view = (t_view*)malloc(sizeof(t_view));
	if (errno)
		perror("View malloc error:");
	view->mlx = mlx_init();
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	view->param = (cl_float*)malloc(sizeof(cl_float)*9);
	view->param[0] = 10000;
	view->param[1] = 1;
	view->param[2] = WIN_WIDTH/2;
	view->param[3] = WIN_HEIGHT/2;
	view->param[4] = 0;
	view->param[5] = 0;
	view->param[6] = view->size_line;
	view->param[7] = 400;
	view->param[8] = 700;
	cl_init(view, frac);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	return (view);
}


int 	main(int argc, char **argv)
{
	t_view	*view;
	t_cl	*cl;

	if (argc != 2)
	{
		print_fract();
		exit(0);
	}
	view = view_init(argv[1]);
	mlx_hook(view->win, 4, 5, &do_mouse, view);
	mlx_hook(view->win, 6, 0, &do_mouse_m, view);
	mlx_loop(view->mlx);
	return (0);
}
