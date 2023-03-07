/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:17:05 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/07 14:22:30 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*f(void)
{
	static char	*str;

	str = strdup("const char *s");
	return (str);
}

int main(void)
{
	char	*s;

	s = f();
	printf("%s\n", s);
	free(s);
	return (0);
}
