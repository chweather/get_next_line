/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:59:40 by cweather          #+#    #+#             */
/*   Updated: 2017/08/17 16:11:11 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_check_rest(char **rest, char **line)
{
	char				*tmp;

	tmp = ft_strchr(*rest, '\n');
	if (tmp)
	{
		*line = ft_strsub(*rest, 0, tmp - *rest);
		ft_memmove(*rest, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

static int		reader(int fd, char **rest, char **line)
{
	char				buf[BUFF_SIZE + 1];
	int					i;
	char				*tmp;

	while ((i = read(fd, buf, BUFF_SIZE)))
	{
		if (i == -1)
			return (-1);
		buf[i] = '\0';
		tmp = NULL;
		if (*rest)
		{
			tmp = ft_strdup(*rest);
			ft_memdel((void **)rest);
			*rest = ft_strjoin(tmp, buf);
			ft_memdel((void **)&tmp);
		}
		else
			*rest = ft_strdup(buf);
		if (ft_check_rest(rest, line))
			return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char			*rest[256];
	int					result;

	if (!line || fd < 0 || fd > 255)
		return (-1);
	if (rest[fd] && ft_check_rest(&rest[fd], line))
		return (1);
	result = reader(fd, &rest[fd], line);
	if (result != 0)
		return (result);
	if (rest[fd] == NULL || rest[fd][0] == '\0')
		return (0);
	*line = rest[fd];
	rest[fd] = NULL;
	return (1);
}
