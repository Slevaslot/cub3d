/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:37:28 by slevaslo          #+#    #+#             */
/*   Updated: 2023/11/08 19:49:44 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_error(int i)
{
	printf("Error : %d", i);
	exit(1);
}

void map_print(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		dprintf(2, "%s\n", str[i]);
}
