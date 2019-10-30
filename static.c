/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 06:23:33 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/30 15:41:35 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void f(int a)
{
	static char *s;

	a = 1;
	s = (char*)malloc(sizeof(char) * 5);

}

int main()
{
	int a;

	f(a);
	while (1);
}
