/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 09:20:36 by kquetat-          #+#    #+#             */
/*   Updated: 2022/12/30 09:30:48 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_stock_next_call(char *stash)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0)
	{
		free(stash);
		return (0);
	}
	tmp = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (stash[i] == '\n')
		i++;
	j = 0;
	while (stash[i])
	{
		tmp[j] = stash[i];
		j++;
		i++;
	}
	free(stash);
	return (tmp);
}

static char	*ft_stock_result(char *stash)
{
	char	*result;
	int		i;

	i = 0;
	if (stash[i] == 0)
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	result = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		result[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
	{
		result[i] = '\n';
		i++;
	}
	return (result);
}

static char	*ft_read_and_stock(int fd, char	*stash)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (i != 0 && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			free(stash);
			return (0);
		}
		buffer[i] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	stash[fd] = ft_read_and_stock(fd, stash[fd]);
	if (!stash[fd])
		return (0);
	line = ft_stock_result(stash[fd]);
	stash[fd] = ft_stock_next_call(stash[fd]);
	return (line);
}
