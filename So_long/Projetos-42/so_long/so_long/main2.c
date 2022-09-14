/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/08/17 23:07:27 by tasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000
#define BLUE_PIXEL 0x0000FF
#define GREEN_PIXEL 0x00FF00

typedef struct images
{
	void	*wall;
	void	*dino;
	void	*floor;
	void	*collect;
	void	*portal;
}	db_img;

typedef struct s_img
{
	void	*mlx_img;
	void	*mlx_img2;
	void	*bkg_grass;
	void	*bkg_rock;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

typedef struct s_rect
{
	int x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

void	*mlx_xpm_file_to_image(void *mlx_pointer, char *relative_path, int *width, int *height);

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}
int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}
int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLUE_PIXEL);
	render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
		100, 100, GREEN_PIXEL});
	render_rect(&data->img, (t_rect){0, 0, 500, 300, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}
/*
int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	if (data->win_ptr ==NULL)
		return(1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		i++;
	}
	return (0);
}

int	render(t_data *data)
{
	int	i;

//	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
//	mlx_img = mlx_xpm_file_to_image(data->mlx_ptr , "./images/dinostop.xpm", 
//		height_dino, width_dino);
//	render_rect(data, (t_rect){50, 50, img_width, img_height, img_2});
	while (i < WINDOW_WIDTH)
	{
//		render_rect(data, (t_rect){i,0,10,10, RED_PIXEL});
		render_rect(data, (t_rect){i,WINDOW_HEIGHT-10,10,10, RED_PIXEL});
//		render_rect(data, (t_rect){0,i,10,10, RED_PIXEL});
//		render_rect(data, (t_rect){WINDOW_WIDTH-10, i,10,10, img_2});
		i += 10;
	}

	return (0);
}
*/
int	main(void)
{	
	void	*mlx_2;
	void	*img_2;
	void	*grass;
	void	*rock;
	char	*relative_path_dino = "./images/sprites/Dino.xpm";
	char	*relative_path_coelho = "./images/sprites/capy.xpm";
	char	*backgroud_grass = "./images/backgrouds/Grass.xpm";
	char	*backgroud_rock = "./images/backgrouds/Rock.xpm";
	int		img_width;
	int		img_height;

	t_data data;
	t_img img;
	
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Jurassic Tales");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	grass = mlx_xpm_file_to_image(data.mlx_ptr, backgroud_grass, &img_width, &img_height);
	data.img.bkg_grass = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
//Funcional colocando dois personagens diferentes em pontos definidos
	
	img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, relative_path_dino, &img_width, &img_height);
	if (img.mlx_img == NULL)
		return (printf("ERROR : %i\n", MLX_ERROR));
	img.mlx_img2 = mlx_xpm_file_to_image(data.mlx_ptr, backgroud_grass, &img_width, &img_height);
	if (img.mlx_img2 == NULL)
		return (printf("ERROR : %i\n", MLX_ERROR));
	mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, img.mlx_img2, 100,100);
	mlx_put_image_to_window(data.mlx_ptr,data.win_ptr, img.mlx_img, 100,100);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr); 
//	free(img_2);
	}
	
/*
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./images/dinostop.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Jurassic Tales");
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
}*/