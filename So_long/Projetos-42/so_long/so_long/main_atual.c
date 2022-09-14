/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/08/25 21:02:21 by tasantos         ###   ########.fr       */
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
open("./maps/map.ber", O_RDONLY);

int	key_hook(int keycode, t_data *data)
{
	printf("Keycode: %i\n", keycode);
	return (keycode); }
int	render_next_frame(void *data)
{ return (0);
}
int main()
{ t_data data;
//	void    *mlx = mlx_init(); // 	void    *window = mlx_new_window(mlx, 400, 400, "Capivarias");
data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 400, 400, "Capivarias2");
    int     x; int		i;
    int     y; int		j;
	int		c; int		p;
	int		w; int		t;
	int		r; int		k;
	int		size_x = 0; int		size_y = 0;
	int		keycode; void	*bkg_grass = mlx_xpm_file_to_image(data.mlx_ptr, "./images/backgrouds/Grass_2.xpm", &x, &y);
	void	*bkg_water = mlx_xpm_file_to_image(data.mlx_ptr, "./images/backgrouds/Water.xpm", &w, &t);
    void    *img = mlx_xpm_file_to_image(data.mlx_ptr, "./images/sprites/capy_red.xpm", &i, &j);
	void	*capy = mlx_xpm_file_to_image(data.mlx_ptr, "./images/sprites/capy.xpm", &c, &p);
	void	*rock = mlx_xpm_file_to_image(data.mlx_ptr, "./images/backgrouds/Rock.xpm",&r, &k);
	int		fd_map;
	char	*line;

	mlx_key_hook(data.win_ptr, key_hook, &data);
	printf("o Valor de retorno é: %i\n",keycode );
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	fd_map = open("./maps/map.ber", O_RDONLY);
	while (size_x < 32)
	{
		line = get_next_line(fd_map);
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, bkg_grass, size_x * 30, size_y * 30);
		while (size_y < 32)
		{
			if (size_y == 7 && size_x == 7)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, size_x * 30, size_y * 30);
			else if (size_y == 5 && size_x == 5)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, capy, size_x * 30, size_y * 30);
			else if (size_y == 6 && size_x == 6)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, capy, size_x * 30, size_y * 30);
			else if (size_x == 10 && size_y == 10)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, bkg_water, size_x * 30, size_y * 30);
			else if (size_x == 0)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else if (size_x == 32)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else if (size_y == 0)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else if (size_y == 32)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else if (size_x == 15)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else if (size_y == 15)
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, rock, size_x * 24, size_y * 24);
			else
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, bkg_grass, size_x * 30, size_y * 30);
			size_y++;
		}
		size_y=0;
		size_x++;
	}
    mlx_loop(data.mlx_ptr);
}