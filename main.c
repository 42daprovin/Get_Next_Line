/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:35:44 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/26 18:43:30 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int main()
{
	char *content;
	char *tmp;
	char *tmp2;
	char *line;
	int i = 0;
	int j = 0;

	content = ft_strdup("hola\ndavid");
	tmp = content;
	tmp2 = strdup(content);
	while (tmp2[i] != '\n')
		i++;
	tmp2[i] = '\0';
	line = tmp2;
	content = (char*)malloc(sizeof(char) * (ft_strlen(content) - i + 1));
	while (tmp[j + i])
	{
		content[j] = tmp[j + i + 1];
		j++;
	}
	printf("%s\n",line);
	printf("%s\n", content);
	return (0);
}
