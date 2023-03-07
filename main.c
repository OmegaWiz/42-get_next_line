/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:03:02 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/03/07 16:50:38 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnlTester/files/empty", O_RDWR);
	line = (char *) malloc(BUFFER_SIZE);
	/*
	do {
		free(line);
		line = get_next_line(fd);
		printf("%s", line);
	}while (line);
	*/
	for (int i = 0; i < 10; i++)
	{
		gnl_fnr(&line);
		line = get_next_line(fd);
		printf("%s", line);
	}
	close(fd);
	return (0);
}
