/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/09/20 17:30:00 by tasantos         ###   ########.fr       */
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

#define MLX_ERROR 1

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_data;

typedef struct s_map
{
	char	**matrix;
	int		n_row;
	int		n_col;
}	t_map;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	if (keysym == 119) //w = 119
		mlx_destroy_window(data->mlx, data->win);
	printf("Keypress: %d\n", keysym);
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

void map_dimensions(t_map *map)
{
	int	i;
	int	j;
	int width;
	int		file;
	char	*line;
	char	*path_map = "./maps/map.ber";
	int	height;

	width = 0;
	height = 0;
	map->n_row = 0;
	file = open(path_map, O_RDONLY);
	line = get_next_line(file);
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(file);
	line = ft_strchr(line, '1');
	map->n_col = ft_strlen(line);
	width = ft_strlen(line);
	while (line != NULL)
	{
		line = get_next_line(file);
		height++;
		map->n_row++;
	}
	ft_printf("O valor de height é: [%i]\nO valor de n_row é: [%i]\nO valor de n_col é: [%i]\nO valor de width é: [%i]\n", height, map->n_row, map->n_col, width);
}

int main()
{
	t_map map;
	t_data data;
	data.mlx = mlx_init();
	
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
	void	*bkg_grass = mlx_xpm_file_to_image(data.mlx, "./images/backgrouds/Grass_2.xpm", &x, &y);
	void	*bkg_water = mlx_xpm_file_to_image(data.mlx, "./images/backgrouds/Water.xpm", &w, &t);
	void	*img = mlx_xpm_file_to_image(data.mlx, "./images/sprites/capy_red.xpm", &i, &j);
	void	*capy = mlx_xpm_file_to_image(data.mlx, "./images/sprites/capy.xpm", &c, &p);
	void	*rock = mlx_xpm_file_to_image(data.mlx, "./images/backgrouds/Rock.xpm",&r, &k);

	int		len;
	map_dimensions(&map);
	ft_printf("O valor de n_row é: [%i]\nO valor de n_col é: [%i]\n", map.n_row, map.n_col);
	data.width = window_width("./maps/map.ber");
	data.height = window_height("./maps/map.ber");
	data.win = mlx_new_window(data.mlx, data.width * 32, data.height * 32, "Capivarias");
	if (data.win == NULL)
	{
		free(data.win);
		return (1);
	}
	
	//mlx_key_hook(data.win, key_hook, &data);
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);

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
			if (line[size] == '1' || line[size] == '0' || line[size] == 'C' || line[size] == 'P' || line[size] == 'E' || line[size] == '\n')
			{
				result_start[size] = line[size];
				if (result_start[size] == '1')
					mlx_put_image_to_window(data.mlx, data.win, rock, size * 32, next_line * 32);
				else if (result_start[size] == 'P')
					mlx_put_image_to_window(data.mlx, data.win, capy, size * 32, next_line * 32);
				else if (result_start[size] == 'E')
					mlx_put_image_to_window(data.mlx, data.win, bkg_water, size * 32, next_line * 32);
				else if (result_start[size] == '0')
					mlx_put_image_to_window(data.mlx, data.win, bkg_grass, size * 32, next_line * 32);
				else if (result_start[size] == 'C')
					mlx_put_image_to_window(data.mlx, data.win, img, size * 32, next_line * 32);
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
    mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
