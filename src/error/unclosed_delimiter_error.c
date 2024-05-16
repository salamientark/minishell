#include "parser.h"

void	unclosed_delimiter_error(const char *str, int ref)
{
	write(2, BASH, 9);
	write(2, ": unclosed \'", 12);
	write(2, str + ref, 1);
	write(2, "\' at col ", 9);
	ft_putnbr_fd(ref, 2);
	write(2, "\n", 1);
}
