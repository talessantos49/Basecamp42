/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/09/19 11:08:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "./includes/get_next_line.h"
#include "./includes/ft_printf.h"
#include "./includes/libft.h"

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

typedef struct s_map
{
	int	height;
	int	width;
}	t_map;

int	key_hook(int keycode, t_data *data, void **mlx)
{
	printf("Keycode: %i\n", keycode);
	return (0);
}

int	window_width(char	*path_map)
{
	int		file;
	int		width;
	char	*line;

	width = 0;
	file = open(path_map, O_RDONLY);
	line = get_next_line(file);
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(file);
	line = ft_strchr(line, '1');
	width = ft_strlen(line);
	return (width - 1);
}

int window_height(char	*path_map)
{
	int		file;
	int		height;
	char	*line;

	height = 0;
	file = open(path_map, O_RDONLY);
	line = get_next_line(file);
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(file);
	line = ft_strchr(line, '1');
	while (line != NULL)
	{
		line = get_next_line(file);
		height++;
	}
	return (height);
}

int main()
{
	t_data data;
    void    *mlx = mlx_init();
    void    *window;
	
	int     fd;
    char    *line;
	char	*result_start;
	int		size;
	int		lenght;
	int		next_line;
	int		first_line;

    int     x;
	int		i;
    int     y;
	int		j;
	int		c;
	int		p;
	int		w;
	int		t;
	int		r;
	int		k;
	int		size_x = 0;
	int		size_y = 0;
	void	*bkg_grass = mlx_xpm_file_to_image(mlx, "./images/backgrouds/Grass_2.xpm", &x, &y);
	void	*bkg_water = mlx_xpm_file_to_image(mlx, "./images/backgrouds/Water.xpm", &w, &t);
    void    *img = mlx_xpm_file_to_image(mlx, "./images/sprites/capy_red.xpm", &i, &j);
	void	*capy = mlx_xpm_file_to_image(mlx, "./images/sprites/capy.xpm", &c, &p);
	void	*rock = mlx_xpm_file_to_image(mlx, "./images/backgrouds/Rock.xpm",&r, &k);

	int		len;

	t_map map;
	map.width = window_width("./maps/map.ber");
	map.height = window_height("./maps/map.ber");
	window = mlx_new_window(mlx, map.width * 32, map.height * 32, "Capivarias");
	
	fd = open("./maps/map.ber", O_RDONLY);
    line = get_next_line(fd);	
	size = 0;
	lenght = 0;
	next_line = 0;
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(fd);
	line = ft_strchr(line, '1');
    if (line == NULL)
		return (1);
	result_start = malloc((ft_strlen(line) + 1));
	ft_printf("O tamanho de line é: %i\n", ft_strlen(line));
	first_line = ft_strlen(line);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (first_line != (len))
			ft_printf("Error tamanho de linha!\n[first_line: %i]-[len: %i]\n", first_line, len);
		while (size < len)
		{
			if (line[size] == '1' || line[size] == '0' || line[size] == 'C' || line[size] == 'P' || line[size] == 'E')
			{
				result_start[size] = line[size];
				if (result_start[size] == '1')
					mlx_put_image_to_window(mlx, window, rock, size * 32, next_line * 32);
				else if (result_start[size] == 'P')
					mlx_put_image_to_window(mlx, window, capy, size * 32, next_line * 32);
				else if (result_start[size] == 'E')
					mlx_put_image_to_window(mlx, window, bkg_water, size * 32, next_line * 32);
				else if (result_start[size] == '0')
					mlx_put_image_to_window(mlx, window, bkg_grass, size * 32, next_line * 32);
				else if (result_start[size] == 'C')
					mlx_put_image_to_window(mlx, window, img, size * 32, next_line * 32);
			}
			else 
				ft_printf("\n\nERROR INVALID MAP size = %i\n\n", size);
			size++;
		}
		result_start[size] = '\0';
		ft_printf("[%i] %s\n", next_line, result_start);
		size = 0;
		line = get_next_line(fd);
		next_line++;
	}
	ft_printf("O valor total de linhas é: %i\n", next_line);
    mlx_loop(mlx);
}

/*	while (size_x < size)
	{
		mlx_put_image_to_window(mlx, window, bkg_grass, size_x * size, size_y * size);
		while (size_y < size)
		{
			if (size_y == 7 && size_x == 7)
				mlx_put_image_to_window(mlx, window, img, size_x * 30, size_y * 30);
			else if (size_y == 5 && size_x == 5)
				mlx_put_image_to_window(mlx, window, capy, size_x * 30, size_y * 30);
			else if (size_x == 10 && size_y == 10)
				mlx_put_image_to_window(mlx, window, bkg_water, size_x * 30, size_y * 30);
			else if (size_x == 0)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else if (size_x == 32)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else if (size_y == 0)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else if (size_y == 32)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else if (size_x == 15)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else if (size_y == 15)
				mlx_put_image_to_window(mlx, window, rock, size_x * 24, size_y * 24);
			else
				mlx_put_image_to_window(mlx, window, bkg_grass, size_x * 30, size_y * 30);
			size_y++;
		}
		size_y=0;
		size_x++;
	}
	*/
/*
int    map_validator()
{
    int        fd;
    char    *line;
	char	*result_start;
	int		size;
	int		lenght;
	int		next_line;



    return (0);
}
*/