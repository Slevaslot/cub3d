/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:50:31 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/18 20:22:57 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	int		j;
	char	*big;
	char	*lit;

	i = 0;
	j = 0;
	if (!str && n == 0)
		return (0);
	big = (char *)str;
	lit = (char *)to_find;
	if (lit[j] == '\0')
		return (&big[i]);
	while (big[i] && i < n)
	{
		while (lit[j] && i + j < n && big[i + j] == lit[j])
			j++;
		if (lit[j] == '\0')
			return (&big[i]);
		j = 0;
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char first[] = "bonjour j je suis";
// 	char second[] = "je ";
// 	printf("---> %s\n", ft_strnstr(first, second, 18));
// 	// printf("%c", strnstr(first, second, 5));
// 	return(0);
// }
