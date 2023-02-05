
# Get_Next_Line - 42 Quebec 📖


Project made in a school context, at 42 Quebec. 

/tokei/lines/:provider/:user/:repo


## Task asked

Create a function that, when called, returns the next line in a given file descriptor.
On recall, the function must return the next line in the file. 



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

