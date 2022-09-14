/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:14:46 by tasantos          #+#    #+#             */
/*   Updated: 2022/09/14 15:26:40 by tasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "./includes/get_next_line.h"
#include "./includes/ft_printf.h"
#include "./includes/libft.h"

int    map_validator()
{
    int        fd;
    char    *line;
	char	*result_start;
	int		size;
	int		lenght;
	int		next_line;


	fd = open("./maps/map.ber", O_RDONLY);
    line = get_next_line(fd);	
	size = 0;
	lenght = 0;
	next_line = 0;
    if (line == NULL)
		return (1);
	while (ft_strchr(line, '1') == NULL)
		line = get_next_line(fd);
	line = ft_strchr(line, '1');
	result_start = malloc((ft_strlen(line) + 1));
	ft_printf("O tamanho de line é: %i\n", ft_strlen(line));
	while (line != NULL)
	{
		while (line[size] == '1' || line[size] == '0' || line[size] == 'C' || line[size] == 'P' || line[size] == 'E')
		{
			result_start[size] = line[size];
			ft_printf("Result_Start [%c]\n", result_start[size]);
			size++;
		}
		result_start[size] = '\0';
		ft_printf("[%i] %s\n", next_line, result_start);
		size = 0;
		line = get_next_line(fd);
		next_line++;
	}
	ft_printf("O valor total de linhas é: %i\n", next_line);
    return (0);
}
