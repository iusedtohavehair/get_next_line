/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchouina <cchouina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:52:12 by cchouina          #+#    #+#             */
/*   Updated: 2023/02/06 09:05:35 by cchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (fd< 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		reinitialise_stack(&stack);
		return (NULL);
	}
	stack = read_file_to_stack(fd, stack);
	if (!stack)
		return (NULL);
	line = get_line_from_stack(stack);
	stack = clean_stack(stack);
	return (line);
}

char	*read_file_to_stack(int fd, char *stack)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!find_new_line(stack, NEW_LINE) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			reinitialise_stack(&stack);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stack = append_buffer_to_stack(stack, buffer);
	}
	free(buffer);
	return (stack);
}

char	*get_line_from_stack(char *stack)
{
	int		i;
	int		line_len;
	char	*line;

	if (!stack[0] || !stack)
		return (NULL);
	i = 0;
	line_len = get_line_len(stack);
	line = malloc(sizeof(char) * (line_len + BYTE_FOR_NL + BYTE_FOR_NULL));
	if (!line)
		return (NULL);
	while (stack[i] && stack[i] != NEW_LINE)
	{
		line[i] = stack[i];
		i++;
	}
	if (stack[i] == NEW_LINE)
	{
		line[i] = stack[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_stack(char *stack)
{
	int		i;
	int		cleaned_s_i;
	char	*cleaned_stack;

	i = get_line_len(stack);
	cleaned_s_i = 0;
	if (!stack[i])
	{
		reinitialise_stack(&stack);
		return (NULL);
	}
	cleaned_stack = malloc(sizeof(char) * (ft_strlen(stack) - i
				+ BYTE_FOR_NULL));
	if (!cleaned_stack)
	{
		free(stack);
		return (NULL);
	}
	i++;
	while (stack[i])
		cleaned_stack[cleaned_s_i++] = stack[i++];
	cleaned_stack[cleaned_s_i] = '\0';
	free(stack);
	return (cleaned_stack);
}
