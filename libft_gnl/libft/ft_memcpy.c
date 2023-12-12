/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:16:17 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/18 19:04:10 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t			i;
	unsigned char	*strdest;

	if (!source && !destination)
		return (destination);
	strdest = (unsigned char *)destination;
	i = 0;
	while (i < size)
	{
		strdest[i] = *(unsigned char *)source;
		source++;
		i++;
	}
	destination = strdest;
	return (destination);
}

// int main(void)
// {
//     char source[] = "12345";
//     char *destination;
//     destination = malloc(sizeof(char) * 8);

//     memcpy(destination, source, 4);
//     printf("Vrai fonction :\n%s\n", source);
//     printf("%s\n", destination);

//     char source1[] = "12345";
//     char *destination1;
//     destination1 = malloc(sizeof(char) * 8);

//     ft_memcpy(destination1, source1, 4);
//     printf("\nFausse fonction :\n%s\n", source1);
//     printf("%s", destination1);
// }
