/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 22:35:06 by pdosso-d          #+#    #+#             */
/*   Updated: 2023/01/25 16:54:18 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr( const char *s, int c )
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != (char)c)
	{
		i++;
	}
	if (str[i] != (char)c)
		return (NULL);
	return (&str[i]);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t		i;
	char		*str;
	size_t		len;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(sizeof(char), 1);
	len = ft_strl((char *)s1);
	str = ft_calloc(sizeof(char), (len + ft_strl((char *)s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = '\0';
	free((char *)s1);
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = NULL;
	if (count * size == 0 || count <= SIZE_MAX / size)
		tab = (void *)malloc(count * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
