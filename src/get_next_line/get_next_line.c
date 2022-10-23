/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:25:16 by cyelena           #+#    #+#             */
/*   Updated: 2021/11/30 16:43:48 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_n(char *remains)
{
	int	i;

	i = 0;
	if (!remains)
		return (0);
	while (remains[i])
	{
		if (remains[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*after_n(char *remains)
{
	char	*remainder;
	int		i;

	i = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i] != '\n')
		i++;
	if (remains[i] == '\0')
	{
		free (remains);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(remains) - i + 1));
	if (!remainder)
	{
		free (remains);
		return (NULL);
	}
	ft_strlcpy(remainder, remains + i + 1, ft_strlen(remains) - i + 1);
	free (remains);
	return (remainder);
}

char	*get_line(int fd, char *remains, char *buf)
{
	int			byte_was_read;
	char		*temp;

	byte_was_read = 1;
	while (byte_was_read != 0 && !found_n(remains))
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		if (byte_was_read < 0)
			return (NULL);
		buf[byte_was_read] = '\0';
		if (!remains)
			remains = ft_strdup("");
		if (!remains)
			return (NULL);
		temp = remains;
		remains = ft_strjoin(temp, buf);
		if (!remains)
			return (NULL);
		free(temp);
	}
	return (remains);
}

char	*befor_n(char *remains)
{
	char	*line;
	int		i;

	i = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, remains, i + 2);
	if (line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*buf;
	static char		*remains[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	remains[fd] = get_line(fd, remains[fd], buf);
	free (buf);
	if (!remains[fd])
		return (NULL);
	line = befor_n(remains[fd]);
	remains[fd] = after_n(remains[fd]);
	return (line);
}

// int	main(void)
// {
// 	char	**line;
// 	int		fd1;
// 	int		fd2;
// 	int		counter;

// 	fd1 = open("text2.txt", O_RDONLY);
// 	// write(1, "1", 1);
// 	counter = 0;
// 	line[counter] = get_next_line(fd1);
// 	//fd2 = open("text2.txt", O_RDONLY);
// 	while (counter <= 3)
// 	{
// 		printf("%s", line[counter]);
// 		free (line[counter]);
// 		counter++;
// 		line[counter] = get_next_line(fd1);
// 	}
// 	free (line[counter]);
// }
