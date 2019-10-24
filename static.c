/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 06:23:33 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/24 06:36:23 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void f(char **str)
{
	static char *s;
	char *ss;
	
	printf("\033[0;33m%s\n", s);
	if (!s)
	{
		s = malloc(3);
	s[0] = 'D';
	s[1] = 'P';
	s[2] = '\0';
	}
	*str = s;
}

int main()
{
	char *str;

	f(&str);
	printf("\033[0;38m%s\n", str);
	f(&str);
	printf("\033[0;38m%s\n", str);
}
