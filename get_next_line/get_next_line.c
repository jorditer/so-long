/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordi <jordi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:59 by jterrada          #+#    #+#             */
/*   Updated: 2025/02/14 14:55:16 by jordi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(char *buff, int fd, char *chunk)
{
	ssize_t	n;
	char	*tmp;

	while (1)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
			return (free(chunk), NULL);
		if (n == 0)
			break ;
		buff[n] = '\0';
		if (!chunk)
			chunk = ft_strdup("");
		if (!chunk)
			return (NULL);
		tmp = chunk;
		chunk = ft_strjoin(tmp, buff);
		free(tmp);
		if (!chunk || ft_strchr(chunk, '\n'))
			break ;
	}
	if (!chunk || chunk[0] == '\0')
		return (free(chunk), NULL);
	return (chunk);
}

char	*handle_line(char **chunk)
{
	char	*newline_pos;
	char	*line;
	char	*left;

	newline_pos = ft_strchr(*chunk, '\n');
	if (newline_pos)
	{
		left = ft_strdup(newline_pos + 1);
		if (!left)
			return (NULL);
		line = ft_substr(*chunk, 0, (newline_pos - *chunk) + 1);
		if (!line)
			return (NULL);
		free(*chunk);
		*chunk = left;
		return (line);
	}
	line = ft_strdup(*chunk);
	if (!line)
		return (NULL);
	free(*chunk);
	*chunk = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*chunk;
	char		*line;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buff, 0) < 0)
	{
		free(buff);
		if (chunk)
			free(chunk);
		chunk = NULL;
		return (NULL);
	}
	chunk = fill_line(buff, fd, chunk);
	free(buff);
	if (!chunk)
		return (NULL);
	line = handle_line(&chunk);
	return (line);
}

// void	ft_putstr(char *s)
// {
// 	while (*s)
// 	{
// 		write(1, s, 1);
// 		s++;
// 	}
// }
// int main() {
//     int fd = open("test.txt", O_RDONLY);
//     char *result;

//     if (fd < 0) {
//         perror("Error opening file");
//         return 1;
//     }
// 	while (1)
// 	{
// 		result = get_next_line(fd);
// 		if  (!result)
// 			break ;
// 		ft_putstr(result);
// 		free(result);
// 	}
//     result = get_next_line(fd);
//     if (!result) {
//         ft_putstr("\nNULL 1\n");
//         return 1;
//     }
//     ft_putstr(result);
//     free(result);

//     result = get_next_line(fd);
//     if (!result) {
//         ft_putstr("\nNULL 2\n");
//         return 2;
//     }
//     ft_putstr(result);
//     free(result);

//     if (close(fd) == -1) {
//         write(2, "Cannot close file.\n", 19);
//         return 1;
//     }

//     return 0;
// }
