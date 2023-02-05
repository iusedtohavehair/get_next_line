#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return(i);
}

char	*append_buffer_to_stack(char *stack, char *buffer)
{
	size_t	i;
	size_t	buff_i;
	char	*new_stack;

	if (!stack)
	{
		stack = malloc(sizeof(char) * BYTE_FOR_NULL);
        if (!stack)
		    return (NULL);
		stack[0] = '\0';
	}
	new_stack = malloc(sizeof(char) * \
        ((ft_strlen(stack) + ft_strlen(buffer)) + BYTE_FOR_NULL));
	if (!new_stack)
		return (NULL);
	i = -1;
	buff_i = 0;
    while (stack[++i] != '\0')
		new_stack[i] = stack[i];
	while (buffer[buff_i] != '\0')
		new_stack[i++] = buffer[buff_i++];
	new_stack[i] = '\0';
	free(stack);
	return (new_stack);
}


int	find_new_line(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

int get_line_len(char *stack)
{
    int i;

    i = 0;
	while (stack[i] && stack[i] != NEW_LINE)
		i++;
    return (i);
}

int reinitialise_stack(char **stack)
{
    if (*stack)
    {
        free(*stack);
        (*stack) = NULL;
        return (1);
    }
    return (0);
}