/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 12:10:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/06 12:10:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>

static char	*get_kernel(t_view *view)
{
	char	*rslt;
	char	*a;
	char	*b;
	int		fd;
	int		e;

	errno = 0;
	fd = open("../srcs/kernels.cl", O_RDONLY);
	rslt = NULL;
	b = NULL;
	while ((e = get_next_line(fd, &b)) > 0)
	{
		a = rslt;
		rslt = ft_strjoin(a, b);
		ft_strdel(&a);
		ft_strdel(&b);
	}
	ft_strdel(&b);
	if (e == -1)
	{
		perror("Kernel file error");
		exit_x(view);
	}
	close(fd);
	return (rslt);
}

static void	cl_kernel_init(t_view *view, char *frac)
{
	char	*src;
	int		err;

	view->cl->bufscr = clCreateBuffer(view->cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_int) * (WIN_HEIGHT * WIN_WIDTH), NULL, &err);
	view->cl->bufparam = clCreateBuffer(view->cl->context, CL_MEM_READ_WRITE,
			sizeof(cl_float) * 10, NULL, &err);
	src = get_kernel(view);
	view->cl->program = clCreateProgramWithSource(view->cl->context, 1,
			(const char**)&src, NULL, NULL);
	free(src);
	clBuildProgram(view->cl->program, 1, &view->cl->device, NULL, NULL, NULL);
	view->cl->kernel = clCreateKernel(view->cl->program, frac, &err);
	if (err == -46)
	{
		ft_putendl_fd("Fractal not found. Please check your input.", 2);
		exit_x(view);
	}
	clSetKernelArg(view->cl->kernel, 0, sizeof(cl_mem), &view->cl->bufscr);
	clSetKernelArg(view->cl->kernel, 1, sizeof(cl_mem), &view->cl->bufparam);
	view->cl->works = WIN_WIDTH * WIN_HEIGHT;
}

void		cl_read_buffer(t_view *view)
{
	clEnqueueWriteBuffer(view->cl->queue, view->cl->bufscr, CL_TRUE, 0,
			sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, view->scene, 0,
			NULL, NULL);
	clEnqueueWriteBuffer(view->cl->queue, view->cl->bufparam, CL_TRUE, 0,
			sizeof(cl_float) * 10, view->param, 0, NULL, NULL);
	clFinish(view->cl->queue);
}

void		cl_run(t_view *view)
{
	clEnqueueNDRangeKernel(view->cl->queue, view->cl->kernel, 1,
			NULL, &view->cl->works, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(view->cl->queue, view->cl->bufscr, CL_TRUE, 0,
			sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH,
			view->scene, 0, NULL, NULL);
	clFinish(view->cl->queue);
}

void		cl_init(t_view *view, char *frac)
{
	view->cl = (t_cl*)malloc(sizeof(t_cl));
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &(view->cl->device), NULL);
	view->cl->context = clCreateContext(NULL, 1, &view->cl->device,
			NULL, NULL, NULL);
	view->cl->queue = clCreateCommandQueue(view->cl->context,
			view->cl->device, 0, NULL);
	cl_kernel_init(view, frac);
	cl_read_buffer(view);
	cl_run(view);
}
