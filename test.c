/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 00:05:57 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/24 07:05:38 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int get(int fd, char **line)
{
	char		BUFFER[11];
	char		*tmp;
	char		*dst;
	static char *stc;
	int			rt;
	int			i;
	int		count;
	
	if (fd < 0)
		return (-1);
	dst = ft_strdup("");
	if (stc)
		dst = ft_strjoin(dst, stc);
	while ((rt = read(fd, BUFFER, 10)) > 0)
	{
		BUFFER[rt] = '\0';
		tmp = dst;
		dst = ft_strjoin(dst, BUFFER);
		free(tmp);
		*line = ft_strdup(dst);
		i = 0;
		while (*(*line + i))
		{
			if (*(*line + i) == '\n')
				*(*line + i) = '\0';
			i++;
		}
		if (ft_isinstr('\n', BUFFER))
		{
			i = 0;
			while (BUFFER[i])
			{
				if (BUFFER[i] == '\n')
					count = i;
				i++;
			};
			free(stc);
			stc = (char*)malloc(sizeof(char) * (i - count));
			i = 0;
			while (BUFFER[count + i])
			{
				stc[i] = BUFFER[count + i + 1];
				i++;
			}
			printf("\033[0;33m%s\n", stc);
			break ;
		}
	}
	if (rt == 0)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	int fd;
	char *line;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	while (get(fd, &line))
	{
	printf("\033[0;38m%s\n", line);
	}
	return 0;
}
