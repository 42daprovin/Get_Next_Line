/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 03:04:16 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/26 19:05:02 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

int		ft_isinlst(int fd, t_statlst **lst, char **dst)
{
	t_statlst	*tmp_lst;
	char		*tmp_dst;

	tmp_lst = *lst;
	while (tmp_lst)
	{
		if (tmp_lst->fd == fd)
		{
			if (ft_isinstr('\n', tmp_lst->content))
			{
				ft_
			}
			tmp_dst = *dst;
			*dst = ft_strjoin(*dst, tmp_lst->content);
			free(tmp_dst);
			return (1);
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}

void	ft_lstnewback(int fd, t_statlst **lst)
{
	t_statlst *new;
	t_statlst *tmp_lst;

	tmp_lst = *lst;
	if (!(new = (t_statlst*)malloc(sizeof(t_statlst))))
		return ;
	new->fd = fd;
	new->next = NULL;
	new->content = ft_strdup("");
	if (!tmp_lst)
	{
		*lst = new;
		return ;
	}
	while (tmp_lst->next)
		tmp_lst = tmp_lst->next;
	tmp_lst->next = new;
}

void	ft_changecontent(int fd, t_statlst **lst,char *dst)
{
	t_statlst *tmp_lst;
	int i;
	int j;

	tmp_lst = *lst;
	while (tmp_lst->fd != fd)
		tmp_lst = tmp_lst->next;
	i = 0;
	while (dst[i] != '\n')
		i++;
	tmp_lst->content = (char*)malloc(sizeof(ft_strlen(dst) - i));
	(tmp_lst->content)[ft_strlen(dst) - i - 1] = '\0';
	j = 0;
	while (dst[i + 1])
	{
		(tmp_lst->content)[j] = dst[i + 1];
		i++;
		j++;
	}
}

int		ft_get(int fd, char **line)
{
	char				BUFFER[11];
	char				*tmp;
	char				*dst;
	static t_statlst	*lst;
	int					rt;
	int					i;
	int					count;

	if (fd < 0)
		return (-1);
	dst = ft_strdup("");
	count =  (ft_isinlst(fd, &lst, &dst));
	if (count == 2)
		return (1);
	while ((rt = read(fd, BUFFER, 10)) > 0)
	{
		BUFFER[rt] = '\0';
		tmp = dst;
		dst = ft_strjoin(dst, BUFFER);
		free(tmp);
		*line = dst;
		i = 0;
		while (*(*line + i))
		{
			if (*(*line + i) == '\n')
				*(*line + i) = '\0';
			i++;
		}
		if (ft_isinstr('\n', BUFFER))
		{
			if (!count)
				ft_lstnewback(fd, &lst);
			ft_changecontent(fd, &lst, BUFFER);
			break ;
		}
	}
	if (rt == 0)
	{
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	int fd;
	char *line;
	int fd2;

	if (ac == 1)
		fd = 0;
	else
	{
		fd = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
	}
	line = NULL;
	ft_get(fd, &line);
	printf("\033[0;38m%s\n", line);
	ft_get(fd2, &line);
	printf("\033[0;38m%s\n", line);
	ft_get(fd, &line);
	printf("\033[0;38m%s\n", line);
	return 0;
}
