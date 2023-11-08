/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:59:42 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/18 20:33:13 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = len;
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (ft_strlen(s) - start < len)
		s_len = ft_strlen(s) - start;
	str = malloc(s_len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int main()
// {
// 	// char s[] = "Je suis moi";
// 	// unsigned int start = 3;
// 	// size_t len = 4;

// 	printf("%s", ft_substr("pablo est l", 0, 4000));
// }
