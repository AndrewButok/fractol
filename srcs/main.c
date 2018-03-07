/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:57:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/04 10:57:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_fract(void)
{
	ft_putendl("usage: ./fractol [fractal_name]");
	ft_putendl("fractals:");
	ft_putendl("\t\t\t Mandelbrot");
	ft_putendl("\t\t\t Julia");
	//todo list of fractals

}

int		do_mouse(int button, int x,int y, t_view *view)
{
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);

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
	view->pts = (float*)malloc(sizeof(float) * WIN_WIDTH * WIN_HEIGHT * 2);
	i = -1;
	while (++i < 600)
	{
		j = -1;
		while (++j < 800)
		{
			view->pts[(i*800 + j) * 2] = (j - 400)/200.0f;
			view->pts[(i*800 + j) * 2 + 1] = (i - 300)/200.0f;
		}
	}
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (cl_int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	view->it = (cl_int*)malloc(sizeof(cl_int));
	*(view->it) = 2000;
	view->cl = cl_init(view, frac);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
	//do_mouse(-1,-1,-1,view);
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
	mlx_loop(view->mlx);
	return (0);
}
