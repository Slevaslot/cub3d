/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:29 by pdosso-d          #+#    #+#             */
/*   Updated: 2023/01/25 16:53:52 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*supp_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	while (str[++i] && str[i] != '\n')
		;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), (ft_strl(str) - i + 1));
	if (!line)
		return (NULL);
	while (str[i])
		line[j++] = str[i++];
	free(str);
	return (line);
}

char	*res_line(char *str)
{
	char	*line;
	int		i;

	i = -1;
	if (!str[0])
		return (NULL);
	while (str[++i] && str[i] != '\n')
		;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line_final(int fd, char *line[fd])
{
	char	*res;

	res = res_line(line[fd]);
	if (!res)
	{
		if (!line[fd])
			return (free(line[fd]), NULL);
	}
	line[fd] = supp_line(line[fd]);
	if (!line[fd])
		return (free(line[fd]), NULL);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			ret;
	static char	*line[4096];
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ret = 1;
	while (ret && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (free(buffer), NULL);
		buffer[ret] = '\0';
		line[fd] = ft_strjoin(line[fd], buffer);
		if (!line[fd])
			return (free(buffer), NULL);
	}
	res = get_next_line_final(fd, line);
	free(buffer);
	return (res);
}

// int main()
// {
// 	char *str1;
// 	int	fd1 = open("pablo", O_RDONLY);
// 	str1 = get_next_line(fd1);
// 	printf("%s", str1);
// 	free(str1);
// 	return (0);
// }
