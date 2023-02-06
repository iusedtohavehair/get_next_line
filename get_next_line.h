/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchouina <cchouina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:52:23 by cchouina          #+#    #+#             */
/*   Updated: 2023/02/06 09:17:25 by cchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//BUFFER_SIZE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
//ALLOCATION
# define BYTE_FOR_NULL 1
# define BYTE_FOR_NL 1

//DIVERS
# define NEW_LINE '\n'
# endif

//PROTOTYPES
//get_next_line.c functions
char	*get_next_line(int fd);
char	*read_file_to_stack(int fd, char *stack);
char	*get_line_from_stack(char *stack);
char	*clean_stack(char *stack);

//get_next_line_utils.c functions
int		ft_strlen(char *str);
char	*append_buffer_to_stack(char *stack, char *buffer);
int		find_new_line(char *s, int c);
int		get_line_len(char *stack);
int		reinitialise_stack(char **stack);