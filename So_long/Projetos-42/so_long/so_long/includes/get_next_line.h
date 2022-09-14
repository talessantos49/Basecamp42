/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:19:17 by tasantos          #+#    #+#             */
/*   Updated: 2022/08/25 21:42:45 by tasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *c);
char	*ft_strjoin_gnl(char	*string1, const char	*string2);
char	*ft_strchr(const char *string, int c);
char	*get_line(char	*str);
char	*get_other(char	*str);
char	*new_alocation_buffer(void);
char	*get_next_line(int fd);

#endif