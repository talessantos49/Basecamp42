/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:37:22 by tasantos          #+#    #+#             */
/*   Updated: 2022/08/19 23:40:30 by tasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
/*
	codigos que apareceram quando apertei a tecla W:119 s:115 a:97 d:100 
	Seta pra cima: 65362	Seta pra baixo:	65364	Seta pra direita:	65363	Seta Pra esquerda: 65361
*/
	printf("Keycode: %d\n", keycode);
	printf("Keycode: %i\n", keycode);
	printf("Hello from key_hook!\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}