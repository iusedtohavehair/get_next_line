#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>//TODO retirer
#include <stdio.h> //TODO retirer

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#endif

//BUFFER_SIZE
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

//FILES ERRORS AND CONDITIONS 
# define EMPTY_FILE (readed_bytes == 0 && stack == NULL)
# define INVALID_FILE readed_bytes < 0
# define UNREADABLE_FILE read(fd, NULL, 0) == -1
# define INVALID_FD fd < 0

//ALLOCATION
# define BYTE_FOR_NULL 1
# define BYTE_FOR_NL 1
# define MALLOC_BUFFER_SIZE sizeof(char) * (BUFFER_SIZE +1)

//DIVERS
# define NEW_LINE '\n'

//PROTOTYPES
//get_next_line.c functions
char	*get_next_line(int fd);
char	*read_file_to_stack(int fd, char *stack);
char	*get_line_from_stack(char *stack);
char	*clean_stack(char *stack);

//get_next_line_utils.c functions
int ft_strlen(char *str);
char	*append_buffer_to_stack(char *stack, char *buffer);
int	find_new_line(char *s, int c);
int get_line_len(char *stack);
int reinitialise_stack(char **stack);