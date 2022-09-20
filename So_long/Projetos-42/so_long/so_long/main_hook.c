/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/09/20 18:07:08 by tasantos         ###   ########.fr       */
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

typedef struct s_map
{
	char	**matrix;
	int		n_row;
	int		n_col;
}	t_map;

typedef struct s_img
{
	void	*rock;
	void	*capy;
	void	*bkg_grass;
	void	*capy_red;
	void	*bkg_water;
} t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	img;
}	t_game;

int	handle_no_event(void *game)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(game->mlx, game->win);
	if (keysym == 119) //w = 119
		mlx_destroy_window(game->mlx, game->win);
	printf("Keypress: %d\n", keysym);
	return (0);
}

void map_dimensions(t_map *map)
{
	int		file;
	char	*line;
	char	*path_map = "./maps/map.ber";

	map->n_row = 0;
	file = open(path_map, O_RDONLY);
	line = get_next_line(file);
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(file);
	line = ft_strchr(line, '1');
	map->n_col = ft_strlen(line);
	while (line != NULL)
	{
		line = get_next_line(file);
		map->n_row++;
	}
}

void	*render_img(char *path_img, t_game *game)
{
	int	width;
	int	height;

	return (mlx_xpm_file_to_image(game->mlx, path_img, &width, &height));
}

int main()
{
	t_map map;
	t_game game;
	game.mlx = mlx_init();
	
	int     fd;
    char    *line;
	char	*result_start;
	int		size;
	int		lenght;
	int		next_line;
	int		first_line;

	int		size_x = 0;
	int		size_y = 0;
	void	*bkg_grass = render_img("./images/backgrouds/Grass_2.xpm", &game);
	void	*bkg_water = render_img("./images/backgrouds/Water.xpm", &game);
	void	*img = render_img ("./images/sprites/capy_red.xpm", &game);
	void	*capy = render_img ("./images/sprites/capy.xpm", &game);
	void	*rock = render_img ("./images/backgrouds/Rock.xpm", &game);

	int		len;
	map_dimensions(&map);
	
	game.win = mlx_new_window(game.mlx, (map.n_col -1) * 32, map.n_row * 32, "Capivarias");
	if (game.win == NULL)
	{
		free(game.win);
		return (1);
	}
	
	mlx_loop_hook(game.mlx, &handle_no_event, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);

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
					mlx_put_image_to_window(game.mlx, game.win, rock, size * 32, next_line * 32);
				else if (result_start[size] == 'P')
					mlx_put_image_to_window(game.mlx, game.win, capy, size * 32, next_line * 32);
				else if (result_start[size] == 'E')
					mlx_put_image_to_window(game.mlx, game.win, bkg_water, size * 32, next_line * 32);
				else if (result_start[size] == '0')
					mlx_put_image_to_window(game.mlx, game.win, bkg_grass, size * 32, next_line * 32);
				else if (result_start[size] == 'C')
					mlx_put_image_to_window(game.mlx, game.win, img, size * 32, next_line * 32);
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
    mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
}
