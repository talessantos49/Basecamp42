/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 00:40:00 by tasantos          #+#    #+#             */
/*   Updated: 2022/02/08 21:18:55 by tasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	checkpositive(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2", 2);
			return (147483648);
		}
		else
		{
			write(1, "-", 1);
			return (-n);
		}
	}
	else if (n > 2147483647)
	{
		return (0);
	}
	else
		return (n);
}

void	ft_putnbr(int nb)
{
	char	print;

	nb = checkpositive(nb);
	if (nb < 10)
	{
		print = nb + '0';
		write (1, &print, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		print = (nb % 10) + '0';
		write (1, &print, 1);
	}
}
