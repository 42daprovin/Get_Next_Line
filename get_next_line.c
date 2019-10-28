/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 03:04:16 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/28 19:33:06 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

char	*ft_ovread(char **line, char *content)
{
	char *tmp;
	int i;
	int j;

	tmp = content;
	free(*line);
	*line = strdup(content);
	while ((*line)[i] != '\n')
		i++;
	(*line)[i] = '\0';
	if (!(content = (char*)malloc(sizeof(char) * (ft_strlen(content) - i + 1))))
		return (NULL);
	while (tmp[j + i])
	{
		content[j] = tmp[j + i + 1];
		j++;
	}
	free(tmp);
	return (content);
}

int		ft_isinlst(int fd, t_statlst **lst,/* char **dst,*/ char **line)
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
				tmp_lst->content = ft_ovread(line, tmp_lst->content);
				return (2);
			}
			tmp_dst = *line;
			*line = ft_strjoin(*line, tmp_lst->content);
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
	if(!(tmp_lst->content = (char*)malloc(sizeof(ft_strlen(dst) - i))))
		return ;
	(tmp_lst->content)[ft_strlen(dst) - i - 1] = '\0';
	j = 0;
	while (dst[i + 1])
	{
		(tmp_lst->content)[j] = dst[i + 1];
		i++;
		j++;
	}
}

int		ft_read(int fd, t_statlst **lst, char *BUFFER, char **line)
{
	int i;
	int rt;
	char *tmp;

	while ((rt = read(fd, BUFFER, BUFFER_SIZE)) > 0)
	{
		BUFFER[rt] = '\0';
		tmp = *line;//cambio
		*line = ft_strjoin(*line, BUFFER);//cambio
		free(tmp);
		i = 0;
		while (*(*line + i))
		{
			if (*(*line + i) == '\n')
				*(*line + i) = '\0';
			i++;
		}
		if (ft_isinstr('\n', BUFFER))
		{
			ft_changecontent(fd, lst, BUFFER);
			break ;
		}
	}
	return (rt);
}

int		ft_get(int fd, char **line)
{
	char				BUFFER[BUFFER_SIZE + 1];
	char				*tmp;
	static t_statlst	*lst;
	int					rt;
//	int					i;
	int					count;

	if (fd < 0)
		return (-1);
	*line = ft_strdup("");//cambio
	if ((count = ft_isinlst(fd, &lst,/* &dst,*/ line)) == 2)
		return (1);
	if (!count)
		ft_lstnewback(fd, &lst);
/*	while ((rt = read(fd, BUFFER, 10)) > 0)
	{
		BUFFER[rt] = '\0';
		tmp = *line;//cambio
		*line = ft_strjoin(*line, BUFFER);//cambio
		free(tmp);
		i = 0;
		while (*(*line + i))
		{
			if (*(*line + i) == '\n')
				*(*line + i) = '\0';
			i++;
		}
		if (ft_isinstr('\n', BUFFER))
		{
//			if (!count)
//				ft_lstnewback(fd, &lst);
			ft_changecontent(fd, &lst, BUFFER);
			break ;
		}
	} */
	rt = ft_read(fd, &lst, BUFFER, line);
	if (rt == 0)
		return (0);
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
	printf("%s\n", line);
	free(line);
	ft_get(fd2, &line);
	printf("%s\n", line);
	free(line);
	ft_get(fd, &line);
	printf("%s\n", line);

	while (1);
	return 0;
}
