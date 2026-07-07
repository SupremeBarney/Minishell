*This project has been created as part of the 42 curriculum by alexfran*

# get_next_line

## Description

get_next_line is a function that reads a line in a file or the standard input and returns it. Repetead calls returns the next line.

This project allows us :
- to understand static variables.
- to learn how to handle memory.
- to manipulate macro.

## Instructions

In order to compile the program, use this command :

`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`

if you want to use an exemple of test code you can use :  
```#include "get_next_line.h"
int main(void)
{
	int i = open("./text", O_RDONLY);
	char *a = get_next_line(i);
	printf("line = %s", a);
	char *q = get_next_line(i);
	printf("line = %s", q);
	char *x = get_next_line(i);
	printf("line = %s", x);
	return (0);
}
```

> This will read the three first lines of the text.

And if you want to use an exemple of test code for the bonus you can use :
```#include "get_next_line.h"
int main(void)
{
	int i = open("./text", O_RDONLY);
	int j = open("./text2", O_RDONLY);
	char *a = get_next_line(i);
	printf("line = %s", a);
	char *q = get_next_line(j);
	printf("line = %s", q);
	char *x = get_next_line(i);
	printf("line = %s", x);
	return (0);
}
```


## Algorithm Explanation

### get_next_line

This function returns the line and tests if fd or buffer size is incorrect and malloc the buffer (buf variable) at the buffer size so it can read all of it.

### fill_stash

This function is the main function of get_next_line. It reads the text and put it in the stash and return the line so get_next_line can return it. If it were up to me I would merge it to get_next_line because it's an extent of it. But the norminette want us to make less than 25 lines.

### read_line

This function reads the line in the stash until it finds the NULL Byte ('\0') or a \n character and returns it with the help of ft_substr.

### empty_stash

This function go through the stash until it finds a NULL Byte ('\0') or a \n character and returns what remains after.

## Resources

[man read](http://manpagesfr.free.fr/man/man2/read.2.html)  
[man open](http://manpagesfr.free.fr/man/man2/open.2.html)  
[understanding get next line by nikito](https://www.youtube.com/watch?v=-Mt2FdJjVno)
