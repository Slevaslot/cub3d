/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:29:10 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/17 18:16:06 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*strdest;
	unsigned char	*strsrc;

	strdest = (unsigned char *)destination;
	strsrc = (unsigned char *)source;
	if (!destination && !source)
		return (NULL);
	if (destination > source)
	{
		while (size-- > 0)
		{
			strdest[size] = strsrc[size];
		}
	}
	else
		ft_memcpy(destination, source, size);
	destination = strdest;
	return (destination);
}

// int main(void)
// {
//     char source[] = "12345";
//     char *destination;
// 	destination = malloc(sizeof(char) * 8);

//     ft_memmove(destination, source, 4);
//     printf("Vrai fonction :\n%s\n", source);
//     printf("%s\n", destination);
// }
