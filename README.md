
# Get_Next_Line - 42 Quebec 📖


Project made in a school context, at 42 Quebec. 

/tokei/lines/:provider/:user/:repo

## Task asked

Create a function that, when called, returns the next line in a given file descriptor.
On recall, the function must return the next line in the file. 

> **Warning**
> Some restrictions were given

> **Warning**
> Allowed external functions:
-  read()
- malloc()
- free()

> **Warning**
> A maximum of 10 functions is Allowed

> **Warning**
> Each function can't have more than 25 lines



## Acknowledgements

 - Project written 100% in C.
 - This project is a common way of doing this assignement.
 - 100% with Paco, does not pass Paco --Strict
 


## Exemple

Lets take a look at this text file.

```
Hi, my name is Carl. 
Im a fireman. I love to
Take my dog to the park
```

A single call to the get_next_line function should return

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


## Code explained

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

**Obviously, you can find all *defines* can in et_next_line.h**

Lets take a closer look at this function.

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


