
# Get_Next_Line - 42 Quebec 📖


Project made in a school context, at 42 Quebec. 

## Task asked

Create a function that, when called, returns the next line in a given file descriptor.
On recall, the function must return the next line in the file. 

> **Note**
> Some restrictions were given

> **Note**
> Allowed external functions: read(), malloc(), free().

> **Note**
> A maximum of 10 functions is Allowed.

> **Note**
> Each function can't have more than 25 lines.

> **Warning**
> ***You can't read the entire file and simply return lines one by one.*** On compilation, the user must enter a BUFFER_SIZE with the D- flag. Than, you can only read BUFFER_SIZE bytes of the file at the time. However, even if you dont encounter a line in the first BUFFER_SIZE bytes of the file, you have to read BUFFER_SIZE bytes again until you find one. We do that to prevent a slow response time.






## Acknowledgements

 - Project written 100% in C.
 - This project is a common way of doing this assignement.
 - 100% with Paco, does not pass Paco --Strict
 


## Exemple

Lets take a look at this text file.

```
Hi, my name is Carl. 
Im a fireman. I love to take my dog to the park
the park and play with him.
```

A single call to the get_next_line function with a ***BUFFER_SIZE of 30*** should return

```
Hi, my name is Carl.
```
A second and a third call to the function should return
```
I'm a fireman. I love to
```
```
Take my dog to the park
```
Any subsequent calls should return
```
(null)
```



# Code explained

**You can find all *defines* can in et_next_line.h**

Everything starts here

```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
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
```


Lets take a closer look at this function.

#### Our local variables:
- char *line is the line that we will return.
- static char *stack is where we will put what we read from the file. We use a static variable because we need to remember what we already read last time the function was called.

We start by verifying that the given file descriptor, links to a valid, opened file.
```c
char	*get_next_line(int fd<--) 
```

```c
if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
    {
        reinitialise_stack(&stack);
		return (NULL);
    }
```

Pretty simple stuff: if the file is invalid (fd is negative), the given BUFFER_SIZE is 0 or less, or the file is not readeable, we reinitialise the stack with the *reinitialise_stack(char \*\*stack)* function.

Let's take a look at out *reinitialise_stack(char \*\*stack)* function:

### reinitialise_stack()

```c
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
```
Pretty simple stuff again. We simply check, if the stack was initialised if the first place. We want to free the stack only if the file is valid at the first call, then deleted or closed before a subsequent call. Then, we want to initialise it to NULL again to prevent segfaults.

Why would there be segfaults? Because a user could, for exemple, make a call to the function with a valid file. Close the file before a subsequent call and the reopen it before another call. We then want to return the next line on the reopened file. If we dont set *stack to NULL, we will use out stack after we freeed it. 

The ***return value*** of the function is simply a reference for debugging. It returns 1 if it freed the stack, 0 if not.

### Back to out get_next_line function

```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
    {
        reinitialise_stack(&stack);
		return (NULL);
    }
	stack = read_file_to_stack(fd, stack); <--- we are now here
	if (!stack)
		return (NULL);
	line = get_line_from_stack(stack);
	stack = clean_stack(stack);
	return (line);
}
```

Here, we read the file until we meet a new_line or the EOF and put it in our stack.
Let's take a look at out read_file_to_stack() function. 

## read_file_to_stack()

```c
char	*read_file_to_stack(int fd, char *stack)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(MALLOC_BUFFER_SIZE);
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
```
#### Our locals
- char *buffer | where we put out BUFFER_SIZE bytes of the file before being analysed to see if it contains a new line.
- int read_bytes | The number of bytes read by the read() function.

This function read BUFFER_SIZE bytes of the file, then put them in our stack. It does this until it finds a new_line (with the find_new_line function, a simple redesing of the strchr function of the *<strings.h>* library).

While we do this process, we check, each and every time, if there is a problem with the reading of the file. The *read()* function returns -1 if it can't read from the fiven file.

It there is, in fact, a problem with *read()*, we simply reinitialise our stack, free out buffer, and return NULL. 

Once we found a new line in our buffer and put it in our stack, we simply free our buffer and return our stack. We will trim what is after the '\n' afterwards.

## append_buffer_to_stack()
```c
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
```
This function is self explainatory. We take the buffer (the last BUFFER_SIZE bytes we read from the given file), and append it to our stack. 

#### Our locals
- size_t i | the index of out current and new_stack that we create. 
- size_t buff_i | the index of our buffer
- char *new_stack | the new stack created by joining our current stack with our buffer. 

```c
	if (!stack)
	{
		stack = malloc(sizeof(char) * BYTE_FOR_NULL);
        if (!stack)
		    return (NULL);
		stack[0] = '\0';
	}
```
We first check if out stack exists. It should only exist if we called the get_next_line function more than one time **without any problems**. It it does not exist, we initialise it by allocating it a single byte for the null termination, than, protect it and set it to NULL. 

The rest of the function is a common implementation of the *strjoin()* function from the *<strings.h>* library. 

## Extracting the line from our stack

As you can guess, the next step in our get_next_line function is to extrack the line we found from our stack. We need to do this because we can't simply tell the *read()* function to stop reading after it meets a '\n'. It will only stop after reading BUFFER_SIZE bytes from the file. 

Before stepping inside our *get_line_from_stack()* function, we must protect out stack, because there are a plenty of things that could have gone wrong in *read_file_to_stack()*
#### A reminder of our main function
```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
    {
        reinitialise_stack(&stack);
		return (NULL);
    }
	stack = read_file_to_stack(fd, stack);
	if (!stack)
		return (NULL);
	line = get_line_from_stack(stack); <--- we are now here
	stack = clean_stack(stack);
	return (line);
}
```

## get_line_from_stack()
```c
char	*get_line_from_stack(char *stack)
{
	int		i;
    int line_len;
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
```
This function works in a simple way: it only looks for a '\n' character and returns what was before. 

#### Our locals
- int i | Our index for our stack and our newly created line
- int line_len | the length of the line we are trying to create (used to malloc)
- char *line | the line we are trying to create

As usual, we begin by protecting our stack by simply returning NULL if the stack is empty or NULL. 

The rest if self explainatory. We first get the len of out wanted line by using the *get_line_len()* function (a simple redesing of the *strlen* function that checks not only for the null-terminating character but also '\n). With this length, we can allocate enough memory to store our newly created line. We also add one byte for the new line character if necessary. 

The rest is, again, much self explainatory. We go through our stack until we meet a new line, in this case simple stop our loop and adding '\n' character if it's not the EOF plus the obvious null-terminating character.

## Cleaning and preping our stack for the next get_next_line call

Next and (almost) last step is to clean our static stack for futur uses. 
We need to be sure that the line we will return is not a part of our stack anymore, but we can't simply free out stack. If we do so, we will loose all the bytes read by *read()* but that were not part of the returned line. 

To make it short: we need to erease the returned line from our stack. 
#### A reminder of our main function
```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
    {
        reinitialise_stack(&stack);
		return (NULL);
    }
	stack = read_file_to_stack(fd, stack);
	if (!stack)
		return (NULL);
	line = get_line_from_stack(stack); 
	stack = clean_stack(stack); <--- we are now here
	return (line);
}
```

## Cleaning our stack
Altought the function is simple enough, it has more meat. 
It's not as self-explainatory as I would like it to be. 
```c
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
	cleaned_stack = malloc(sizeof(char) * (ft_strlen(stack) - i + BYTE_FOR_NULL));
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
```

#### Our locals
- int i | The index for our current stack
- cleaned_s_i | the index for our newly created cleaned stack
- char *cleaned_stack | The cleaned version of our stack

First step: get the length of the line we just returned earlier. We do this with *get_line_len()*, function we explained before. We use this information to know where to start to copy 

```c
	if (!stack[i])
	{
		reinitialise_stack(&stack);
		return (NULL);
	}
```
Here, we simply check if there is, in fact, something after the new line. In some cases, we must meet a stack that it's last character was a '\n' or was the EOF. It this case, we simply want to reinitialise our stack and return NULL. Next time get_next_line is called, it will simply be with a fresh freed stack. 

```c
cleaned_stack = malloc(sizeof(char) * (ft_strlen(stack) - i + BYTE_FOR_NULL));
```
Here, we allocate enough memory to store the rest of our stack. We take the length of our current stack minus the length of our previously returned line and add a byte for the null-terminating character. 

Afterwards, we simply protect our newly created cleaned_stack and do a simple strcpy of the rest of the stack.


## Last step: returning the line. 

Here we are, the last step. We simply return the line we extracted before. 

```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (INVALID_FD || BUFFER_SIZE <= 0 || UNREADABLE_FILE)
    {
        reinitialise_stack(&stack);
		return (NULL);
    }
	stack = read_file_to_stack(fd, stack);
	if (!stack)
		return (NULL);
	line = get_line_from_stack(stack);
	stack = clean_stack(stack);
	return (line); <--- we are here now
}
```



# Some needed improvements
This project, 