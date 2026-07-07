*This project has been created as part of the 42 curriculum by alexfran*

# ft_printf

## Description

ft_printf aims to reimplement the function printf from the Standard C library.  
The objective is to display the following conversions c | s | p | d | i | u | x | X | % where :

- %c Prints a single character.
- %s Prints a string (as defined by the common C convention).
- %p The void * pointer argument has to be printed in hexadecimal format.
- %d Prints a decimal (base 10) number.
- %i Prints an integer in base 10.
- %u Prints an unsigned decimal (base 10) number.
- %x Prints a number in hexadecimal (base 16) lowercase format.
- %X Prints a number in hexadecimal (base 16) uppercase format.
- %% Prints a percent sign.

This project allows :
- To understand printf function internally.
- To learn variadic functions (<stdarg.h>).
- To convert and display differents types of data.

## Instructions

In order to compile the program, use this command :  
`cc -Wall -Werror -Wextra FILENAME -L. -lftprintf && ./a.out`

> FILENAME is the name of the file you want to compile

if you want to use an exemple of test code you can use :  
`int main(void)
{
	int a = 42;
    ft_printf("Hello %s!\n", "world");
    ft_printf("Number: %d, Hex: %x\n", a, a);
    return 0;	
}`

## Resources

[va_list](https://man7.org/linux/man-pages/man3/va_list.3type.html)  
[va_start, va_arg, va_end](https://man7.org/linux/man-pages/man3/va_start.3.html)  
[understanding ft_printf from nikito](https://www.youtube.com/watch?v=Hb2m7htiKWM)