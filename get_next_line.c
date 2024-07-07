/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:38:36 by mpelage           #+#    #+#             */
/*   Updated: 2024/07/07 16:22:39 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_to_line(int fd, char *stash, char *buffer)
{
	int		read_count;
	char	*temp;

	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == -1)
			return (free(stash), NULL);
		else if (read_count == 0)
			break ;
		buffer[read_count] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*extract_line(char *line_data)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line_data[i] != '\n' && line_data[i])
		i++;
	if (line_data[i] == '\0')
		return (NULL);
	stash = ft_substr(line_data, i + 1, ft_strlen(line_data) - (i + 1));
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line_data[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	line = buffer_to_line(fd, stash, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	stash = extract_line(line);
	return (line);
}
